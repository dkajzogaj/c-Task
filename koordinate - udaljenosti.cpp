#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<ctime>

// Ovo je jako glup zadatak, jer za ovoliko milijuna usporedbi i najmodernijim procesorima treba po nekoliko minuta.
// Ugl smanjio sam granicu s 100000/999999 na 1000/9999, tako da se vide rezultati.

using namespace std;

fstream datoteka;

struct tocka{
	int x;
	int y;
};

int udaljenost(tocka tocka1, tocka tocka2)
{
	return (sqrt(pow(tocka2.x - tocka1.x, 2) + pow(tocka2.y - tocka1.y, 2)));
}

int main(){
	
	srand(time(0));
	rand();
	
	int N;
	do{
		cout << "Unesite broj veci od 1000 i manji od 9999: ";
		cin >> N;
	} while (N<=1000 || N >= 9999);
	
	//////////////////////////////////////////////////////////////
	cout << "Upisujem...";
	
	datoteka.open("koordinate.dat", ios::binary | ios::out | ios::trunc);
	for (int i = 0; i < N; i++)
	{
		tocka unos;
		unos.x = rand();
		unos.y = rand();
		datoteka.write((char *)&unos, sizeof(tocka));
	}
	datoteka.close();	
	
	cout << " upisano!" << endl;
	
	//////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	cout << "Citanje...";
	datoteka.open("koordinate.dat", ios::binary | ios::in);
	tocka *polje = new tocka [N]; // �itat �emo iz datoteke samo jednom (u ovo polje), a onda tra�iti min/max iz ovog polja
	for (int i = 0; i < N; i++)
	{
		datoteka.read((char *)&polje[i], sizeof(tocka));		
	}
	cout << " procitano!" << endl;
	
	for (int i = 0; i < N; i++) polje[i].x;	// Iz nekog razloga program bez ovoga ne �eli obaviti pretragu kak spada... Ne pitaj previ�e...
	
	int min_udalj;
	int max_udalj;
	tocka min_tocka1;
	tocka min_tocka2;
	tocka max_tocka1;
	tocka max_tocka2;
	for (int i = 0; i < N; i++)
	{
		if (i%10==0)
		{
			// prika�imo postotak pretrage, samo da znamo koliko jo� kave mo�emo popiti do rezultata (pogotovo ako dopustimo da je N preko 100,000)
			cout << "\nPretraga...\n" << (100.00/(N))*i << "%\n";	// dost primitivno, ali barem slu�i svrsi ('system("cls")' je program pretvorio u Vietnam flashback)
		}
		for (int c = 0; c < i; c++)
		{
			if (polje[i].x == polje[c].x && polje[i].y == polje[c].y) continue; // ne �elimo uspore�ivati iste to�ke!
			
			if (i == 0 && c == 0)
			{
				min_tocka1 = polje[i];
				min_tocka2 = polje[c];
				min_udalj = udaljenost(polje[i], polje[c]);
				max_tocka1 = polje[i];
				max_tocka2 = polje[c];
				max_udalj = udaljenost(polje[i], polje[c]);
				continue; // prvi put treba postaviti minimalnu i maksimalnu udaljenost, a tek onda mo�emo dalje uspore�ivati
			}
			if (udaljenost(polje[i], polje[c]) < min_udalj)
			{
				min_tocka1 = polje[i];
				min_tocka2 = polje[c];
				min_udalj = udaljenost(polje[i], polje[c]);
			}
			else if (udaljenost(polje[i], polje[c]) > max_udalj)
			{
				max_tocka1 = polje[i];
				max_tocka2 = polje[c];
				max_udalj = udaljenost(polje[i], polje[c]);
			}
		}
	}
	cout << "\nPretraga...\n100%\n\n\n";
	cout << "MINIMALNA UDALJENOST: " << min_udalj << endl
		 << "X1: " << min_tocka1.x << "; Y1: " << min_tocka1.y << endl
		 << "X2: " << min_tocka2.x << "; Y2: " << min_tocka2.y << endl
		 << "MAKSIMALNA UDALJENOST: " << max_udalj << endl
		 << "X1: " << max_tocka1.x << "; Y1: " << max_tocka1.y << endl
		 << "X2: " << max_tocka2.x << "; Y2: " << max_tocka2.y << endl;
		 
	//////////////////////////////////////////////////////////////
	
	cout<<endl;
	system("pause");
	return 0;
}
