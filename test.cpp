#include <bits/stdc++.h>
#include "matrix.h"
using namespace std;

int main(){

	int n, m;
	cin >> n >> m;

	vector<vector<int>> m1(n, vector<int>(m, 0)), m2(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> m1[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> m2[i][j];


	matrix a(m1), b(m2), c(n, m, 0);
	a *= b;
	a[0][0] = 1;
	cout << a[0][0] << endl;
	a.print();

	return 0;
}
