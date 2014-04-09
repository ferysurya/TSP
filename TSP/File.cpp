#include "File.h"

File::File() {}

File::File(string namafile) 
{
	filename = namafile;
}

File::~File() {}

void File::bacaMatriks()
{
	ifstream infile(filename);
	vector<vector<int>> M;	// Matriks penampung hasil bacaan

	// Baca file
	while (infile.good())
	{
		string buffer;
		getline(infile, buffer);
		int i = 0;	char EOL = '\0';
		string temp = "";
		vector<int> tempV;

		// Dapatkan tiap2 angka pada baris
		while (buffer[i] != EOL)
		{
			if (buffer[i] == ' ' || buffer[i + 1] == EOL)
			{
				// Jika merupakan angka terakhir pada baris
				if (buffer[i + 1] == EOL)
					temp += buffer[i];
				int tempint;
				tempint = atoi(temp.c_str());
				tempV.push_back(tempint);
				temp = "";		// Reset temp
			}
			else
				temp += buffer[i];

			++i;
		}

		// Push ke matriksBobot yg merupakan variabel Statik dari kelas Simpul
		M.push_back(tempV);
	}

	// Set matriksBobot
	Simpul::matriksBobot.setMatriks(M);
}