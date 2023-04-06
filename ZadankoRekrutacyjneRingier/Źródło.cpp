#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Kaczuszka {
    int wysokosc, szerokosc;
};

bool porownaj(Kaczuszka k1, Kaczuszka k2) {
    return k1.szerokosc < k2.szerokosc;
}

int main()
{
    //wczytanie danych
    string plik = "dane.txt";
    int liczbaDostepnychKaczuszek;
    int maksymalnaSzerokoscRzedu;

    ifstream odczyt(plik);

    if (!odczyt) {
        cout << "Nie mozna otworzyc pliku!" << endl;
        system("pause");
    }

    odczyt >> liczbaDostepnychKaczuszek;
    odczyt >> maksymalnaSzerokoscRzedu;

    //utworzenie tablicy kaczek
    Kaczuszka* kaczka = new Kaczuszka[liczbaDostepnychKaczuszek];
    for (int i = 0; i < liczbaDostepnychKaczuszek; i++) {
        odczyt >> kaczka[i].wysokosc >> kaczka[i].szerokosc;
    };

    //weryfikacja poprawnosci odczytu
    for (int i = 0; i < liczbaDostepnychKaczuszek; i++) {
        cout << kaczka[i].wysokosc << " " << kaczka[i].szerokosc << endl;
    };

    cout << endl << endl;

    //posortowanie wzgledem szerokosci
    sort(kaczka, kaczka + liczbaDostepnychKaczuszek, porownaj);

    for (int i = 0; i < liczbaDostepnychKaczuszek; i++) {
        cout << kaczka[i].wysokosc << " " << kaczka[i].szerokosc << endl;
    };


    vector<vector<int>> dp(liczbaDostepnychKaczuszek + 1, vector<int>(maksymalnaSzerokoscRzedu + 1));
    for (int i = 1; i <= liczbaDostepnychKaczuszek; i++) {
        for (int j = 1; j <= maksymalnaSzerokoscRzedu; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= kaczka[i - 1].szerokosc) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - kaczka[i - 1].szerokosc] + kaczka[i - 1].wysokosc);
            }
        }
    }

    cout << endl << dp[liczbaDostepnychKaczuszek][maksymalnaSzerokoscRzedu] << endl;

    return 0;
}