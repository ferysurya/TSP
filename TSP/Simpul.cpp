#include "Simpul.h"

// Static variable
Matriks Simpul::matriksBobot;
int Simpul::simpulGenerated = 0;

// CTOR
Simpul::Simpul() 
{
	Cost = 0;
	noSimpul = 0;

	X = rand()%980;
	Y = rand()%650;
	color = sf::Color::Red;
}

// CTOR w/ PARAM
Simpul::Simpul(int noSimpul, Simpul simpulParent)
{
	this->noSimpul = noSimpul;

	// set Matriks Tereduksinya
	MT = simpulParent.getMatriksTereduksi();
	MT.Reduksi(simpulParent.getNoSimpul(), noSimpul);	// Reduksi matriks parent-nya

	Cost = hitungCost(simpulParent);

	// set PassedNode
	PassedNode = simpulParent.getPassedNode();
	PassedNode.push_back(noSimpul);

	X = rand()%1000;
	Y = rand()%700;
	color = sf::Color::Red;
}

// DTOR
Simpul::~Simpul() {}

void Simpul::setMT(Matriks M)
{
	MT = M;
}

int Simpul::hitungCost(Simpul simpulParent) 
{
	int totalCost;
	int i = simpulParent.getNoSimpul();
	int j = noSimpul;
	totalCost = simpulParent.getCost() + Simpul::matriksBobot.getElmt(i,j) + MT.getPengurang();

	return totalCost;
}

bool Simpul::isSolusi()
{
	// Iterasi baris matriks
	int i=1;
	bool Found = false;
	while(!Found && i<MT.Size())
	{
		int j=1;
		// Iterasi kolom matriks
		while(!Found && j<MT.Size())
		{
			if(MT.getElmt(i,j) != -99)
				Found = true;
			else
				++j;
		}
		++i;
	}

	// Jika ditemukan angka selain -99(infiniti), maka bukan solusi
	return !Found;
}

void Simpul::setCost(int N)
{
	Cost = N;
}

void Simpul::setNoSimpul(int N)
{
	noSimpul = N;
}

int Simpul::getCost()
{
	return Cost;
}

int Simpul::getNoSimpul()
{
	return noSimpul;
}

Matriks Simpul::getMatriksTereduksi()
{
	return MT;
}

vector<int> Simpul::getPassedNode()
{
	return PassedNode;		
}

bool Simpul::isPassedNode(int  simpulNum)
{
	int i=0;
	bool Found = false;
	while(!Found && i<PassedNode.size())
	{
		if(PassedNode[i]==simpulNum)
			Found = true;
		else
			++i;
	}

	return Found;
}

void Simpul::insertSimpul(vector<Simpul>& Q)
{
	int i=0; bool Done = false;
	while(!Done)
	{
		// Jika nilai simpul pada Q < simpul yg ingin dimasukkan && bukan simpul ujung+1
		if(i<Q.size() && Q[i].getCost()<Cost)
			++i;
		else
		{
			// Masukkan elemen ke Q[i]
			Q.insert(Q.begin()+i, *this);
			Done = true;
		}
	}
}

void Simpul::insertPassedNode(int i)
{
	PassedNode.push_back(i);
}

void Simpul::Expand(vector<Simpul>& Q)
{
	int Size = Simpul::matriksBobot.Size();

	// Expand simpul
	for(int i=1;i<Size;++i)
	{
		// Jika i belum pernah dikunjungi
		if(!isPassedNode(i))
		{
			Simpul Anak(i, *this);
			Anak.insertSimpul(Q);		// Masukkan simpul ke dalam Q
			Simpul::simpulGenerated++;	// Increment jumlah simpul yg dibangkitkan
		}
	}

}

bool Simpul::isCostSmallest(vector<Simpul> Q)
{
	int i=0;
	bool Smallest = true;
	while(Smallest && i<Q.size())
	{
		if(Cost < Q[i].getCost())
			++i;
		else
			Smallest = false;
	}

	return Smallest;
}

string Simpul::PrintPassedNode()
{
	stringstream SS;
	SS << "Tur terpendek : ";
	for(int i=0;i<PassedNode.size();++i)
		SS << PassedNode[i] << "-";

	SS << PassedNode[0] << "\n";	// Node akhir

	return SS.str();
}

// GUI Handling
void Simpul::Draw(sf::RenderWindow& renderWindow)
{
	
	// Buat lingkaran simpul
	sf::CircleShape shape(15.f, 100);

	// Isi sesuai properti warna
	shape.setFillColor(color);

	// Atur koordinat
	shape.setPosition(sf::Vector2f(X, Y));

	 // Gambar no simpul
    sf::Font font;
    if (!font.loadFromFile("Capriola-Regular.ttf"))
        cout << "Couldn't load font" << endl;

	sf::Text text(to_string(noSimpul), font, 20);
	text.setColor(sf::Color::Blue);
	text.setPosition(X+10, Y);

	// Gambarkan
	renderWindow.draw(shape);
	renderWindow.draw(text);
}

int Simpul::getX()
{
	return X;
}

int Simpul::getY()
{
	return Y;
}

sf::Color Simpul::getColor()
{
	return color;
}