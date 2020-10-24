#include <iostream>
#include <thread>
#include <vector>

template<class T>
class matrix{
private:
	std::vector<std::vector<T>> mat;
protected:
	unsigned int n, m;
public:
	matrix(const unsigned int n, T val = 0) {
		if (n == 0) throw "Matrix size can not be 0";
		this->mat.resize(n, std::vector<T>(n, val));
		this->n = n;
		this->m = n;
	}
	matrix(const unsigned int n, const unsigned int m, T val = 0) {
		if (n == 0 || m == 0) throw "Matrix size can not be 0";
		this->mat.resize(n, std::vector<T>(m, val));
		this->n = n;
		this->m = m;
	}
	matrix(const std::vector<std::vector<T>> &x){
		if (x.size() == 0) throw "Matrix size can not be 0";
		this->mat.resize(x.size(), std::vector<T>(x[0]));
		this->n = x.size(), 
		this->m = x[0].size();
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] = x[i][j];
	}
	matrix<T> operator=(const matrix<T> &x){
		this->n = x.n, this->m = x.m;
		this->mat.resize(this->n, std::vector<T>(this->m));
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] = x.mat[i][j];
		return this->mat;
	}
	std::vector<T>& operator[](const unsigned int &x){
		if (x > this->n) throw "Index is too big";
		return this->mat[x];
	}
	matrix<T> operator+(matrix<T> &x){
		if (this->n != x.n || this->m != x.m)
			throw "You can not add matrices with different size\n";
		matrix<T> new_mat(this->n, this->m);
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				new_mat[i][j] = this->mat[i][j] + x[i][j];
		return new_mat;
	}
	matrix<T> operator+=(matrix<T> &x){
		if (this->n != x.n || this->m != x.m)
			throw "You can not add matrices with different size\n";
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] += x[i][j];
		return this->mat;
	}
	matrix<T> operator*(T x){
		matrix<T> new_mat(this->n, this->m);
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				new_mat[i][j] = this->mat[i][j] * x;
		return new_mat;
	}
	matrix<T> operator*=(T x){
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] *= x;
		return this->mat;
	}
private:
	static void process(matrix<T> &new_mat, matrix<T> &a, matrix<T> &b, int i, int n, int m){
		T tmp;
		for (int j = 0; j < n; j++){
			tmp = 0;
			for (int k = 0; k < m; k++)
				tmp += a[i][k] * b[k][j];
			new_mat[i][j] = tmp;
		}
	}
public:
	matrix operator*(matrix<T> &x){
		if (this->m != x.n) 
			throw "Matrix multiplication is not supported for this matrices\n";
		matrix<T> new_mat(this->n, x.m), tmp_mat(this->mat);
		std::vector<std::thread> threads(this->n);
		for (int i = 0; i < this->n; i++)
			threads[i] = std::thread(std::ref(process), std::ref(new_mat), 
				std::ref(tmp_mat), std::ref(x), i, x.m, this->m);
		/*
		int tmp;
		for (int i = 0; i < new_mat.n; i++)
			for (int j = 0; j < new_mat.m; j++){
				tmp = 0;
				for (int k = 0; k < this->m; k++)
					tmp += this->mat[i][k] * x[k][j];
				new_mat[i][j] = tmp;
			}
		*/
		for (int i = 0; i < this->n; i++)
			threads[i].join();
		return new_mat;
	}
	matrix operator*=(matrix<T> &x){
		if (this->m != x.n) 
			throw "Matrix multiplication is not supported for this matrices\n";
		matrix<T> new_mat(this->n, x.m), tmp_mat(this->mat);
		std::vector<std::thread> threads(this->n);
		for (int i = 0; i < this->n; i++)
			threads[i] = std::thread(std::ref(process), std::ref(new_mat), 
				std::ref(tmp_mat), std::ref(x), i, x.m, this->m);
		/*
		int tmp;
		for (int i = 0; i < new_mat.n; i++)
			for (int j = 0; j < new_mat.m; j++){
				tmp = 0;
				for (int k = 0; k < this->m; k++)
					tmp += this->mat[i][k] * x[k][j];
				new_mat[i][j] = tmp;
			}
		*/
		for (int i = 0; i < this->n; i++)
			threads[i].join();
		this->m = x.m;
		this->mat.resize(this->n, std::vector<int>(this->m));
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] = new_mat[i][j];
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
