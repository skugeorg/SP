document.addEventListener("DOMContentLoaded", () => {
    const authModal = document.getElementById("authModal");
    const authUsername = document.getElementById("authUsername");
    const authPassword = document.getElementById("authPassword");
    const authButton = document.getElementById("authButton");
    const authError = document.getElementById("authError");
    const authTitle = document.getElementById("authTitle");
    const authSubtitle = document.getElementById("authSubtitle");
    const toggleText = document.getElementById("toggleText");
    const toggleAuthMode = document.getElementById("toggleAuthMode");

    const messenger = document.getElementById("messenger");
    const currentUserName = document.getElementById("currentUserName");
    const logoutButton = document.getElementById("logoutButton");
    const searchInput = document.getElementById("searchInput");
    const searchResults = document.getElementById("searchResults");
    const chatsList = document.getElementById("chatsList");
    const chatPlaceholder = document.getElementById("chatPlaceholder");
    const chatActive = document.getElementById("chatActive");
    const chatPartnerName = document.getElementById("chatPartnerName");
    const messagesArea = document.getElementById("messagesArea");
    const messageInput = document.getElementById("messageInput");
    const sendButton = document.getElementById("sendButton");
    const fileInput = document.getElementById("fileInput");
    const attachButton = document.getElementById("attachButton");

    console.log("Элементы найдены:", {
        searchInput: !!searchInput,
        searchResults: !!searchResults,
        chatsList: !!chatsList
    });

    const savedUsername = localStorage.getItem("messenger_username");
    const savedPassword = localStorage.getItem("messenger_password");
    if (savedUsername) authUsername.value = savedUsername;
    if (savedPassword) authPassword.value = savedPassword;

    const socket = io();
    let currentUser = null;
    let currentChatId = null;
    let currentPartner = null;
    let isRegistering = false;

    toggleAuthMode.addEventListener("click", (e) => {
        e.preventDefault();
        isRegistering = !isRegistering;
        authError.textContent = "";
        if (isRegistering) {
            authTitle.textContent = "Регистрация";
            authSubtitle.textContent = "Создайте новый аккаунт";
            authButton.textContent = "Зарегистрироваться";
            toggleText.textContent = "Уже есть аккаунт?";
            toggleAuthMode.textContent = "Войти";
        } else {
            authTitle.textContent = "Вход в ZOV-messenger";
            authSubtitle.textContent = "Введите ваше имя и пароль";
            authButton.textContent = "Войти";
            toggleText.textContent = "Нет аккаунта?";
            toggleAuthMode.textContent = "Зарегистрироваться";
        }
    });

    function tryAuth() {
        const username = authUsername.value.trim();
        const password = authPassword.value;
        if (!username) { authError.textContent = "Введите имя"; return; }
        if (!password) { authError.textContent = "Введите пароль"; return; }

        authButton.disabled = true;
        authError.textContent = "Проверка...";
        authError.style.color = "#cc0000";

        const eventType = isRegistering ? "register" : "auth";
        console.log("Отправляю событие:", eventType, { username, password });
        
        socket.emit(eventType, { username, password }, (response) => {
            console.log("Получен ответ от сервера:", response);
            authButton.disabled = false;
            if (response && response.success) {
                if (isRegistering) {
                    authError.style.color = "green";
                    authError.textContent = response.message;
                    setTimeout(() => {
                        socket.emit("auth", { username, password }, (loginResp) => {
                            console.log("Ответ на автоматический вход:", loginResp);
                            if (loginResp.success) completeLogin(username, password);
                        });
                    }, 800);
                } else {
                    completeLogin(username, password);
                }
            } else {
                authError.textContent = response.error || "Ошибка";
                authPassword.value = "";
                authPassword.focus();
            }
        });
    }

    function completeLogin(username, password) {
        currentUser = username;
        currentUserName.textContent = username;
        localStorage.setItem("messenger_username", username);
        localStorage.setItem("messenger_password", password);
        authModal.style.display = "none";
        messenger.style.display = "flex";
        console.log("Вход выполнен, загружаю список чатов");
        loadChatsList();
    }

    function logout() {
        currentUser = null;
        currentChatId = null;
        currentPartner = null;
        messenger.style.display = "none";
        authModal.style.display = "flex";
        authPassword.value = "";
        authError.textContent = "";
        chatsList.innerHTML = "";
        messagesArea.innerHTML = "";
        chatActive.style.display = "none";
        chatPlaceholder.style.display = "flex";
    }

    authButton.addEventListener("click", tryAuth);
    authUsername.addEventListener("keypress", (e) => { if (e.key === "Enter") tryAuth(); });
    authPassword.addEventListener("keypress", (e) => { if (e.key === "Enter") tryAuth(); });
    logoutButton.addEventListener("click", logout);

    function loadChatsList() {
        console.log("Запрашиваю список чатов");
        socket.emit("getChatsList", {}, (response) => {
            console.log("Получен список чатов:", response);
            if (response && response.success) renderChatsList(response.chats);
        });
    }

    function renderChatsList(chats) {
        console.log("Рендерю список чатов:", chats);
        chatsList.innerHTML = "";
        if (chats.length === 0) {
            chatsList.innerHTML = '<div class="empty-chats">У вас пока нет чатов.<br>Используйте поиск, чтобы найти собеседника.</div>';
            return;
        }
        chats.forEach(chat => {
            const item = document.createElement("div");
            item.className = "chat-item";
            if (chat.chatId === currentChatId) item.classList.add("active");

            const avatar = document.createElement("div");
            avatar.className = "search-avatar";
            avatar.textContent = chat.partner.charAt(0).toUpperCase();

            const info = document.createElement("div");
            info.className = "chat-info";
            const name = document.createElement("div");
            name.className = "chat-name";
            name.textContent = chat.partner;
            const last = document.createElement("div");
            last.className = "chat-last";
            if (chat.lastMessage) {
                last.textContent = chat.lastMessage.image ? "📷 Изображение" : (chat.lastMessage.text || "");
            } else {
                last.textContent = "Нет сообщений";
            }
            info.appendChild(name);
            info.appendChild(last);

            item.appendChild(avatar);
            item.appendChild(info);

            if (chat.lastMessage && chat.lastMessage.timestamp) {
                const time = document.createElement("div");
                time.className = "chat-time";
                time.textContent = chat.lastMessage.timestamp;
                item.appendChild(time);
            }

            item.addEventListener("click", () => openChatById(chat.chatId, chat.partner));
            chatsList.appendChild(item);
        });
    }

    let searchTimeout = null;
    searchInput.addEventListener("input", () => {
        console.log("Ввод в поиск:", searchInput.value);
        clearTimeout(searchTimeout);
        const query = searchInput.value.trim();
        if (!query) {
            console.log("Пустой запрос, скрываю результаты");
            searchResults.style.display = "none";
            searchResults.innerHTML = "";
            return;
        }
        searchTimeout = setTimeout(() => {
            console.log("Отправляю запрос поиска:", query);
            socket.emit("searchUsers", { query }, (response) => {
                console.log("Получен ответ поиска:", response);
                if (response && response.success) renderSearchResults(response.users);
            });
        }, 300);
    });

    function renderSearchResults(users) {
        console.log("Рендерю результаты поиска:", users);
        searchResults.innerHTML = "";
        if (users.length === 0) {
            searchResults.innerHTML = '<div class="search-item" style="color:#999;cursor:default;">Никого не найдено</div>';
        } else {
            users.forEach(username => {
                const item = document.createElement("div");
                item.className = "search-item";
                const avatar = document.createElement("div");
                avatar.className = "search-avatar";
                avatar.textContent = username.charAt(0).toUpperCase();
                const name = document.createElement("div");
                name.textContent = username;
                item.appendChild(avatar);
                item.appendChild(name);
                item.addEventListener("click", () => {
                    console.log("Клик по пользователю:", username);
                    searchInput.value = "";
                    searchResults.style.display = "none";
                    openChatWithUser(username);
                });
                searchResults.appendChild(item);
            });
        }
        searchResults.style.display = "block";
    }

    function openChatWithUser(partner) {
        console.log("Открываю чат с пользователем:", partner);
        socket.emit("openChatWith", { partner }, (response) => {
            console.log("Ответ на открытие чата:", response);
            if (!response.success) {
                alert(response.error || "Ошибка");
                return;
            }
            currentChatId = response.chatId;
            currentPartner = response.partner;
            showChat(response.partner, response.messages);
            loadChatsList();
        });
    }

    function openChatById(chatId, partner) {
        console.log("Открываю чат по ID:", chatId);
        socket.emit("openChat", { chatId }, (response) => {
            console.log("Ответ на открытие чата по ID:", response);
            if (!response.success) return;
            currentChatId = response.chatId;
            currentPartner = response.partner;
            showChat(response.partner, response.messages);
            document.querySelectorAll(".chat-item").forEach(el => el.classList.remove("active"));
            document.querySelectorAll(".chat-item").forEach(el => {
                if (el.querySelector(".chat-name")?.textContent === partner) el.classList.add("active");
            });
        });
    }

    function showChat(partner, messages) {
        console.log("Показываю чат с", partner, "сообщений:", messages.length);
        chatPlaceholder.style.display = "none";
        chatActive.style.display = "flex";
        chatPartnerName.textContent = partner;
        messagesArea.innerHTML = "";
        messages.forEach(msg => addMessageToChat(msg));
        messageInput.focus();
    }

    function sendMessage() {
        const text = messageInput.value.trim();
        if (!text || !currentChatId) return;
        console.log("Отправляю сообщение в чат:", currentChatId);
        socket.emit("sendMessage", { chatId: currentChatId, text });
        messageInput.value = "";
    }

    function sendImage(file) {
        if (!currentChatId) return;
        if (file.size > 2 * 1024 * 1024) {
            alert("Файл слишком большой. Максимум 2MB");
            return;
        }
        const reader = new FileReader();
        reader.onload = (e) => {
            const img = new Image();
            img.onload = () => {
                const canvas = document.createElement("canvas");
                let width = img.width, height = img.height;
                const MAX_WIDTH = 800, MAX_HEIGHT = 600;
                if (width > height) {
                    if (width > MAX_WIDTH) { height *= MAX_WIDTH / width; width = MAX_WIDTH; }
                } else {
                    if (height > MAX_HEIGHT) { width *= MAX_HEIGHT / height; height = MAX_HEIGHT; }
                }
                canvas.width = width;
                canvas.height = height;
                canvas.getContext("2d").drawImage(img, 0, 0, width, height);
                const compressed = canvas.toDataURL("image/jpeg", 0.7);
                socket.emit("sendMessage", { chatId: currentChatId, image: compressed });
            };
            img.src = e.target.result;
        };
        reader.readAsDataURL(file);
    }

    function addMessageToChat(msg) {
        const messageDiv = document.createElement("div");
        messageDiv.classList.add("message");
        if (msg.from !== currentUser) messageDiv.classList.add("incoming");

        if (msg.from !== currentUser) {
            const u = document.createElement("div");
            u.className = "message-username";
            u.textContent = msg.from;
            messageDiv.appendChild(u);
        }
        if (msg.text) {
            const t = document.createElement("div");
            t.textContent = msg.text;
            messageDiv.appendChild(t);
        }
        if (msg.image) {
            const img = document.createElement("img");
            img.src = msg.image;
            img.className = "message-image";
            img.onclick = () => window.open(msg.image, "_blank");
            messageDiv.appendChild(img);
        }
        if (msg.timestamp) {
            const time = document.createElement("div");
            time.className = "message-time";
            time.textContent = msg.timestamp;
            messageDiv.appendChild(time);
        }
        messagesArea.appendChild(messageDiv);
        messagesArea.scrollTop = messagesArea.scrollHeight;
    }

    socket.on("newMessage", (data) => {
        console.log("Получено новое сообщение:", data);
        if (data.chatId === currentChatId) addMessageToChat(data.message);
        loadChatsList();
    });

    socket.on("chatUpdated", () => {
        console.log("Чат обновлен, перезагружаю список");
        loadChatsList();
    });

    sendButton.addEventListener("click", sendMessage);
    messageInput.addEventListener("keypress", (e) => { if (e.key === "Enter") sendMessage(); });
    attachButton.addEventListener("click", () => fileInput.click());
    fileInput.addEventListener("change", (e) => {
        const file = e.target.files[0];
        if (file) {
            sendImage(file);
            fileInput.value = "";
        }
    });
});