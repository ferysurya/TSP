#include <iostream>
#include <sstream>
#include <deque>
#include "Matriks.h"
#include "Simpul.h"
#include "File.h"
using namespace std;

#include <SFML/Graphics.hpp>

enum GameState {Playing, Exiting};
GameState gameState;

bool isExiting() {
	if(gameState==Exiting)
		return true;
	else
		return false;
}

bool isTetangga(vector<int> P, int simpulBelakang, int simpulDepan)
{
	int i=0;
	while(P[i] != simpulDepan)
		++i;

	if(simpulDepan==P.back())
	{
		if(P[i-1]==simpulBelakang)
			return true;
		else
			return false;
	}
	else
	if(simpulDepan==P.front())
	{
		if(i+1==simpulBelakang)
			return true;
		else
			return false;
	}
	else
	{
		if(P[i+1]==simpulBelakang || P[i-1]==simpulBelakang)
			return true;
		else
			return false;
	}
}

int getBobotPassedNode(vector<int> PassedNode,Matriks matriksAwal)
{
	int bobot=0;
	for(int i=1;i<PassedNode.size();++i)
		bobot += matriksAwal.getElmt(PassedNode[i-1], PassedNode[i]);

	return bobot + matriksAwal.getElmt(PassedNode.back(), PassedNode.front());
}

int main() {
	
	// Timer program
    clock_t tStart = clock();

	// Handle file input
	File F("Filematriks2.txt");
	F.bacaMatriks();

	// Matriks semula (sebelum direduksi)
	Matriks MatriksAwal = Simpul::matriksBobot;

	// Tampilkan matriksBobot
	Simpul::matriksBobot.Print();

	// Reduksi matriksBobot
	Simpul::matriksBobot.Reduksi();		// Reduksi matriks Start
	Simpul::matriksBobot.Print();		// Tampilkan matriksBobot tereduksi
	
	// Buat simpul bestSolution
	Simpul bestSolution;
	bestSolution.setCost(9999); // Set sgt tinggi supaya pasti ditukar klo ada solusi pertama

	// Buat Queue Simpul
	vector<Simpul> Q;

	// Buat simpul Start & push ke Q
	Simpul Start;
	Start.setNoSimpul(1);
	Start.setMT(Simpul::matriksBobot);
	Start.setCost(Simpul::matriksBobot.getPengurang());
	Start.insertPassedNode(1);
	Simpul::simpulGenerated++;
	Q.push_back(Start);

	// Selama Q tidak kosong, expand simpul terdepan
	while(Q.size() != 0)
	{
		Simpul X = Q.front();	// Ambil simpul terdepan
		Q.erase(Q.begin());	// Pop depan

		if(!X.isSolusi())
		{
			X.Expand(Q);
		}
		else
		{
			if(X.getCost()<bestSolution.getCost())	// Jika X merupakan solusi terbaik
				bestSolution = X;			// Masukkan ke bestSolution
			
			if(bestSolution.isCostSmallest(Q))		// Jika tidak ada lg Cost(simpul) pd Q < Cost(bestSolutiono) 
			{
				Q.erase(Q.begin(),Q.end());		// Hapus semua isi Q
			}
		}
	}
	
	// Print info
	stringstream SS;
	SS << bestSolution.PrintPassedNode();
	SS << "Bobot : " << getBobotPassedNode(bestSolution.getPassedNode(), MatriksAwal) << endl;
	SS << "Jumlah simpul dibangkitkan : " << Simpul::simpulGenerated << endl;
    SS << "Waktu eksekusi : " << ((double)(clock() - tStart)/CLOCKS_PER_SEC) << "\n";

    sf::Font font;
    if (!font.loadFromFile("Capriola-Regular.ttf"))
        cout << "Couldn't load font" << endl;

	sf::Text text(SS.str(), font, 15);
	text.setColor(sf::Color::White);
	text.setPosition(750, 600);

	/* GUI Handling */
	srand (time(NULL));
	gameState = Playing;
	
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(1000, 700), "Travelling Salesman Problem");

	// Buat Array of Node untuk digambarkan ke layar
	vector<Simpul> S;
	Simpul Dummy;
	S.push_back(Dummy);
	int Size = Simpul::matriksBobot.Size();
	for(int i=1;i<Size;++i)
	{
		Simpul X;
		X.setNoSimpul(i);
		S.push_back(X);
	}

	// Gambarkan garis
	for(int i=1;i<S.size();++i)
	{
		for(int j=1;j<S.size();++j)
		{
			if(i!=j)
			{
				sf::VertexArray garis(sf::Lines, 2);
				
				// Set posisi garis
				garis[0].position = sf::Vector2f(S[i].getX()+10, S[i].getY()+10);
				garis[1].position = sf::Vector2f(S[j].getX()+10, S[j].getY()+10);
				
				// Beri path solusi dg warna berbeda
				if(isTetangga(bestSolution.getPassedNode(), j, i))
				{
					garis[0].color = sf::Color::White;
					garis[1].color = sf::Color::White;
				}
				else
				{
					garis[0].color = S[i].getColor();
					garis[1].color = S[j].getColor();
				}
				window.draw(garis);
			}
		}

		// Gambarkan Node
		S[i].Draw(window);
	}

	// Tampilkan info
	window.draw(text);

	// Update Window
	window.display();

	while(!isExiting())
	{
		// Handle event
		sf::Event currentEvent;
		while(window.pollEvent(currentEvent))
		{

			// Handle Exit-button
			if(currentEvent.type == sf::Event::Closed) 
				gameState = Exiting;
		}
	}
	

	return 0;
}