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

public:
    Osoba()
    {
        nrIndeksu = 0;
        imie = "";
        nazwisko = "";
    }

    Osoba(int nrIndeksuVal, string imieVal, string nazwiskoVal)
    {
        nrIndeksu = 0;
        imie = "";
        nazwisko = "";

        ustawNrIndeksu(nrIndeksuVal);
        ustawImie(imieVal);
        ustawNazwisko(nazwiskoVal);
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

    void ustawNrIndeksu(int nowyNrIndeksu)
    {
        if(nowyNrIndeksu > 0)
        {
            nrIndeksu = nowyNrIndeksu;
        }
    }

    void ustawImie(string noweImie)
    {
        if(noweImie.length() > 2)
        {
            imie = noweImie;
        }
    }

    void ustawNazwisko(string noweNazwisko)
    {
        if(noweNazwisko.length() > 2)
        {
            nazwisko = noweNazwisko;
        }
    }

    virtual void drukuj()
    {
        cout << nrIndeksu << " | " << imie << " | " << nazwisko;
    }
};

class ListaObecnosci
{
private:
    Osoba osoby[MAX];
    bool obecny[MAX];
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

        for(int i = 0; i < MAX; i++)
        {
            obecny[i] = false;
        }
    }

    bool czyIstniejeIndeks(int nrIndeksuVal)
    {
        if(znajdzIndexPoNrIndeksu(nrIndeksuVal) != -1)
        {
            return true;
        }

        return false;
    }

    bool dodajOsobe(int nrIndeksuVal, string imieVal, string nazwiskoVal, bool obecnyVal)
    {
        if(liczbaOsob >= MAX)
        {
            return false;
        }

        if(czyIstniejeIndeks(nrIndeksuVal))
        {
            return false;
        }

        osoby[liczbaOsob] = Osoba(nrIndeksuVal, imieVal, nazwiskoVal);
        obecny[liczbaOsob] = obecnyVal;
        liczbaOsob++;

        return true;
    }

    void ustawObecnosc(int nrIndeksuVal, bool obecnosc)
    {
        int idx = znajdzIndexPoNrIndeksu(nrIndeksuVal);

        if(idx != -1)
        {
            obecny[idx] = obecnosc;
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
            obecny[idx] = nowaObecnosc;
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
            obecny[i] = obecny[i + 1];
        }

        liczbaOsob--;
        obecny[liczbaOsob] = false;

        return true;
    }

    void drukujListe()
    {
        cout << "\nLista obecnosci:\n";
        cout << "Nr indeksu | Imie | Nazwisko | Obecny\n";

        for(int i = 0; i < liczbaOsob; i++)
        {
            osoby[i].drukuj();
            cout << " | " << (obecny[i] ? 1 : 0) << endl;
        }

        if(liczbaOsob == 0)
        {
            cout << "Lista jest pusta.\n";
        }
    }
};

class Interfejs
{
private:
    ListaObecnosci analiza1;
    ListaObecnosci ppo1;
    ListaObecnosci* lista;
    string nazwaListy;

    void wybierzListe()
    {
        char wyborListy;

        cout << "\nWybierz liste:\n";
        cout << " 1 - Analiza 1\n";
        cout << " 2 - PPO 1\n";
        cout << "Wybierz opcje: ";
        cin >> wyborListy;

        if(wyborListy == '2')
        {
            lista = &ppo1;
            nazwaListy = "PPO 1";
        }
        else
        {
            lista = &analiza1;
            nazwaListy = "Analiza 1";
        }
    }

    void drukujMenu()
    {
        cout << "\nMenu - aktualna lista: " << nazwaListy << endl;
        cout << " 1 - dodaj osobe\n";
        cout << " 2 - edytuj osobe\n";
        cout << " 3 - usun osobe\n";
        cout << " 4 - ustaw obecnosc\n";
        cout << " 5 - pokaz liste\n";
        cout << " 6 - zmien liste\n";
        cout << " 7 - zakoncz\n";
        cout << "Wybierz opcje: ";
    }

    void akcjaDodajOsobe()
    {
        int nrIndeksuVal;
        string imieVal;
        string nazwiskoVal;
        bool obecnyVal;

        cout << "Podaj nr indeksu: ";
        cin >> nrIndeksuVal;

        if(lista->czyIstniejeIndeks(nrIndeksuVal))
        {
            cout << "Ten nr indeksu jest juz zajety.\n";
            return;
        }

        cout << "Podaj imie: ";
        cin >> imieVal;

        cout << "Podaj nazwisko: ";
        cin >> nazwiskoVal;

        cout << "Czy osoba byla obecna? (1 tak, 0 nie): ";
        cin >> obecnyVal;

        bool ok = lista->dodajOsobe(nrIndeksuVal, imieVal, nazwiskoVal, obecnyVal);

        if(ok)
        {
            cout << "Osoba dodana.\n";
        }
        else
        {
            cout << "Nie dodano osoby. Lista jest pelna albo dane sa niepoprawne.\n";
        }
    }

    void akcjaEdytujOsobe()
    {
        int nrIndeksuVal;
        int nowyNrIndeksu;
        string noweImie;
        string noweNazwisko;
        int obecnoscInput;
        bool zmienicObecnosc = false;
        bool nowaObecnosc = false;

        cout << "Podaj nr indeksu osoby do edycji: ";
        cin >> nrIndeksuVal;

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

        bool ok = lista->edytujOsobe(nrIndeksuVal, nowyNrIndeksu, noweImie, noweNazwisko, zmienicObecnosc, nowaObecnosc);

        if(ok)
        {
            cout << "Osoba edytowana.\n";
        }
        else
        {
            cout << "Nie znaleziono osoby lub nr indeksu docelowy jest zajety.\n";
        }
    }

    void akcjaUsunOsobe()
    {
        int nrIndeksuVal;

        cout << "Podaj nr indeksu osoby do usuniecia: ";
        cin >> nrIndeksuVal;

        bool ok = lista->usunOsobe(nrIndeksuVal);

        if(ok)
        {
            cout << "Osoba usunieta.\n";
        }
        else
        {
            cout << "Nie znaleziono osoby o tym numerze indeksu.\n";
        }
    }

    void akcjaUstawObecnosc()
    {
        int nrIndeksuVal;
        int obecnoscInput;

        cout << "Podaj nr indeksu osoby: ";
        cin >> nrIndeksuVal;

        if(!lista->czyIstniejeIndeks(nrIndeksuVal))
        {
            cout << "Nie znaleziono osoby o tym numerze indeksu.\n";
            return;
        }

        cout << "Obecnosc (1 tak, 0 nie): ";
        cin >> obecnoscInput;

        lista->ustawObecnosc(nrIndeksuVal, obecnoscInput == 1);

        cout << "Obecnosc zmieniona.\n";
    }

public:
    Interfejs()
    {
        lista = &analiza1;
        nazwaListy = "Analiza 1";
    }

    void petla()
    {
        char wybor;

        wybierzListe();

        do
        {
            drukujMenu();
            cin >> wybor;

            switch(wybor)
            {
                case '1':
                {
                    akcjaDodajOsobe();
                    break;
                }

                case '2':
                {
                    akcjaEdytujOsobe();
                    break;
                }

                case '3':
                {
                    akcjaUsunOsobe();
                    break;
                }

                case '4':
                {
                    akcjaUstawObecnosc();
                    break;
                }

                case '5':
                {
                    lista->drukujListe();
                    break;
                }

                case '6':
                {
                    wybierzListe();
                    break;
                }

                case '7':
                {
                    cout << "Koniec.\n";
                    break;
                }

                default:
                {
                    cout << "Nieprawidlowy wybor.\n";
                }
            }

        } while(wybor != '7');
    }
};

int main()
{
    Interfejs interfejs;
    interfejs.petla();

    return 0;
}