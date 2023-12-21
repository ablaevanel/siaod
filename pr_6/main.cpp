#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int V1 = 6; // число вершин

// матрица смежности графа
vector<vector<int>> G1 = {
        {0, 7, 0, 2, 0, 4},
        {7, 0, 1, 2, 0, 0},
        {0, 1, 0, 2, 3, 0},
        {2, 2, 2, 0, 6, 1},
        {0, 0, 3, 6, 0, 8},
        {4, 0, 0, 1, 8, 0}
};

void graph(int V, vector<vector<int>> &G){
    int n_edge = 0; // количество ребер
    int selected[V]; // массив обработанных вершин
    // изначально все необработаны:
    memset(selected, false, sizeof(selected));
    selected[0] = true; // посещаем начальную вершину
    int x, y;
    cout << "Edge" << " : " << "Weight" << endl;
    while(n_edge < V - 1){
        int min = INT_MAX;
        x = 0; y = 0;
        for (int i = 0; i < V; i++){
            if (selected[i]){
                for (int j = 0; j < V; j++){
                    if (!selected[j] && G[i][j]){
                        if (min > G[i][j]){
                            min = G[i][j];
                            x = i; y = j;
                        }
                    }
                }
            }
        }
        cout << ++x << " - " << ++y << " : " << G[--x][--y] << endl;
        selected[y] = true;
        n_edge++;
    }
}
int main() {
    system("chcp 65001");
    int V, choice;
    cout << "Построение остовного дерева алгоритмом Прима" << endl;
    cout << "Ввести граф с клавиатуры - 1" << endl;
    cout << "Использовать тестовый граф - 2" << endl;
    cin >> choice;
    if (choice == 1){
        cout << "Введите количество вершин графа:" << endl;
        cin >> V;
        vector<vector<int>> G2(V, vector<int>(V, 0));
        cout << "Введите матрицу смежности графа:" << endl;
        for (int i = 0; i < V; i++){
            for (int j = 0; j < V; j++){
                cin >> G2[i][j];
            }
        }
        graph(V, G2);
    } else {
        graph(V1, G1);
    }
    return 0;
}
