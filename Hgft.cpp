#include <iostream>

// Типы данных для удобства
using INT = int;
using BOOL = bool;
using VOID = void;
const BOOL TRUE = true;
const BOOL FALSE = false;

struct rbtree {
    enum rbcolor { eRED, eBLACK };

    struct node {
        INT Key;
        rbcolor Color;
        node *Less, *More; // Левый и правый потомки
        node *Parent;

        node(INT NewKey, rbcolor NewColor = eRED, 
             node* NewLess = nullptr, node* NewMore = nullptr, node* NewParent = nullptr)
            : Key(NewKey), Color(NewColor), Less(NewLess), More(NewMore), Parent(NewParent) {}
    };

    node* Root;

    rbtree() : Root(nullptr) {}
    
    ~rbtree() { Clear(&Root); }

    // Запрещаем копирование
    rbtree(const rbtree&) = delete;
    rbtree& operator=(const rbtree&) = delete;

    // Очистка дерева
    VOID Clear(node** T = nullptr) {
        if (T == nullptr) Clear(&Root);
        else if (*T != nullptr) {
            Clear(&(*T)->Less);
            Clear(&(*T)->More);
            delete *T;
            *T = nullptr;
        }
    }

    // Проверка на черный цвет (nullptr считается черным листом)
    BOOL IsBlack(node* Nd) {
        return Nd == nullptr || Nd->Color == eBLACK;
    }

    // Левый поворот
    VOID LeftRotate(node* X) {
        node* Y = X->More;
        X->More = Y->Less;
        if (Y->Less != nullptr) Y->Less->Parent = X;

        Y->Parent = X->Parent;
        if (X->Parent == nullptr) Root = Y;
        else if (X == X->Parent->Less) X->Parent->Less = Y;
        else X->Parent->More = Y;

        Y->Less = X;
        X->Parent = Y;
    }

    // Правый поворот (зеркальное отражение левого)
    VOID RightRotate(node* Y) {
        node* X = Y->Less;
        Y->Less = X->More;
        if (X->More != nullptr) X->More->Parent = Y;

        X->Parent = Y->Parent;
        if (Y->Parent == nullptr) Root = X;
        else if (Y == Y->Parent->Less) Y->Parent->Less = X;
        else Y->Parent->More = X;

        X->More = Y;
        Y->Parent = X;
    }

    // Логика балансировки при вставке
    VOID CorrectInsert(node* Z) {
        // Пока родитель Z красный (нарушено свойство 4)
        while (Z->Parent != nullptr && Z->Parent->Color == eRED) {
            node* Grandparent = Z->Parent->Parent;
            if (Grandparent == nullptr) break;

            // Если родитель — левый сын деда
            if (Z->Parent == Grandparent->Less) {
                node* Uncle = Grandparent->More; // Дядя — правый сын деда

                // Случай 1: Дядя КРАСНЫЙ
                if (!IsBlack(Uncle)) {
                    Z->Parent->Color = eBLACK;
                    Uncle->Color = eBLACK;
                    Grandparent->Color = eRED;
                    Z = Grandparent; // Поднимаемся выше для проверки
                } 
                // Дядя ЧЕРНЫЙ (или его нет)
                else {
                    // Случай 2: Z — правый сын (треугольник), делаем поворот
                    if (Z == Z->Parent->More) {
                        Z = Z->Parent;
                        LeftRotate(Z);
                    }
                    // Случай 3: Z — левый сын (линия), красим и делаем поворот деда
                    Z->Parent->Color = eBLACK;
                    Grandparent->Color = eRED;
                    RightRotate(Grandparent);
                }
            } 
            // Зеркальный случай: если родитель — правый сын деда
            else {
                node* Uncle = Grandparent->Less;

                if (!IsBlack(Uncle)) {
                    Z->Parent->Color = eBLACK;
                    Uncle->Color = eBLACK;
                    Grandparent->Color = eRED;
                    Z = Grandparent;
                } else {
                    if (Z == Z->Parent->Less) {
                        Z = Z->Parent;
                        RightRotate(Z);
                    }
                    Z->Parent->Color = eBLACK;
                    Grandparent->Color = eRED;
                    LeftRotate(Grandparent);
                }
            }
        }
        // Свойство 2: Корень всегда должен быть черным
        Root->Color = eBLACK;
    }

    // Вставка нового узла
    VOID Insert(INT Key) {
        node* NewNode = new node(Key);
        node* Parent = nullptr;
        node* TreePtr = Root;

        // Ищем место для вставки
        while (TreePtr != nullptr) {
            if (Key == TreePtr->Key) {
                delete NewNode; // Ключ уже есть, дубликаты не вставляем
                return;
            }
            Parent = TreePtr;
            TreePtr = (NewNode->Key < TreePtr->Key) ? TreePtr->Less : TreePtr->More;
        }

        // Привязываем новый узел
        NewNode->Parent = Parent;
        if (Parent == nullptr) {
            Root = NewNode; // Дерево было пустым
        } else if (NewNode->Key < Parent->Key) {
            Parent->Less = NewNode;
        } else {
            Parent->More = NewNode;
        }

        // Запускаем балансировку
        CorrectInsert(NewNode);
    }

    // Поиск узла по ключу
    node* Search(INT Key) {
        node* Current = Root;
        while (Current != nullptr) {
            if (Key == Current->Key) return Current;
            Current = (Key < Current->Key) ? Current->Less : Current->More;
        }
        return nullptr;
    }

    // Вывод дерева в консоль
    VOID Put(node* T) {
        if (T == nullptr) {
            std::cout << "NIL ";
        } else {
            std::cout << T->Key << (T->Color == eBLACK ? "[B]" : "[R]") << "(";
            Put(T->Less);
            std::cout << ",";
            Put(T->More);
            std::cout << ") ";
        }
    }
    
    VOID Put() {
        Put(Root);
        std::cout << std::endl;
    }

    // Проверка высоты дерева
    INT GetHeight() {
        return GetHeightHelper(Root);
    }

private:
    INT GetHeightHelper(node* T) {
        if (T == nullptr) return 0;
        return 1 + std::max(GetHeightHelper(T->Less), GetHeightHelper(T->More));
    }
};

int main() {
    rbtree tree;
    
    std::cout << "=== Демонстрация Красно-Черного Дерева ===" << std::endl;
    std::cout << std::endl;
    
    // Последовательная вставка от 1 до 8
    std::cout << "Вставляем числа от 1 до 8:" << std::endl;
    for (int i = 1; i <= 8; ++i) {
        tree.Insert(i);
        std::cout << "После вставки " << i << ": ";
        tree.Put();
    }
    
    std::cout << std::endl;
    std::cout << "Высота дерева: " << tree.GetHeight() << std::endl;
    std::cout << std::endl;
    
    // Проверка поиска
    std::cout << "Поиск элементов:" << std::endl;
    for (int i = 1; i <= 10; ++i) {
        if (tree.Search(i)) {
            std::cout << "Элемент " << i << " найден" << std::endl;
        } else {
            std::cout << "Элемент " << i << " НЕ найден" << std::endl;
        }
    }
    
    std::cout << std::endl;
    std::cout << "Финальная структура дерева:" << std::endl;
    tree.Put();
    
    return 0;
}
