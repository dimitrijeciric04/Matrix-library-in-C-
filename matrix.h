#include <iostream>
#include <thread>
#include <vector>

class matrix{
private:
	std::vector<std::vector<double>> mat;
protected:
	unsigned int n, m;
public:
	matrix(const unsigned n) {
		if (n == 0) throw "Matrix size can not be 0\n";
		this->mat.resize(n, std::vector<double>(n));
		this->n = n;
		this->m = n;
	}
	matrix(const unsigned n, const unsigned m) {
		if (n == 0 || m == 0) throw "Matrix size can not be 0\n";
		this->mat.resize(n, std::vector<double>(m));
		this->n = n;
		this->m = m;
	}
	matrix(const std::vector<std::vector<double>> x){
		if (x.size() == 0) throw "Matrix size can not be 0\n";
		this->mat.resize(x.size(), std::vector<double>(x[0]));
		this->n = x.size(), 
		this->m = x[0].size();
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] = x[i][j];
	}
	matrix operator=(const matrix x){
		this->n = x.n, this->m = x.m;
		this->mat.resize(this->n, std::vector<double>(this->m));
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] = x.mat[i][j];
		return this->mat;
	}
	std::vector<double>& operator[](const unsigned int x){
		if (x > this->n) throw "Index is too big";
		return this->mat[x];
	}
	void resize(const unsigned int x, const unsigned int y){
		this->n = x, this->m = y;
		mat.resize(x, std::vector<double>(y));
	}
	matrix operator+(matrix x){
		if (this->n != x.n || this->m != x.m)
			throw "You can not add matrices with different size\n";
		matrix new_mat(this->n, this->m);
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				new_mat[i][j] = this->mat[i][j] + x[i][j];
		return new_mat;
	}
	matrix operator+=(matrix x){
		if (this->n != x.n || this->m != x.m)
			throw "You can not add matrices with different size\n";
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] += x[i][j];
		return this->mat;
	}
	matrix operator*(const double x){
		matrix new_mat(this->n, this->m);
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				new_mat[i][j] = this->mat[i][j] * x;
		return new_mat;
	}
	matrix operator*=(const double x){
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] *= x;
		return this->mat;
	}
private:
	static void process_multiplication(matrix &new_mat, matrix &a, matrix &b, int i, int n, int m){
		double tmp;
		for (int j = 0; j < n; j++){
			tmp = 0;
			for (int k = 0; k < m; k++)
				tmp += a[i][k] * b[k][j];
			new_mat[i][j] = tmp;
		}
	}
public:
	matrix operator*(matrix x){
		if (this->m != x.n) 
			throw "Matrix multiplication is not supported for this matrices\n";
		matrix new_mat(this->n, x.m), tmp_mat(this->mat);
		std::vector<std::thread> threads(this->n);
		for (int i = 0; i < this->n; i++)
			threads[i] = std::thread(std::ref(process_multiplication), std::ref(new_mat), 
				std::ref(tmp_mat), std::ref(x), i, x.m, this->m);
		/*
		double tmp; // calculation without multithreading
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
	matrix operator*=(matrix x){
		if (this->m != x.n) 
			throw "Matrix multiplication is not supported for this matrices\n";
		matrix new_mat(this->n, x.m), tmp_mat(this->mat);
		std::vector<std::thread> threads(this->n);
		for (int i = 0; i < this->n; i++)
			threads[i] = std::thread(std::ref(process_multiplication), std::ref(new_mat), 
				std::ref(tmp_mat), std::ref(x), i, x.m, this->m);
		/*
		double tmp; // calculation without multithreading
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
		this->mat.resize(this->n, std::vector<double>(this->m));
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] = new_mat[i][j];
		return this->mat;
	}
	matrix operator^(std::pair<unsigned int, unsigned int> idx){ // co matrix
		std::vector<std::vector<double>> tmp_mat;
		std::vector<double> tmp_v;
		for (int i = 0; i < n; i++){
			if (idx.first == i) continue;
			tmp_v.clear();
			for (int j = 0; j < n; j++)
				if (idx.second != j)
					tmp_v.push_back(this->mat[i][j]);
			tmp_mat.push_back(tmp_v);
		}
		return matrix(tmp_mat);
	}	
	matrix operator^=(std::pair<unsigned int, unsigned int> idx){ // co matrix
		std::vector<std::vector<double>> tmp_mat;
		std::vector<double> tmp_v;
		for (int i = 0; i < n; i++){
			if (idx.first == i) continue;
			tmp_v.clear();
			for (int j = 0; j < n; j++)
				if (idx.second != j)
					tmp_v.push_back(this->mat[i][j]);
			tmp_mat.push_back(tmp_v);
		}
		--this->n, --this->m;
		this->mat.resize(this->n, std::vector<double>(this->m));
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				this->mat[i][j] = tmp_mat[i][j];
		return matrix(this->mat);
	}
private:
	double determinant(matrix x){
		if (x.n != x.m)
			throw "Determinant is not supported for non-square matrix!\n";
		if (x.n == 1) return x[0][0];
		if (x.n == 2) return x[0][0] * x[1][1] - x[0][1] * x[1][0];
		double result = 0;
		for (int i = 0; i < x.n; i++)
			result += x[0][i] * determinant(x ^ std::make_pair(0, i)) * (i % 2? -1 : 1);
		return result;
	} 
public:
	double determinant(){return determinant(this->mat);}
	matrix transpose(){
		matrix new_mat(this->m, this->n), tmp_mat(this->mat);
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				new_mat[j][i] = this->mat[i][j];
		return new_mat;
	}
private:
	static void process_inverse(int i, int m, double det, matrix &inverse, matrix &this_mat){
		for (int j = 0; j < m; j++)
			inverse[i][j] = (this_mat ^ std::make_pair(i, j)).determinant() / det * ((i + j) % 2? -1 : 1);
	}
public:
	matrix operator~(){ // inverse of matrix
		double det = this->determinant();
		if (det == 0) throw "Can not calculate inverse of matrix with 0 determinant!\n";
		matrix inverse(this->n, this->m), this_mat(this->mat);
		std::vector<std::thread> threads(this->n);
		for (int i = 0; i < this->n; i++)
			threads[i] = std::thread(std::ref(process_inverse), i, this->m, det, std::ref(inverse), std::ref(this_mat));
		for (int i = 0; i < this->n; i++)
			threads[i].join();
		/*
		for (int i = 0; i < this->n; i++)
			for (int j = 0; j < this->m; j++)
				inverse[i][j] = (this_mat ^ std::make_pair(i, j)).determinant() / det * ((i + j) % 2? -1 : 1);
		*/
		return inverse.transpose();
	}
	
	void print(){
		for (int i = 0; i < this->n; i++){
			for (int j = 0; j < this->m; j++)
				std::cout << this->mat[i][j] << " ";
			std::cout << "\n";
		}
	}
};
