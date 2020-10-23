#include <bits/stdc++.h>
#include "matrix.h"
using namespace std;

int random_number(){return rand() % 1000;}

int main(){

	int n = 100, m = 100;
	//cin >> n >> m;
	vector<vector<int>> v1(n, vector<int>(m)), v2(n, vector<int>(m));
	srand(time(NULL));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++){
			v1[i][j] = random_number();
			v2[i][j] = random_number();
		}
	/*
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> v1[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> v2[i][j];
	*/

	matrix a(v1), b(v2), c(n, m);
	auto t1 = chrono::high_resolution_clock::now();
	c = a;
	c *= b;
	auto t2 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<std::chrono::microseconds>( t2 - t1).count() << endl;
	//c.print();

	return 0;
}
