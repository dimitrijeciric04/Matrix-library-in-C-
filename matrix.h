#include <iostream>
#include <vector>

class matrix{
private:
protected:
	std::vector<std::vector<int>> mat;
	unsigned int n, m;
public:
	matrix(const unsigned int n, int val = 0) {
		if (n == 0) throw "Matrix size can not be 0";
		this->mat.resize(n, std::vector<int>(n, val));
		this->n = n;
		this->m = n;
	}
	matrix(const unsigned int n, const unsigned int m, int val = 0) {
		if (n == 0 || m == 0) throw "Matrix size can not be 0";
		this->mat.resize(n, std::vector<int>(m, val));
		this->n = n;
		this->m = m;
	}
	matrix(const std::vector<std::vector<int>> &x){
		if (x.size() == 0) throw "Matrix size can not be 0";
		this->mat.resize(x.size(), std::vector<int>(x[0]));
		this->n = x.size(), 
		this->m = x[0].size();
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] = x[i][j];
	}
	matrix operator=(const matrix &x){
		this->n = x.n, this->m = x.m;
		this->mat.resize(this->n, std::vector<int>(this->m));
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] = x.mat[i][j];
		return this->mat;
	}
	matrix operator+(const matrix &x){
		if (this->n != x.n || this->m != x.m)
			throw "You can not add matrices with different size\n";
		matrix new_mat(this->n, this->m);
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				new_mat.mat[i][j] = x.mat[i][j] + this->mat[i][j];
		return new_mat;
	}
	matrix operator+=(const matrix &x){
		if (this->n != x.n || this->m != x.m)
			throw "You can not add matrices with different size\n";
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] += x.mat[i][j];
		return this->mat;
	}
	matrix operator*(const int x){
		matrix new_mat(this->n, this->m);
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				new_mat.mat[i][j] = this->mat[i][j] * x;
		return new_mat;
	}
	matrix operator*=(const int x){
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] *= x;
		return this->mat;
	}
	matrix operator*(const matrix &x){
		if (this->m != x.n) 
			throw "Matrix multiplication is not supported for this matrices\n";
		matrix new_mat(this->n, x.m);
		int tmp;
		for (int i = 0; i < new_mat.n; i++)
			for (int j = 0; j < new_mat.m; j++){
				tmp = 0;
				for (int k = 0; k < this->m; k++)
					tmp += this->mat[i][k] * x.mat[k][j];
				new_mat.mat[i][j] = tmp;
			}
		return new_mat;
	}
	matrix operator*=(const matrix &x){
		if (this->m != x.n) 
			throw "Matrix multiplication is not supported for this matrices\n";
		matrix new_mat(this->n, x.m, 0);
		int tmp;
		for (int i = 0; i < new_mat.n; i++)
			for (int j = 0; j < new_mat.m; j++){
				tmp = 0;
				for (int k = 0; k < this->m; k++)
					tmp += this->mat[i][k] * x.mat[k][j];
				new_mat.mat[i][j] = tmp;
			}
		this->m = x.m;
		this->mat.resize(this->n, std::vector<int>(this->m));
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] = new_mat.mat[i][j];
		return this->mat;
	}
	void print(){
		for (int i = 0; i < this->n; i++){
			for (int j = 0; j < this->m; j++)
				std::cout << this->mat[i][j] << " ";
			std::cout << "\n";
		}
	}
};