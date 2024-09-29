#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<ctime>

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
	
	cout << "Citanje...";
	datoteka.open("koordinate.dat", ios::binary | ios::in);
	tocka *polje = new tocka [N]; 
	for (int i = 0; i < N; i++)
	{
		datoteka.read((char *)&polje[i], sizeof(tocka));		
	}
	cout << " procitano!" << endl;
	
	for (int i = 0; i < N; i++) polje[i].x;	
	
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
			cout << "\nPretraga...\n" << (100.00/(N))*i << "%\n";
		}
		for (int c = 0; c < i; c++)
		{
			if (polje[i].x == polje[c].x && polje[i].y == polje[c].y) continue;
			
			if (i == 0 && c == 0)
			{
				min_tocka1 = polje[i];
				min_tocka2 = polje[c];
				min_udalj = udaljenost(polje[i], polje[c]);
				max_tocka1 = polje[i];
				max_tocka2 = polje[c];
				max_udalj = udaljenost(polje[i], polje[c]);
				continue; 
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
		 
	
	cout<<endl;
	system("pause");
	return 0;
}
