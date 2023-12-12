//Лаба №17 “Операции над БНП: поиск, добавление, удаление”
//Дерево вводится в программу в формате линейно-скобочной записи.
// Затем появляется меню, в котором доступна операция добавления, удаления и поиска вершины БДП.
// После выполнения операции программа должна возвращаться снова в меню.
// При выходе из него до завершения программы на экран должно быть выведено БДН любым способом (в виде линейно-скобочной записи или в графической форме).

#include <iostream>
#include <fstream>
#include <string>
#include <stack>

struct Elem {
    int data;
    int level;
    Elem* left;
    Elem* right;
    Elem* parent;
};

//Создание элемента
Elem* MAKE(int data, Elem* p)
{
    Elem* q = new Elem;
    q->data = data;
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;
    return q;
}

//Добавление элемента в дерево
void ADD(int data, Elem*& root)
{
    if (root == nullptr)
    {
        root = MAKE(data, nullptr);
        return;
    }
    Elem* v = root;
    while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))
    {
        if (data < v->data)
            v = v->left;
        else
            v = v->right;
    }
    if (data == v->data)
        return;
    Elem* u = MAKE(data, v);
    if (data < v->data)
        v->left = u;
    else if (data > v->data)
        v->right = u;
}
//Проход по дереву
void PASS(Elem* v)
{
    if (v == nullptr)
        return;
    PASS(v->left);
    std::cout << v->data << " ";
    PASS(v->right);
}
//поиск в дереве элемента
Elem* SEARCH(int data, Elem* v) {
    if (v == nullptr)
        return v;
    if (v->data == data)
        return v;
    if (data < v->data)
        return SEARCH(data, v->left);
    else  if (data > v->data)
        return SEARCH(data, v->right);
}

//удаление определенного элемента в дереве
void DELETE(int data, Elem*& root)
{
    Elem* u = SEARCH(data, root);
    if (u == nullptr)
        return;
    if (u->left == nullptr && u->right == nullptr && u == root)
    {
        delete root;
        root = nullptr;
        return;
    }
    if (u->left == nullptr && u->right != nullptr && u == root)
    {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    if (u->left != nullptr && u->right == nullptr && u == root)
    {
        Elem* t = u->left;
        while (t->right != nullptr)
            t = t->right;
        u->data = t->data;
        u = t;
    }
    if (u->left != nullptr && u->right != nullptr)
    {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    Elem* t;
    if (u->left == nullptr)
        t = u->right;
    else
        t = u->left;
    if (u->parent->left == u)
        u->parent->left = t;
    else
        u->parent->right = t;
    if (t != nullptr)
        t->parent = u->parent;
    delete u;
}
//Добавление скобочной записи в виде БДП (Бинарное дерево поиска)
void ADD_BY_PARENTHESIS(int data, Elem*& root, bool inLeft)
{
    Elem* v = root;
    Elem* u = MAKE(data, v);
    if (inLeft)
        v->left = u;
    else
        v->right = u;
}
//Заполнение дерева скобочной записью
void FILL_TREE(std::string& bracketEntry, int& i, Elem*& root)
{
    int value = 0;
    while (bracketEntry[i] != '\0')
    {
        switch (bracketEntry[i])
        {
            case '(':
            {
                i++;
                value = 0;
                while ((bracketEntry[i] >= '0') && (bracketEntry[i] <= '9'))
                {
                    value = value * 10 + bracketEntry[i] - '0';
                    i++;
                }

                if (value != 0)
                {
                    ADD_BY_PARENTHESIS(value, root, true);
                    if (bracketEntry[i] == '(')
                        FILL_TREE(bracketEntry, i, root->left);
                }
                value = 0;
                break;
            }
            case ',':
            {
                i++;
                value = 0;
                while ((bracketEntry[i] >= '0') && (bracketEntry[i] <= '9'))
                {
                    value = value * 10 + bracketEntry[i] - '0';
                    i++;
                }

                if (value != 0)
                {
                    ADD_BY_PARENTHESIS(value, root, false);
                    if (bracketEntry[i] == '(')
                        FILL_TREE(bracketEntry, i, root->right);
                }
                value = 0;
                break;
            }
            case ')':
                i++;
                return;
            default:
                break;
        }
    }
}

//Определение глубины элемента в дереве
int DEPTH(int data, Elem* v, int k)
{
    if (v == nullptr)
    {
        return -15;
    }
    if (v->data == data)
    {
        return k;
    }
    if (data < v->data)
        return DEPTH(data, v->left, k + 1);
    if (data > v->data)
        return DEPTH(data, v->right, k + 1);
}
//Очистка памяти, выделенной под дерево.
void CLEAR(Elem*& v) {
    if (v == nullptr)
        return;
    CLEAR(v->left);
    CLEAR(v->right);
    delete v;
    v = nullptr;
}
//Прямой
void straightOrder(Elem* root)
{
    if (root == nullptr)
        return;
    std::cout << root->data << std::endl;

    straightOrder(root->left);
    straightOrder(root->right);
}

//Вывод элементов в консоль
void PRINT(Elem* root)
{
    if (root == nullptr)
    {
        std::cout << std::endl;
        return;
    }
    PRINT(root->right);
    for (int i = root->level; i > 0; i--)
    {
        std::cout << '\n';
    }
    std::cout << root->data << std::endl;
    PRINT(root->left);
}

void menu(Elem* root)
{
    std::cout << "Главное меню:" << std::endl;
    bool work = false;
    int action;
    while (!work)
    {
        std::cout << "Выберите операцию: " << std::endl;
        std::cout << "Добавление(1)\n"
                     "Удаление(2)\n"
                     "Поиск(3)\n"
                     "Выход(4)" << std::endl;
        std::cin >> action;
        switch (action)
        {
            case 1:
            {
                int value;
                std::cout << "Введите значение для добавления: ";
                std::cin >> value;
                ADD(value, root);
                break;
            }
            case 2:
            {
                int value;
                std::cout << "Введите значение для стирания: ";
                std::cin >> value;
                DELETE(value, root);
                break;
            }
            case 3:
            {
                int value;
                std::cout << "Введите значение, которое вам нужно найти: ";
                std::cin >> value;

                Elem* e = nullptr;
                e = SEARCH(value, root);
                if (e == nullptr)
                    std::cout << "Значение не найдено" << std::endl;
                else
                    std::cout << "Значение найдено" << std::endl;
                break;
            }
            case 4:
                work = true;
                break;
            default:
                break;
        }
    }
    //PRINT(root);
}

int main()
{
    Elem* root = nullptr;//начальное значение корня
    std::string bracketEntry;//создание скобочной записи
    std::cout << "Введите линейно-скобочную запись:" << std::endl;
    std::cin >> bracketEntry;

    int digit = 0;
    int i = 0;
    while ((bracketEntry[i] >= '0') && (bracketEntry[i] <= '9'))
    {
        digit += digit * 10 + bracketEntry[i] - '0';
        i++;
    }

    ADD(digit, root);
    FILL_TREE(bracketEntry, i, root);

    //PASS(root);
    std::cout << "----------" << std::endl;
    menu(root);
    straightOrder(root);
    CLEAR(root);
    return 0;
}

//8(3(1,6(4,7)),10(,14(13,)))