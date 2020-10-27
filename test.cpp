#include <bits/stdc++.h>
#include "matrix.h"
using namespace std;

int random_number(){return rand() % 1000;}

int main(){

	int n = 9, m = 9;
	//cin >> n >> m;
	vector<vector<double>> v1(n, vector<double>(m)), v2(n, vector<double>(m));
	srand(time(NULL));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++){
			v1[i][j] = int(random_number());
			v2[i][j] = int(random_number());
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
	try{
		a = (~a);
	}catch(char const* msg){
		cout << msg << endl;
	}
	auto t2 = chrono::high_resolution_clock::now();
	cout << chrono::duration_cast<std::chrono::microseconds>( t2 - t1).count() << endl;
	a.print();

	return 0;
}
