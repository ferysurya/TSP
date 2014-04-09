#pragma once

#include <iostream>
#include <vector>
using namespace std;

class Matriks{
private:
	vector<vector<int>> M;	// Isi dari matriks

	// Fungsi reduksi matriks
	bool isNolExistAtRow(int row);
	bool isNolExistAtColumn(int column);
	int getSmallestRowValue(int row);
	int getSmallestColumnValue(int column);
	void reduksiBaris(int row, int Pengurang);
	void reduksiKolom(int column, int Pengurang);

public:
	Matriks();
	Matriks(vector<vector<int>> M);
	Matriks(const Matriks &R);
	Matriks& operator=(const Matriks &R);
	~Matriks();
	
	void setMatriks(vector<vector<int>> MM);
	void Reduksi();	
	void Print();
	int getPengurang();
	int getElmt(int i, int j);
	int Size();
};
