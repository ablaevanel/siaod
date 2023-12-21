#include <iostream>
#include <vector>
using namespace std;
vector<int> findLIS(vector<int> a){
    int n = a.size();
    int prev[n];
    int d[n];

    for (int i = 0; i < n; i++){
        d[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; j++){
            if (a[j] < a[i] and d[j] + 1 > d[i]) {
                d[i] = d[j] + 1;
                prev[i] = j;
            }
        }
    }

    int pos = 0;
    int length = d[0];
    for (int i = 0; i < n; i++){
        if (d[i] > length){
            pos = i;
            length = d[i];
        }
    }

    vector<int> answer;
    vector<int> result;

    while (pos != -1){
        answer.push_back(a[pos]);
        pos = prev[pos];
    }

    for(int i = answer.size()-1; i >= 0; i--){
        result.push_back(answer[i]);
    }

    return result;
}

int main() {
    vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    vector<int> result = findLIS(nums);
    for (int num : result) {
        cout << num << " ";
    }
    return 0;
}
