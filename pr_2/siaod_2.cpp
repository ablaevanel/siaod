#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

vector<vector<string>> pointer_table;
vector<vector<string>> table;

void create_text_file(int n)
{
    pointer_table.clear();
    ofstream fout("text.txt");
    srand(time(NULL));
    int x = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            x += (rand() % 10) * pow(10, j);
        }
        x += (1 + (rand() % 9)) * pow(10, 6);
        fout << setw(7) << x << ' ' << setw(9) << "FIO#" + to_string(rand() % n) << ' ' << setw(11) << "adress#" + to_string(rand() % n) << endl;
        x = 0;
    }
    fout.close();
}

void create_bin_file()
{
    ifstream pTextFile("text.txt", ios::in);
    ofstream pBinaryFile("text.bin", ios::out | ios::binary);
    string str;
    while (!pTextFile.eof())
    {
        getline(pTextFile, str);
        pBinaryFile.write(str.c_str(), str.size());
    }
    pTextFile.close();
    pBinaryFile.close();
    printf("Текстовый файл конвертировался в бинарный\n");
}

void create_table()
{
    ifstream pBinaryFile("text.bin", ios::in | ios::binary);
    char buffer[29];
    int idx = 0;
    while (!pBinaryFile.eof())
    {
        pBinaryFile.read(buffer, 29);
        stringstream ss(buffer);
        string s;
        vector<string> line;
        for (int i = 0; i < 3; i++)
        {
            getline(ss, s, ' ');
            if (i == 0)
                line.push_back(s);
        }
        line.push_back(to_string(idx * 29));
        pointer_table.push_back(line);
        idx++;
    }
    pointer_table.pop_back();
    pBinaryFile.close();
}

void create_table_2()
{
    ifstream pBinaryFile("text.bin", ios::in | ios::binary);
    char buffer[29];
    int idx = 0;
    while (!pBinaryFile.eof())
    {
        pBinaryFile.read(buffer, 29);
        stringstream ss(buffer);
        string s;
        vector<string> line;
        for (int i = 0; i < 3; i++)
        {
            getline(ss, s, ' ');
            if (i == 0)
                line.push_back(s);
        }
        line.push_back(to_string(idx * 29));
        table.push_back(line);
        idx++;
    }
    table.pop_back();
    pBinaryFile.close();
}

void read_line(int num)
{
    ifstream pBinaryFile("text.bin", ios::in | ios::binary);
    ifstream pTextFile("text.txt");
    char buffer[29] = "";
    string str;
    for (int i = 0; i < num - 1; i++) {
        pBinaryFile.read(buffer, 29);
        getline(pTextFile, str);
    }  
    pBinaryFile.read(buffer, 29);
    getline(pTextFile, str);
    cout << str << '\n';
    pBinaryFile.close();
    pTextFile.close();
}

void print_table()
{
    ifstream fin;
    fin.open("text.txt");
    string str;
    while (!fin.eof()) {
        getline(fin, str);
        cout << str << endl;
    }
    fin.close();
}

void print_pointer_table()
{
    for (int i = 0; i < pointer_table.size(); i++)
    {
        cout << setw(7) << pointer_table[i][0] << ' '
            << setw(6) << pointer_table[i][1] << '\n';
    }
}

void linear_search(string key)
{
    string s;
    int i = 1;
    for (auto line : table)
    {
        if (line[0] == key)
        {
            read_line(i);
            return;
        }
        i++;
    }
    cout << "Запись с заданным ключом не найдена\n";
}

string get_key(int i)
{
    return pointer_table[i][0];
}

string get_link(string str)
{
    for (auto line : pointer_table) {
        if (line[0] == str) {
            return line[1];
        }
    }
}

string get_string(string link){
    ifstream fin;
    fin.open("text.txt");
    string str;
    for (int i = 0; i < stoi(link) / 29; i++) {
        getline(fin, str);
    }
    getline(fin, str);
    return str;
}

void bin_search(string key)
{
    sort(pointer_table.begin(), pointer_table.end());
    int left = 0, right = pointer_table.size();
    int mid;
    string keyFromTable;
    string link, str;
    while (right - left > 1)
    {
        mid = (left + right) / 2;
        keyFromTable = get_key(mid);
        if (key < keyFromTable)
            right = mid;
        else if (key > keyFromTable)
            left = mid;
        else if (key == keyFromTable)
        {
            link = get_link(key);
            cout << get_string(link) << endl;
            return;
        }
    }
    cout << "Запись с заданным ключом не найдена\n";
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int task_num;
    int length;
    int start, finish;
    bool is_agree;
    string account_number;
    do {
        cout << "Выберите задание: 1 2 3 (0 - завершить программу) ";
        cin >> task_num;
        switch (task_num) {
        case 1:
            cout << "---СОЗДАНИЕ ДВОИЧНОГО ФАЙЛА---\n";
            cout << "Введите длину файла: ";
            cin >> length;
            while (length <= 0)
            {
                cout << "Введите длину файла: ";
                cin >> length;
            }
            create_text_file(length);
            create_bin_file();
            create_table();
            create_table_2();
            cout << "Вывести таблицу ключей и ссылок? 1-Да 0-Нет" << endl;
            cin >> is_agree;
            if (is_agree) print_pointer_table();
            cout << "Вывести таблицу записей? 1-Да 0-Нет" << endl;
            cin >> is_agree;
            if (is_agree) print_table();
            break;
        case 2:
            cout << "---ЛИНЕЙНЫЙ ПОИСК---\n";
            cout << "Введите номер счета в банке: ";
            cin >> account_number;
            start = clock();
            linear_search(account_number);
            finish = clock();
            cout << "Время: " << static_cast<float>(finish - start) / CLOCKS_PER_SEC << " s" << endl;
            break;
        case 3:
            cout << "---БИНАРНЫЙ ПОИСК---\n";
            cout << "Введите номер счета в банке: ";
            cin >> account_number;
            start = clock();
            bin_search(account_number);
            finish = clock();
            cout << "Время: " << static_cast<float>(finish - start) / CLOCKS_PER_SEC << " s" << endl;
        }
    } while (task_num != 0);
    return 0;
}