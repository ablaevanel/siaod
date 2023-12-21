#include <iostream>
using namespace std;

// Узел АВЛ дерева
struct Node {
    int key;                // Ключ
    unsigned char height;   // Высота
    Node* left;             // Левый ребенок
    Node* right;            // Правый ребенок

    // Конструктор, создающий узел
    Node(int k) {key = k; left = right = nullptr; height = 0; }
};

int get_height(Node* p) // Высота поддерева с корнем в данном узле
{
    return p ? p->height : -1;
}

int bfactor(Node* p)    // Разность между высотами левого и правого поддерева
{
    return p ? get_height(p->right) - get_height(p->left) : 0;
}

void fix_height(Node* p)    // Исправление высоты после вставки/балансировки дерева
{
    int hl = get_height(p->left);
    int hr = get_height(p->right);
    p->height = max(hl, hr) + 1;
}

void right_rotate(Node* p) {    // Правый поворот вокруг p
    swap(p->key, p->left->key);
    Node* buffer = p->right;
    p->right = p->left;
    p->left = p->right->left;
    p->right->left = p->right->right;
    p->right->right = buffer;

    fix_height(p->right);
    fix_height(p);
}

void left_rotate(Node* p) {     // Левый поворот вокруг p
    swap(p->key, p->right->key);
    Node* buffer = p->left;
    p->left = p->right;
    p->right = p->left->right;
    p->left->right = p->left->left;
    p->left->left = buffer;

    fix_height(p->left);
    fix_height(p);
}

void balance(Node* p) {     // Балансировка дерева
    if (bfactor(p) == -2) {
        if (bfactor(p->left) == 1) left_rotate(p->left);
        right_rotate(p);
    }
    else if (bfactor(p) == 2) {
        if (bfactor(p->right) == -1)right_rotate(p->right);
        left_rotate(p);
    }
}

void insert(Node* p, int k) {   // Вставка узла в дерево
    if (k < p->key) {
        if (p->left == nullptr)
            p->left = new Node(k);
        else
            insert(p->left, k);
    }
    else if (k > p->key) {
        if (p->right == nullptr)
            p->right = new Node(k);
        else
            insert(p->right, k);
    }
    else {
        printf("The key %d exists in the tree\n", k);
    }

    fix_height(p);
    balance(p);
}

void symmetric_traversal(Node* p) { // Симмертричный обход дерева
    if (!p) return;

    symmetric_traversal(p->left);
    cout << p->key << ' ';
    symmetric_traversal(p->right);
}

int get_distance(Node* root, int n) {     // Поиск расстояния между корневым узлом и заданным значением
    int h = 0;
    while(n != root->key && (root->right || root->left)){
        if (n > root->key){
            root = root->right;
            h++;
        } else if (n < root->key){
            root = root->left;
            h++;
        }
    }
    if (n == root->key){
        return h;
    } else {
        return -1;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Введите 10 элементов дерева:" << endl;
    int elem;
    cin >> elem;
    Node* root = new Node(elem);
    for (int i = 1; i <= 9; i++){
        cin >> elem;
        insert(root, elem);
    }

    cout << "Симмеричный обход дерева - 1" << endl;
    cout << "Высота дерева - 2" << endl;
    cout << "Поиск расстояния между корневым узлом и заданным значением - 3" << endl;

    int ch;
    cin >> ch;
    if (ch == 1) {
        cout << "Симмеричный обход:" << endl;
        symmetric_traversal(root);
        cout << endl;
    } else if (ch == 2){
        cout << "Высота дерева: " << get_height(root) << endl;
    } else if (ch == 3){
        int n;
        cin >> n;
        cout << "Введите значение для поиска расстояния: " ;
        cout << endl << "Расстояние между корневым узлом и заданным значением: " << get_distance(root, n) << endl;
    }
    return 0;
}