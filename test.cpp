#include <bits/stdc++.h>
#include "matrix.h"
using namespace std;

int random_number(){return rand() % 1000;}

int main(){

	auto t1 = chrono::high_resolution_clock::now();

	int n = 20, m = 20;
	vector<vector<int>> v1(n, vector<int>(m)), v2(n, vector<int>(m));
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++){
			v1[i][j] = random_number();
			v2[i][j] = random_number();
		}

	matrix a(v1), b(v2);
	a *= b;
	//a.print();

	auto t2 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << endl;
	//average time is 350 microseconds

	return 0;
}
