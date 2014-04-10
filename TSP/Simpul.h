#pragma once

#include <iostream>
#include <sstream>
#include <deque>
#include <vector>
#include "Matriks.h"
using namespace std;

#include <SFML/Graphics.hpp>

class Simpul{
private:
	int noSimpul;	// Kota/Simpul
	int Cost;		// Cost simpul
	Matriks MT;		// Matriks tereduksi-nya
	vector<int> PassedNode;		// Daftar simpul yang telah dilewati
	int hitungCost(Simpul simpulParent); 

	sf::Color color;
	int X;
	int Y;

public:
	static Matriks matriksBobot;		// matriks bobot graf (A)
	static int simpulGenerated;

	Simpul();
	Simpul(int noSimpul, Simpul simpulParent);
	~Simpul();	
	void setMT(Matriks M);
	void setCost(int N);
	void setNoSimpul(int N);
	bool isSolusi();
	int getCost();
	int getNoSimpul();
	vector<int> getPassedNode();
	Matriks getMatriksTereduksi();
	bool isPassedNode(int simpulNum);
	void Expand(vector<Simpul>& Q);
	void insertSimpul(vector<Simpul>& Q);	
	void insertPassedNode(int i);
	bool isCostSmallest(vector<Simpul> Q);
	string PrintPassedNode();
	void Draw(sf::RenderWindow& renderWindow);
	int getX();
	int getY();
	sf::Color Simpul::getColor();
};
