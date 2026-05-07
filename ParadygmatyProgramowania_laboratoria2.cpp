#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

class Osoba
{
private:
    int nrIndeksu;
    string imie;
    string nazwisko;
    bool obecny;

public:
    Osoba()
    {
        nrIndeksu = 0;
        imie = "";
        nazwisko = "";
        obecny = false;
    }

    Osoba(int nrIndeksuVal, string imieVal, string nazwiskoVal, bool obecnyVal)
    {
        nrIndeksu = nrIndeksuVal;
        imie = imieVal;
        nazwisko = nazwiskoVal;
        obecny = obecnyVal;
    }

    int pobierzNrIndeksu()
    {
        return nrIndeksu;
    }

    string pobierzImie()
    {
        return imie;
    }

    string pobierzNazwisko()
    {
        return nazwisko;
    }

    bool pobierzObecnosc()
    {
        return obecny;
    }

    void ustawNrIndeksu(int nowyNrIndeksu)
    {
        nrIndeksu = nowyNrIndeksu;
    }

    void ustawImie(string noweImie)
    {
        imie = noweImie;
    }

    void ustawNazwisko(string noweNazwisko)
    {
        nazwisko = noweNazwisko;
    }

    void ustawObecnosc(bool nowaObecnosc)
    {
        obecny = nowaObecnosc;
    }

    void drukuj()
    {
        cout << nrIndeksu << " | " << imie << " | " << nazwisko << " | " << (obecny ? 1 : 0) << endl;
    }
};

class ListaObecnosci
{
private:
    Osoba osoby[MAX];
    int liczbaOsob;

    int znajdzIndexPoNrIndeksu(int nrIndeksuVal)
    {
        for(int i = 0; i < liczbaOsob; i++)
        {
            if(osoby[i].pobierzNrIndeksu() == nrIndeksuVal)
            {
                return i;
            }
        }
        return -1;
    }

public:
    ListaObecnosci()
    {
        liczbaOsob = 0;
    }

    bool czyIstniejeIndeks(int nrIndeksuVal)
    {
        if(znajdzIndexPoNrIndeksu(nrIndeksuVal) != -1)
        {
            return true;
        }
        return false;
    }

    void dodajOsobe(int nrIndeksuVal, string imieVal, string nazwiskoVal, bool obecnyVal)
    {
        if(liczbaOsob < MAX)
        {
            osoby[liczbaOsob] = Osoba(nrIndeksuVal, imieVal, nazwiskoVal, obecnyVal);
            liczbaOsob++;
        }
    }

    void ustawObecnosc(int nrIndeksuVal, bool obecnosci)
    {
        int idx = znajdzIndexPoNrIndeksu(nrIndeksuVal);

        if(idx != -1)
        {
            osoby[idx].ustawObecnosc(obecnosci);
        }
    }

    bool edytujOsobe(int nrIndeksuVal, int nowyNrIndeksu, string noweImie, string noweNazwisko, bool zmienicObecnosc, bool nowaObecnosc)
    {
        int idx = znajdzIndexPoNrIndeksu(nrIndeksuVal);

        if(idx == -1)
        {
            return false;
        }

        if(nowyNrIndeksu > 0 && nowyNrIndeksu != nrIndeksuVal)
        {
            if(czyIstniejeIndeks(nowyNrIndeksu))
            {
                return false;
            }
            osoby[idx].ustawNrIndeksu(nowyNrIndeksu);
        }

        if(noweImie != "" && noweImie != "-")
        {
            osoby[idx].ustawImie(noweImie);
        }

        if(noweNazwisko != "" && noweNazwisko != "-")
        {
            osoby[idx].ustawNazwisko(noweNazwisko);
        }

        if(zmienicObecnosc)
        {
            osoby[idx].ustawObecnosc(nowaObecnosc);
        }

        return true;
    }

    bool usunOsobe(int nrIndeksuVal)
    {
        int idx = znajdzIndexPoNrIndeksu(nrIndeksuVal);

        if(idx == -1)
        {
            return false;
        }

        for(int i = idx; i < liczbaOsob - 1; i++)
        {
            osoby[i] = osoby[i + 1];
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
            osoby[i].drukuj();
        }
    }
};

int main()
{
    ListaObecnosci lista;

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

                if(lista.czyIstniejeIndeks(nrIndeksuVal))
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

                lista.dodajOsobe(nrIndeksuVal, imieVal, nazwiskoVal, obecnyVal);
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

                bool ok = lista.edytujOsobe(nrIndeksuVal, nowyNrIndeksu, noweImie, noweNazwisko, zmienicObecnosc, nowaObecnosc);

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

                bool ok = lista.usunOsobe(nrIndeksuVal);

                if(!ok)
                {
                    cout << "Nie znaleziono osoby o tym numerze indeksu.\n";
                }
                break;
            }

            case '4':
            {
                lista.drukujListe();
                break;
            }

            case '5':
            {
                cout << "Koniec.\n";
                break;
            }

            default:
            {
                cout << "Nieprawidlowy wybor.\n";
            }
        }

    } while(wybor != '5');

    return 0;
}