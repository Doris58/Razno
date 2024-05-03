#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main (void)
{
    string Cyphertext = string("RZZRUVXCAMZEAXHEXGTBSMYUXNUVYIAWMIOZQFHW") +
                        string("OVJHIIIAYBZTUVXXDWTIGOYZUJZFHTZOACFMPEHO") +
                        string("RXGVAXZPOSJGHJGRHYDERFPPDXKTPYNHGSJBZOUN") +
                        string("ZZIYINTFHNKCXRNHGVPZHTXEDGSERAHZNZGAATZFKTP");

    int n = Cyphertext.size();  /// n je duljina zadanog sifrata

    /// slova medunarodne abecede redom 0 - 25
    vector<char> slovo = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                          'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                          'W', 'X', 'Y', 'Z'};

    cout << "Radit cu metodu napada s matricom za m = 1, 2, ... , 10." << "\n\n";

    for(int m = 1; m <= 10; m++)
    {
        cout << "m = " << m << "\n\n";

        /// Matrica ima m redaka i ceiling(n/m) stupaca
        const int broj_redaka = m;
        const int broj_stupaca = ceil((double)n/(double)m);

        char** matrica = (char**)malloc(broj_redaka*sizeof(char*));
        for(int i = 0; i < broj_redaka; i++)
            matrica[i] = (char*)malloc(broj_stupaca*sizeof(char));

        /// Matricu stupac po stupac punim redom elementima iz sifrata
        for(int j = 0; j < broj_stupaca; j++)
            for(int i = 0; i < broj_redaka; i++)
            {
                if(j*broj_redaka + i < n)
                    matrica[i][j] = Cyphertext[j*broj_redaka + i];
                else
                    /// EVENTUALNI VISAK ELEMENATA MATRICE POSTAVIM NA *
                    matrica[i][j] = '*';
            }

        /// Ispis matrice
        cout << "Matrica: \n\n";
        for(int i = 0; i < broj_redaka; i++)
        {
            for(int j = 0; j < broj_stupaca; j++)
            {
                cout << matrica[i][j];
            }
            cout << endl << endl;
        }

        vector<double> indeks(broj_redaka, 0.0);
        int duljina_podniza, frekvencija;

        /// Racunanje indeksa koincidencije za svaki redak matrice
        for(int redak = 0; redak < broj_redaka; redak++)
        {
            if(matrica[redak][broj_stupaca - 1] != '*')
                duljina_podniza = broj_stupaca;
            else
                duljina_podniza = broj_stupaca - 1;

            for(int i = 0; i < 26; i++)
            {
                frekvencija = 0;

                for(int l = 0; l < duljina_podniza; l++)
                {
                    if(matrica[redak][l] == slovo[i])
                        frekvencija++;
                }

                indeks[redak] += frekvencija*(frekvencija - 1);
            }

            indeks[redak] = indeks[redak]/(duljina_podniza*(duljina_podniza - 1));
        }

        /// Ispis svih indeksa koincidencije za odredeni broj m
        cout << "Indeksi koincidencije za podnizove: \n\n";
        for(int i = 0; i < indeks.size(); i++)
        {
            cout << "Podniz z_" << i + 1 << " : ";
            cout << "I_c = " << indeks[i];
            cout << "  GRESKA: " << abs(indeks[i]-0.064) << endl << endl;
        }
        cout << endl << "------------------------------------" << endl << endl;

        for(int i = 0; i < broj_redaka; i++)
            free matrica[i]; 
        free matrica;
    }

    return 0;
}
