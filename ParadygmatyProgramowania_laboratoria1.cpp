#include <iostream>
#include <string>

using namespace std;

const int MAX = 10;
int liczbaOsob = 0;

struct Osoba {
    int nrIndeksu;
    string imie;
    string nazwisko;
    bool obecny;
};

void dodajOsobe(Osoba* tab, int nrIndeksu, const string& imie, const string& nazwisko, bool obecny)
{
    if(liczbaOsob < MAX)
    {
        tab[liczbaOsob].nrIndeksu = nrIndeksu;
        tab[liczbaOsob].imie = imie;
        tab[liczbaOsob].nazwisko = nazwisko;
        tab[liczbaOsob].obecny = obecny;
        liczbaOsob++;
    }
}
void ustawObecnosc(Osoba* tab, int nrIndeksu, bool obecnosci)
{
    for(int i = 0; i < liczbaOsob; i++)
    {
        if(tab[i].nrIndeksu == nrIndeksu)
        {
            tab[i].obecny = obecnosci;
        }
    }
}

bool edytujOsobe(Osoba* tab, int nrIndeksu, int nowyNrIndeksu, const string& noweImie, const string& noweNazwisko, bool zmienicObecnosc, bool nowaObecnosc)
{
    int idx = -1;
    for(int i = 0; i < liczbaOsob; i++)
    {
        if(tab[i].nrIndeksu == nrIndeksu)
        {
            idx = i;
            break;
        }
    }
    if(idx == -1)
    {
        return false;
    }

    if(nowyNrIndeksu > 0 && nowyNrIndeksu != nrIndeksu)
    {
        for(int i = 0; i < liczbaOsob; i++)
        {
            if(tab[i].nrIndeksu == nowyNrIndeksu)
            {
                return false; // Konflikt numerów indeksu
            }
        }
        tab[idx].nrIndeksu = nowyNrIndeksu;
    }

    if(!noweImie.empty() && noweImie != "-")
    {
        tab[idx].imie = noweImie;
    }

    if(!noweNazwisko.empty() && noweNazwisko != "-")
    {
        tab[idx].nazwisko = noweNazwisko;
    }

    if(zmienicObecnosc)
    {
        tab[idx].obecny = nowaObecnosc;
    }

    return true;
}

bool usunOsobe(Osoba* tab, int nrIndeksu)
{
    int idx = -1;
    for(int i = 0; i < liczbaOsob; i++)
    {
        if(tab[i].nrIndeksu == nrIndeksu)
        {
            idx = i;
            break;
        }
    }
    if(idx == -1)
    {
        return false;
    }

    for(int i = idx; i < liczbaOsob - 1; i++)
    {
        tab[i] = tab[i + 1];
    }

    liczbaOsob--;
    return true;
}

void drukujListe(Osoba* tab)
{
    cout << "\nLista obecnosci:\n";
    cout << "Nr indeksu | Imie | Nazwisko | Obecny\n";

    for(int i = 0; i < liczbaOsob; i++)
    {
        cout << tab[i].nrIndeksu << " | " << tab[i].imie << " | " << tab[i].nazwisko << " | " << (tab[i].obecny ? 1 : 0) << endl;
    }
}

int main()
{
    Osoba tabOsob[MAX];

    int nrIndeksu;
    string imie;
    string nazwisko;
    bool obecny;
    char wybor;

    do
    {
        cout << "\nMenu:\n";
        cout << " 1 - dodaj osobe\n";
        cout << " 2 - edytuj osobe\n";
        cout << " 3 - usun osobe\n";
        cout << " 4 - pokaz liste\n";
        cout << " 5 - zakoncz\n";
        cout << "Wybierz opcje: ";
        cin >> wybor;

        switch(wybor)
        {
            case '1':
            {
                cout << "Podaj nr indeksu: ";
                cin >> nrIndeksu;
                bool existsIndex = false;
                for(int i = 0; i < liczbaOsob; i++)
                {
                    if(tabOsob[i].nrIndeksu == nrIndeksu)
                    {
                        existsIndex = true;
                        break;
                    }
                }

                if(existsIndex)
                {
                    cout << "Ten nr indeksu jest juz zajety\n";
                    break;
                }

                cout << "Podaj imie: ";
                cin >> imie;
                cout << "Podaj nazwisko: ";
                cin >> nazwisko;
                cout << "Czy osoba byla obecna? (1 tak, 0 nie): ";
                cin >> obecny;

                dodajOsobe(tabOsob, nrIndeksu, imie, nazwisko, obecny);
                break;
            }
            case '2':
            {
                cout << "Podaj nr indeksu osoby do edycji: ";
                cin >> nrIndeksu;

                int nowyNrIndeksu;
                string noweImie;
                string noweNazwisko;
                int obecnoscInput;
                bool zmienicObecnosc = false;
                bool nowaObecnosc = false;

                cout << "Nowy nr indeksu (0 zostaw bez zmian): ";
                cin >> nowyNrIndeksu;
                cout << "Nowe imie (wpisz '-' aby zostawic): ";
                cin >> noweImie;
                cout << "Nowe nazwisko (wpisz '-' aby zostawic): ";
                cin >> noweNazwisko;
                cout << "Nowa obecnosc (1 tak 0 nie -1 zostaw bez zmian): ";
                cin >> obecnoscInput;

                if(obecnoscInput == 0 || obecnoscInput == 1)
                {
                    zmienicObecnosc = true;
                    nowaObecnosc = (obecnoscInput == 1);
                }

                bool ok = edytujOsobe(tabOsob, nrIndeksu, nowyNrIndeksu, noweImie, noweNazwisko, zmienicObecnosc, nowaObecnosc);
                if(!ok)
                {
                    cout << "Nie znaleziono osoby lub nr indeksu docelowy jest zajety.\n";
                }
                break;
            }
            case '3':
            {
                cout << "Podaj nr indeksu osoby do usuniecia: ";
                cin >> nrIndeksu;
                bool ok = usunOsobe(tabOsob, nrIndeksu);
                if(!ok)
                {
                    cout << "Nie znaleziono osoby o tym numerze indeksu.\n";
                }
                break;
            }
            case '4':
                drukujListe(tabOsob);
                break;
            case '5':
                cout << "Koniec.\n";
                break;
            default:
                cout << "Nieprawidlowy wybor.\n";
        }

    } while(wybor != 'q' && wybor != 'Q');

    return 0;
}