#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <Windows.h>
#include <map>

using namespace std;

void createArray() {
	vector <string> a;
	string s;
	cout << "Введите предложение:" << endl;
	getline(cin, s);
	string word;
	istringstream ss(s);
	while (ss >> word) {
		if (word[word.length() - 1] == '.' || word[word.length() - 1] == ',' || word[word.length() - 1] == ':'
			|| word[word.length() - 1] == ';' || word[word.length() - 1] == '!' || word[word.length() - 1] == '?')
			word.erase(word.length() - 1, word.length());

		a.push_back(word);
	}
	for (string l : a)
		cout << l << endl;
}
bool findArray(char s, vector<char> array) {
	auto it = find(array.begin(), array.end(), s);

	if (it != array.end())
		return true;
	else
		return false;
}
void BoyerMoore() {

	string sentences, pattern;
	cout << "Введите предложение:" << endl;
	getline(cin, sentences);
	cout << "Введите искомую подстроку:" << endl;
	getline(cin, pattern);

	vector<char> uniq;
	int len = pattern.length();
	map<char, unsigned> shift;

	for (int i = len - 2; i >= 0; i--) {
		if (findArray(pattern[i], uniq))
			continue;

		shift[pattern[i]] = len - i - 1;
		uniq.push_back(pattern[i]);
	}

	if (findArray(pattern[len - 1], uniq))
		shift[pattern[len - 1]] = len;

	shift['*'] = len;

	int len_s = sentences.length();
	if (len_s < len)
		return;

	int i = len - 1, off, k;
	while (i < len_s) {
		k = 0;
		for (int j = len - 1; j >= 0; j--) {
			if (sentences[i - k] != pattern[j]) {
				if (j == len - 1) {
					if (shift.count(sentences[i]) == 1)
						off = shift[sentences[i]];
					else
						off = shift['*'];
				}
				else
					off = shift[pattern[j]];

				i += off;
				break;
			}
			k++;

			if (j == 0) {
				cout << "Индекс вхождения подстроки: " << i - k + 1 << endl;
				i++;
			}
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	createArray();
	BoyerMoore();
}