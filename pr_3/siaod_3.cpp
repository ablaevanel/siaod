#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

struct bankAccount {
    long long account_number;
    string name;
    string address;

    bankAccount(long long account_number, string name, string address) {
        this->account_number = account_number;
        this->name = name;
        this->address = address;
    }
};

class HashTable {
public:
    int num = 0;
    int size;
    list<bankAccount*>* table;

    HashTable(int initialSize) {
        size = initialSize;
        table = new list<bankAccount*>[initialSize];
    }

    int hashFunction(long long key) {
        return key % size;
    }

    void resizeTable() {
        size *= 2;
        list<bankAccount*>* newTable = new list<bankAccount*>[size];

        for (int i = 0; i < size / 2; i++) {
            for (bankAccount* company : table[i]) {
                int index = hashFunction(company->account_number);

                newTable[index].push_back(company);
            }
        }

        delete[] table;

        table = newTable;
    }

    void insert(bankAccount* company) {
        if ((double)num / size > 0.75) {
            resizeTable();
        }
        num++;

        int index = hashFunction(company->account_number);

        table[index].push_back(company);
    }

    bankAccount* search(long long key) {
        int index = hashFunction(key);

        for (bankAccount* company : table[index]) {
            if (company->account_number == key) {
                return company;
            }
        }

        return nullptr;
    }

    void remove(long long key) {
        int index = hashFunction(key);

        for (auto it = table[index].begin(); it != table[index].end(); it++) {
            if ((*it)->account_number == key) {
                table[index].erase(it);
                num--;

                return;
            }
        }
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            cout << "Индекс " << i << ": ";

            for (bankAccount* company : table[i]) {
                cout << company->account_number << " " << company->name << " " << company->address << "\n";
            }

            cout << endl;
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    HashTable hashTable(8);
    long long number, key;
    string name, address;
    bankAccount* table;

    int command;

    while (true) {
        cout << "1. Добавить счет в банке;" << endl;
        cout << "2. Найти счет в банке;" << endl;
        cout << "3. Удалить счет в банке;" << endl;
        cout << "4. Вывести счета в банке;" << endl;
        cout << "5. Выход." << endl;

        cin >> command;

        switch (command) {
        case 1:
            cout << "Заполнить данные:" << endl;
            cout << "0 - вручную;" << endl;
            cout << "1 - случайным образом." << endl;

            int choice;

            cin >> choice;

            if (choice == 0) {
                cout << "Введите номер счета: ";
                cin >> number;

                cout << "Введите ФИО: ";
                cin >> name;

                cout << "Введите адресс: ";
                cin >> address;

                table = new bankAccount(number, name, address);
            }
            else {
                number = 1000000 + (rand() % 10) * pow(10, 5) + (rand() % 10) * pow(10, 4) + (rand() % 10) * pow(10, 3) + (rand() % 10) * pow(10, 2) + (rand() % 10) * 10 + (rand() % 10);
                name = "name#" + to_string(rand() % 1000);
                address = "address#" + to_string(rand() % 1000);

                table = new bankAccount(number, name, address);
            }

            hashTable.insert(table);

            cout << "Счет добавлен в банк\n";
            break;
        case 2:
            cout << "Введите ключ для поиска: ";
            cin >> key;

            table = hashTable.search(key);

            if (table != nullptr) {
                cout << "Найден счет: " << table->name << " " << table->address << "\n";
            }
            else {
                cout << "Cчет не найден\n";
            }
            break;
        case 3:
            cout << "Введите ключ для удаления: ";
            cin >> key;

            table = hashTable.search(key);

            hashTable.remove(key);

            cout << "Счет удален\n";
            break;
        case 4:
            hashTable.printTable();
            break;
        case 5:
            exit(1);
        default:
            cout << "Неправильная команда" << endl;
        }
    }

    return 0;
}