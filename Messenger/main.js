const http = require("http");
const express = require("express");
const { Server } = require("socket.io");

const app = express();
const PORT = 8080;

app.use(express.json({ limit: "50mb" }));
app.use(express.static(__dirname));

const server = http.createServer(app);
const io = new Server(server, {
    maxHttpBufferSize: 50 * 1024 * 1024,
    transports: ["websocket", "polling"]
});

// Хранилища данных
const usersDB = {};     
const chatsDB = {};          
const userChatsIndex = {};  

// ID чата — отсортированная пара имён, чтобы у A->B и B->A был один ID
function getChatId(user1, user2) {
    return [user1, user2].sort().join("__");
}

function ensureChat(user1, user2) {
    const chatId = getChatId(user1, user2);
    if (!chatsDB[chatId]) {
        chatsDB[chatId] = {
            id: chatId,
            participants: [user1, user2],
            messages: [],
            createdAt: Date.now()
        };
        if (!userChatsIndex[user1]) userChatsIndex[user1] = new Set();
        if (!userChatsIndex[user2]) userChatsIndex[user2] = new Set();
        userChatsIndex[user1].add(chatId);
        userChatsIndex[user2].add(chatId);
    }
    return chatId;
}

io.on("connection", (socket) => {
    console.log("Подключение:", socket.id);

    // Регистрация
    socket.on("register", (data, callback) => {
        const username = (data.username || "").trim();
        const password = data.password || "";
        if (username.length < 2) return callback({ success: false, error: "Имя должно содержать минимум 2 символа" });
        if (usersDB[username]) return callback({ success: false, error: "Пользователь с таким именем уже существует" });
        usersDB[username] = password;
        callback({ success: true, message: "Регистрация успешна!" });
    });

    // Вход
    socket.on("auth", (data, callback) => {
        const username = (data.username || "").trim();
        const password = data.password || "";
        if (!usersDB[username]) return callback({ success: false, error: "Пользователь не найден" });
        if (usersDB[username] !== password) return callback({ success: false, error: "Неправильный пароль" });
        socket.username = username;
        socket.join("user_" + username); 
        callback({ success: true, username });
    });

    // Список чатов текущего пользователя
    socket.on("getChatsList", (data, callback) => {
        if (!socket.username) return callback({ success: false });
        const chatIds = Array.from(userChatsIndex[socket.username] || []);
        const list = chatIds.map(chatId => {
            const chat = chatsDB[chatId];
            const partner = chat.participants.find(p => p !== socket.username);
            const lastMsg = chat.messages[chat.messages.length - 1] || null;
            return {
                chatId,
                partner,
                lastMessage: lastMsg ? { text: lastMsg.text, image: !!lastMsg.image, timestamp: lastMsg.timestamp } : null
            };
        });
        // Новые сообщения сверху
        list.sort((a, b) => {
            const ta = a.lastMessage && a.lastMessage.timestamp ? a.lastMessage.timestamp : "";
            const tb = b.lastMessage && b.lastMessage.timestamp ? b.lastMessage.timestamp : "";
            return tb.localeCompare(ta);
        });
        callback({ success: true, chats: list });
    });

    // Поиск пользователей
    socket.on("searchUsers", (data, callback) => {
        if (!socket.username) return callback({ success: false });
        const query = (data.query || "").trim().toLowerCase();
        if (!query) return callback({ success: true, users: [] });
        const results = Object.keys(usersDB)
            .filter(u => u !== socket.username && u.toLowerCase().includes(query))
            .slice(0, 20);
        callback({ success: true, users: results });
    });

    // Открыть/создать чат с пользователем
    socket.on("openChatWith", (data, callback) => {
        if (!socket.username) return callback({ success: false });
        const partner = (data.partner || "").trim();
        if (!usersDB[partner]) return callback({ success: false, error: "Пользователь не найден" });
        if (partner === socket.username) return callback({ success: false, error: "Нельзя создать чат с самим собой" });
        const chatId = ensureChat(socket.username, partner);
        socket.join("chat_" + chatId);
        callback({ success: true, chatId, partner, messages: chatsDB[chatId].messages });
    });

    // Открыть существующий чат по ID
    socket.on("openChat", (data, callback) => {
        if (!socket.username) return callback({ success: false });
        const chat = chatsDB[data.chatId];
        if (!chat) return callback({ success: false, error: "Чат не найден" });
        if (!chat.participants.includes(socket.username)) return callback({ success: false, error: "Нет доступа" });
        socket.join("chat_" + data.chatId);
        const partner = chat.participants.find(p => p !== socket.username);
        callback({ success: true, chatId: data.chatId, partner, messages: chat.messages });
    });

    // Отправка сообщения в конкретный чат
    socket.on("sendMessage", (data) => {
        if (!socket.username) return;
        const chat = chatsDB[data.chatId];
        if (!chat || !chat.participants.includes(socket.username)) return;
        const msg = {
            from: socket.username,
            text: data.text || "",
            image: data.image || null,
            timestamp: new Date().toLocaleTimeString()
        };
        chat.messages.push(msg);
        // Сообщение всем, кто в комнате этого чата
        io.to("chat_" + data.chatId).emit("newMessage", { chatId: data.chatId, message: msg });
        // Уведомление собеседнику (даже если он не открыл чат — чтобы обновить список)
        chat.participants.forEach(p => {
            if (p !== socket.username) {
                io.to("user_" + p).emit("chatUpdated", {
                    chatId: data.chatId,
                    partner: socket.username,
                    lastMessage: { text: msg.text, image: !!msg.image, timestamp: msg.timestamp }
                });
            }
        });
    });

    socket.on("disconnect", () => console.log("Отключение:", socket.id));
});

server.listen(PORT, "0.0.0.0", () => {
    console.log("Сервер запущен на http://localhost:" + PORT);
});