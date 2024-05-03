#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>

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

    /// frekvencije slova u HRVATSKOM jeziku redom
    vector<double> p = {0.115, 0.015, 0.028, 0.037, 0.084, 0.003, 0.016, 0.008,
                        0.098, 0.051, 0.036, 0.033, 0.031, 0.066, 0.090, 0.029,
                        0.000, 0.054, 0.056, 0.048, 0.043, 0.035, 0.000, 0.000,
                        0.000, 0.023};

    /// Matrica ima m = 6 redaka i ceiling(n/6) stupaca
    const int m = 6;
    const int broj_stupaca = ceil((double)n/(double)m);

    char** matrica = (char**)malloc(m*sizeof(char*));
    for(int i = 0; i < m; i++)
        matrica[i] = (char*)malloc(broj_stupaca*sizeof(char));

    /// Matricu stupac po stupac punim redom elementima iz sifrata
    for(int j = 0; j < broj_stupaca; j++)
        for(int i = 0; i < m; i++)
        {
            if(j*m + i < n)
                matrica[i][j] = Cyphertext[j*m + i];
            else
                /// EVENTUALNI VISAK ELEMENATA MATRICE POSTAVIM NA *
                matrica[i][j] = '*';
        }

    /// Ispis matrice
    cout << "Matrica: \n\n";
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < broj_stupaca; j++)
        {
            cout << matrica[i][j];
        }
        cout << endl << endl;
    }

    vector<int> k (m);  /// ovdje cu redom spremiti slova kljuca (tj. odg. brojeve)

    /// Trazenje k_j za svaki j
    for(int j = 0; j < m; j++)
    {
        int duljina_podniza;
        if(matrica[j][broj_stupaca - 1] != '*')
                duljina_podniza = broj_stupaca;
            else
                duljina_podniza = broj_stupaca - 1;

        vector<int> frekvencija(26, 0);
        for(int i = 0; i < 26; i++)
            for(int l = 0; l < duljina_podniza; l++)
            {
                if(matrica[j][l] == slovo[i])
                        frekvencija[i]++;
            }

        /// Racunanje M_0 - M_25 za fiksirani j
        vector<double> M (26, 0.0);
        for(int g = 0; g < 26; g++)
        {
            for(int i = 0; i < 26; i++)
            {
                int mod = (i - g) % 26;
                if(mod < 0) mod = 26 + mod;

                M[g] += p[i]*frekvencija[mod];
            }

            M[g] = M[g]/duljina_podniza;
        }

        /// Trazenje maksimalnog M za fiksirani j
        double max = M[0];
        int h = 0;
        for(int g = 1; g < 26; g++)
        {
            if(M[g] > max)
            {
                max = M[g];
                h = g;
            }
        }

        if(h == 0)  k[j] = 0;
        else  k[j] = 26 - h;   /// racunanje k_j

        cout << "Za j = " << j + 1 << " imamo h = " << h;
        cout << ", M_" << h << " = " << max;
        cout << ", pa je k_" << j + 1 << " = " << k[j] << "; \n\n";
    }

    cout << "Kljucna rijec: ";
    for(int j = 0; j < m; j++)
        cout << slovo[k[j]];
    cout << endl << endl;

    /// Korespondencija brojeva i slova - drugi smjer
    map<char, int> mapping = {{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4},
                              {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9},
                              {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13},
                              {'O', 14},{'P', 15}, {'Q', 16}, {'R', 17},
                              {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21},
                              {'W', 22}, {'X', 23}, {'Y', 24}, {'Z', 25}};
    /// Dekriptiranje
    for(int j = 0; j < m; j++)
        for(int i = 0; i < broj_stupaca; i++)
        {
            if(matrica[j][i] != '*')
            {
                /// od svakog broja u j-tom retku oduzimam k_j mod 26
                int mod = (mapping[matrica[j][i]] - k[j]) % 26;
                if(mod < 0) mod = 26 + mod;

                /// u istu matricu pohranjujem odgovarajuca dekriptirana slova
                matrica[j][i] = slovo[mod];
            }
        }

    /// Ispisujem dekriptiranu matricu kao jedan string, stupac po stupac
    cout << "Otvoreni tekst: \n\n";
    for(int j = 0; j < broj_stupaca; j++)
        for(int i = 0; i < m; i++)
        {
            if(j*m + i >= n) break; /// dosli smo do kraja teksta

            cout << matrica[i][j];
        }
    cout << endl;

    for(int i = 0; i < m; i++)
        free matrica[i]; 
    free matrica;
    
    return 0;
}

