#include <iostream>
#include <string>

using namespace std;

const int MAX = 10;
int liczbaOsob = 0;

int nrIndeksu[MAX];
string imie[MAX];
string nazwisko[MAX];
bool obecny[MAX];

void dodajOsobe(int nrIndeksuVal, const string& imieVal, const string& nazwiskoVal, bool obecnyVal)
{
    if(liczbaOsob < MAX)
    {
        nrIndeksu[liczbaOsob] = nrIndeksuVal;
        imie[liczbaOsob] = imieVal;
        nazwisko[liczbaOsob] = nazwiskoVal;
        obecny[liczbaOsob] = obecnyVal;
        liczbaOsob++;
    }
}
void ustawObecnosc(int nrIndeksuVal, bool obecnosci)
{
    for(int i = 0; i < liczbaOsob; i++)
    {
        if(nrIndeksu[i] == nrIndeksuVal)
        {
            obecny[i] = obecnosci;
        }
    }
}

bool edytujOsobe(int nrIndeksuVal, int nowyNrIndeksu, const string& noweImie, const string& noweNazwisko, bool zmienicObecnosc, bool nowaObecnosc)
{
    int idx = -1;
    for(int i = 0; i < liczbaOsob; i++)
    {
        if(nrIndeksu[i] == nrIndeksuVal)
        {
            idx = i;
            break;
        }
    }
    if(idx == -1)
    {
        return false;
    }

    if(nowyNrIndeksu > 0 && nowyNrIndeksu != nrIndeksuVal)
    {
        for(int i = 0; i < liczbaOsob; i++)
        {
            if(nrIndeksu[i] == nowyNrIndeksu)
            {
                return false; // Konflikt numerów indeksu
            }
        }
        nrIndeksu[idx] = nowyNrIndeksu;
    }

    if(!noweImie.empty() && noweImie != "-")
    {
        imie[idx] = noweImie;
    }

    if(!noweNazwisko.empty() && noweNazwisko != "-")
    {
        nazwisko[idx] = noweNazwisko;
    }

    if(zmienicObecnosc)
    {
        obecny[idx] = nowaObecnosc;
    }

    return true;
}

bool usunOsobe(int nrIndeksuVal)
{
    int idx = -1;
    for(int i = 0; i < liczbaOsob; i++)
    {
        if(nrIndeksu[i] == nrIndeksuVal)
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
        nrIndeksu[i] = nrIndeksu[i + 1];
        imie[i] = imie[i + 1];
        nazwisko[i] = nazwisko[i + 1];
        obecny[i] = obecny[i + 1];
    }

    liczbaOsob--;
    return true;
}

void drukujListe()
{
    cout << "\nLista obecnosci:\n";
    cout << "Nr indeksu | Imie | Nazwisko | Obecny\n";

    for(int i = 0; i < liczbaOsob; i++)
    {
        cout << nrIndeksu[i] << " | " << imie[i] << " | " << nazwisko[i] << " | " << (obecny[i] ? 1 : 0) << endl;
    }
}

int main()
{

    int nrIndeksuVal;
    string imieVal;
    string nazwiskoVal;
    bool obecnyVal;
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
                cin >> nrIndeksuVal;
                bool existsIndex = false;
                for(int i = 0; i < liczbaOsob; i++)
                {
                    if(nrIndeksu[i] == nrIndeksuVal)
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
                cin >> imieVal;
                cout << "Podaj nazwisko: ";
                cin >> nazwiskoVal;
                cout << "Czy osoba byla obecna? (1 tak, 0 nie): ";
                cin >> obecnyVal;

                dodajOsobe(nrIndeksuVal, imieVal, nazwiskoVal, obecnyVal);
                break;
            }
            case '2':
            {
                cout << "Podaj nr indeksu osoby do edycji: ";
                cin >> nrIndeksuVal;

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

                bool ok = edytujOsobe(nrIndeksuVal, nowyNrIndeksu, noweImie, noweNazwisko, zmienicObecnosc, nowaObecnosc);
                if(!ok)
                {
                    cout << "Nie znaleziono osoby lub nr indeksu docelowy jest zajety.\n";
                }
                break;
            }
            case '3':
            {
                cout << "Podaj nr indeksu osoby do usuniecia: ";
                cin >> nrIndeksuVal;
                bool ok = usunOsobe(nrIndeksuVal);
                if(!ok)
                {
                    cout << "Nie znaleziono osoby o tym numerze indeksu.\n";
                }
                break;
            }
            case '4':
                drukujListe();
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