//В качестве входной информации для следующих лабораторных работ вводится символьная строка
// (бинарное дерево) с помощью линейно-скобочной записи.
//Структура бинарного дерева создается с помощь динамических переменных.
/// “Рекурсивные обходы (прямой, центральный, концевой)” и “Не рекурсивный прямой обход"
///15-16 лабы
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
struct Elem{
    int data;
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

//Добавление скобочной записи в виде БДП
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
void CLEAR(Elem*& v)
{
    if (v == nullptr)
        return;
    CLEAR(v->left);
    CLEAR(v->right);
    delete v;
    v = nullptr;
}
//Рекурсивные обходы (прямой, центральный, концевой)
//Прямой
void straightOrder(Elem* root)
{
    if (root == nullptr)
        return;
    std::cout << root->data << " ";
    straightOrder(root->left);
    straightOrder(root->right);
}
//Центральный (симметричный)
void centralOrder(Elem* root)
{
    if (root == nullptr)
        return;
    centralOrder(root->left);
    std::cout << root->data << " ";
    centralOrder(root->right);
}
//Концевой (обратный)
void endOrder(Elem* root)
{
    if (root == nullptr)
        return;
    endOrder(root->left);
    endOrder(root->right);
    std::cout << root->data << " ";

}
//Нерекурсивный обход
void nonRecursiveOrder(Elem* root)
{
    if (root == nullptr)
        return;
    std::stack<Elem*> stack;
    stack.push(root);//добавляем в стек корень

    while (!stack.empty())
    {
        Elem* node = stack.top();
        stack.pop();
        std::cout << node->data << " ";

        if (node->left != nullptr) //проверка существования левого поддерева у узла node.
        {
            stack.push(node->left);
        }
        if (node->right != nullptr) //проверка существования правого поддерева у узла node.
        {
            stack.push(node->right);
        }
    }
}

int main()
{
    Elem* root = nullptr;//начальное значение корня
    std::string bracketEntry;//создание скобочной записи
    std::cout << "Введите скобочную запись дерева:" << std::endl;
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
    //std::cout << std::endl;

    std::cout << "------Рекурсивный обход (прямой)------" << std::endl;

    straightOrder(root);
    std::cout<<"\n";

    std::cout << "------Рекурсивный обход (центральный)------" << std::endl;

    centralOrder(root);
    std::cout<<"\n";

    std::cout << "------Рекурсивный обход (концевой)------" << std::endl;

    endOrder(root);
    std::cout<<"\n";

    std::cout << "------Нерекурсивный обход------" << std::endl;

    nonRecursiveOrder(root);
    CLEAR(root);
    return 0;
}

//8(3(1,6(4,7)),10(,14(13,)))
//6(5(3(2,4),8(7,9)))