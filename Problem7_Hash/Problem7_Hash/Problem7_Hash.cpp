#include <iostream>
#include <fstream>
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end

using namespace std;

struct NODE {
	int key;
	string data;
	NODE* next;
};

struct HASH {
	NODE** a; //hashing table
	int m;//size
};

HASH* initialize(int m) {
	HASH* h = new HASH;
	h->a = new NODE * [m];
	for (int i = 0; i < m; i++)
		h->a[i] = NULL;
	h->m = m;
	return h;
}

int hashing(int key, int m) {
	return key % m;
}

void insert(HASH* h, int k, string val, int key) {
	NODE* tmp;
	tmp = new NODE;
	tmp->data = val;
	tmp->key = key;
	tmp->next = NULL;
	tmp->next = h->a[k];
	h->a[k] = tmp;
}

void display(HASH* h) {
	cout << "Hashing table: index: (key,data)..." << endl;
	for (int k = 0; k < h->m; k++) {
		cout << k << ": ";
		for (NODE* cur = h->a[k]; cur != NULL; cur = cur->next) {
			cout << "(" << cur->key << "," << cur->data << ");\t";
		}
		cout << endl;
	}
}

NODE* search(HASH* h, string val, int N) {
	for (int i = 0; i < N; i++) {
		NODE* cur = h->a[i];
		while (cur != NULL) {
			if (cur->data == val) {
				return cur;
			}
			cur = cur->next;
		}
	}
	return NULL;
}

string* CheckText(string txt, HASH* h, int N) {
	string x = "";
	string* res = new string[N];
	NODE* cur;
	int i = 0;
	ifstream myReadFile;
	myReadFile.open(txt);
	while(myReadFile >> x) {
		cur = search(h, x, N);
		if (cur == NULL) {
			res[i] = x;
			i++;
		}
	}
	return res;
}

int main()
{
	HASH* h;
	int N = 9;
	int k;
	//int key;
	string val;
	h = initialize(N);
	string x = "";
	string* res = new string[N];

	ifstream myReadFile;
	myReadFile.open("Input.txt");

	for (int i = 0; i < N; i++) {
		myReadFile >> x;
		k = hashing(i, N);
		insert(h, k, x, i);
	}

	display(h);
	cout << endl;

	int numb_char = 0;
	cout << "The words not found in the hash table are: " << endl;
	res = CheckText("paragraph.txt", h, N);
	for (int i = 0; i < N; i++) {
		cout <<  res[i] << " ";
	}
	cout << endl;
}