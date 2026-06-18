#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

class IWyswietlany
{
public:
    virtual void wyswietl() = 0;
    virtual ~IWyswietlany() {}
};

class Osoba : public IWyswietlany
{
protected:
    string imie;
    string nazwisko;
    string nrIndeksu;

public:
    Osoba()
    {
        imie = "";
        nazwisko = "";
        nrIndeksu = "";
    }

    Osoba(string _imie, string _nazwisko, string _nrIndeksu)
    {
        ustawImie(_imie);
        ustawNazwisko(_nazwisko);
        ustawNrIndeksu(_nrIndeksu);
    }

    virtual ~Osoba() {}

    void ustawImie(string _imie)
    {
        if(_imie.length() > 2)
        {
            imie = _imie;
        }
    }

    void ustawNazwisko(string _nazwisko)
    {
        if(_nazwisko.length() > 2)
        {
            nazwisko = _nazwisko;
        }
    }

    void ustawNrIndeksu(string _nrIndeksu)
    {
        if(_nrIndeksu != "")
        {
            nrIndeksu = _nrIndeksu;
        }
    }

    string pobierzImie()
    {
        return imie;
    }

    string pobierzNazwisko()
    {
        return nazwisko;
    }

    string pobierzNrIndeksu()
    {
        return nrIndeksu;
    }

    virtual void wyswietl()
    {
        cout << "OSOBA " << nrIndeksu << " | " << imie << " " << nazwisko;
    }
};

class Student : public Osoba
{
public:
    Student()
        : Osoba()
    {

    }

    Student(string _imie, string _nazwisko, string _nrIndeksu)
        : Osoba(_imie, _nazwisko, _nrIndeksu)
    {

    }

    void wyswietl()
    {
        cout << "STUDENT " << nrIndeksu << " | " << imie << " " << nazwisko;
    }
};

class Pracownik : public Osoba
{
public:
    Pracownik()
        : Osoba()
    {

    }

    Pracownik(string _imie, string _nazwisko, string _nrIndeksu)
        : Osoba(_imie, _nazwisko, _nrIndeksu)
    {

    }

    void wyswietl()
    {
        cout << "PRACOWNIK " << nrIndeksu << " | " << imie << " " << nazwisko;
    }
};

class ListaObecnosci : public IWyswietlany
{
private:
    Osoba* osoby[MAX];
    bool obecny[MAX];
    int liczbaOsob;

    int znajdzIndexPoNrIndeksu(string nrIndeksu)
    {
        for(int i = 0; i < liczbaOsob; i++)
        {
            if(osoby[i]->pobierzNrIndeksu() == nrIndeksu)
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
            osoby[i] = nullptr;
            obecny[i] = false;
        }
    }

    ~ListaObecnosci()
    {
        for(int i = 0; i < liczbaOsob; i++)
        {
            delete osoby[i];
            osoby[i] = nullptr;
        }
    }

    bool czyIstniejeIndeks(string nrIndeksu)
    {
        if(znajdzIndexPoNrIndeksu(nrIndeksu) != -1)
        {
            return true;
        }

        return false;
    }

    void dodajOsobe(int typOsoby, string imie, string nazwisko, string nrIndeksu, bool czyObecny)
    {
        if(liczbaOsob < MAX)
        {
            if(typOsoby == 2)
            {
                osoby[liczbaOsob] = new Student(imie, nazwisko, nrIndeksu);
            }
            else if(typOsoby == 3)
            {
                osoby[liczbaOsob] = new Pracownik(imie, nazwisko, nrIndeksu);
            }
            else
            {
                osoby[liczbaOsob] = new Osoba(imie, nazwisko, nrIndeksu);
            }

            obecny[liczbaOsob] = czyObecny;
            liczbaOsob++;
        }
    }

    bool usunOsobe(string nrIndeksu)
    {
        int idx = znajdzIndexPoNrIndeksu(nrIndeksu);

        if(idx == -1)
        {
            return false;
        }

        delete osoby[idx];

        for(int i = idx; i < liczbaOsob - 1; i++)
        {
            osoby[i] = osoby[i + 1];
            obecny[i] = obecny[i + 1];
        }

        liczbaOsob--;
        osoby[liczbaOsob] = nullptr;
        obecny[liczbaOsob] = false;

        return true;
    }

    bool ustawObecnosc(string nrIndeksu, bool stan)
    {
        int idx = znajdzIndexPoNrIndeksu(nrIndeksu);

        if(idx == -1)
        {
            return false;
        }

        obecny[idx] = stan;
        return true;
    }

    Osoba* pobierzOsobe(string nrIndeksu)
    {
        int idx = znajdzIndexPoNrIndeksu(nrIndeksu);

        if(idx == -1)
        {
            return nullptr;
        }

        return osoby[idx];
    }

    void wyswietl()
    {
        if(liczbaOsob == 0)
        {
            cout << "Lista jest pusta.\n";
            return;
        }

        for(int i = 0; i < liczbaOsob; i++)
        {
            cout << "[" << i << "] ";
            osoby[i]->wyswietl();

            if(obecny[i])
            {
                cout << " | Obecny";
            }
            else
            {
                cout << " | Nieobecny";
            }

            cout << endl;
        }
    }
};

class Interfejs
{
private:
    ListaObecnosci analiza1;
    ListaObecnosci ppo1;
    ListaObecnosci* lista;

    void wybierzListe()
    {
        int wybor;

        cout << "\nWybierz kurs:\n";
        cout << "1. Analiza 1\n";
        cout << "2. PPO 1\n";
        cout << "Wybor: ";
        cin >> wybor;

        if(wybor == 2)
        {
            lista = &ppo1;
        }
        else
        {
            lista = &analiza1;
        }
    }

    void wyswietlMenu()
    {
        cout << "\n=============================\n";
        cout << "  MENU LISTY OBECNOSCI\n";
        cout << "=============================\n";
        cout << "1. Dodaj osobe\n";
        cout << "2. Edytuj osobe\n";
        cout << "3. Usun osobe\n";
        cout << "4. Ustaw obecnosc\n";
        cout << "5. Zmien imie osoby\n";
        cout << "6. Zmien nazwisko osoby\n";
        cout << "7. Zmien numer indeksu osoby\n";
        cout << "8. Wyswietl wybrany kurs\n";
        cout << "9. Wyswietl wszystkie kursy\n";
        cout << "0. Wyjscie\n";
        cout << "Wybor: ";
    }

    void akcjaDodajOsobe()
    {
        wybierzListe();

        int typOsoby;
        string imie;
        string nazwisko;
        string nrIndeksu;
        bool czyObecny;

        cout << "Podaj typ osoby:\n";
        cout << "1. Osoba\n";
        cout << "2. Student\n";
        cout << "3. Pracownik\n";
        cout << "Wybor: ";
        cin >> typOsoby;

        cout << "Imie: ";
        cin >> imie;

        cout << "Nazwisko: ";
        cin >> nazwisko;

        cout << "Numer indeksu / identyfikator: ";
        cin >> nrIndeksu;

        cout << "Czy osoba byla obecna? (1 tak, 0 nie): ";
        cin >> czyObecny;

        if(lista->czyIstniejeIndeks(nrIndeksu))
        {
            cout << "Osoba o takim numerze indeksu juz istnieje na tym kursie.\n";
            return;
        }

        lista->dodajOsobe(typOsoby, imie, nazwisko, nrIndeksu, czyObecny);

        cout << "Osoba dodana.\n";
    }

    void akcjaEdytujOsobe()
    {
        wybierzListe();

        string szukanyIndeks;
        string imie;
        string nazwisko;
        string nowyIndeks;
        char stan;

        cout << "Podaj numer indeksu osoby do edycji: ";
        cin >> szukanyIndeks;

        Osoba* osoba = lista->pobierzOsobe(szukanyIndeks);

        if(osoba == nullptr)
        {
            cout << "Brak osoby o podanym numerze indeksu na tym kursie.\n";
            return;
        }

        cout << "Nowe imie (- zostaw bez zmian): ";
        cin >> imie;

        if(imie != "-")
        {
            osoba->ustawImie(imie);
        }

        cout << "Nowe nazwisko (- zostaw bez zmian): ";
        cin >> nazwisko;

        if(nazwisko != "-")
        {
            osoba->ustawNazwisko(nazwisko);
        }

        cout << "Nowy numer indeksu (- zostaw bez zmian): ";
        cin >> nowyIndeks;

        if(nowyIndeks != "-")
        {
            if(lista->czyIstniejeIndeks(nowyIndeks))
            {
                cout << "Ten numer indeksu jest juz zajety na tym kursie.\n";
            }
            else
            {
                osoba->ustawNrIndeksu(nowyIndeks);
                szukanyIndeks = nowyIndeks;
            }
        }

        cout << "Obecnosc (t = obecny, n = nieobecny, - = zostaw): ";
        cin >> stan;

        if(stan == 't' || stan == 'T')
        {
            lista->ustawObecnosc(szukanyIndeks, true);
        }
        else if(stan == 'n' || stan == 'N')
        {
            lista->ustawObecnosc(szukanyIndeks, false);
        }

        cout << "Dane osoby zaktualizowane.\n";
    }

    void akcjaUsunOsobe()
    {
        wybierzListe();

        string nrIndeksu;

        cout << "Podaj numer indeksu osoby do usuniecia: ";
        cin >> nrIndeksu;

        bool ok = lista->usunOsobe(nrIndeksu);

        if(ok)
        {
            cout << "Osoba usunieta.\n";
        }
        else
        {
            cout << "Brak osoby o podanym numerze indeksu na tym kursie.\n";
        }
    }

    void akcjaUstawObecnosc()
    {
        wybierzListe();

        string nrIndeksu;
        char stan;

        cout << "Podaj numer indeksu osoby: ";
        cin >> nrIndeksu;

        cout << "Obecnosc (t = obecny, n = nieobecny): ";
        cin >> stan;

        bool ok = lista->ustawObecnosc(nrIndeksu, stan == 't' || stan == 'T');

        if(ok)
        {
            cout << "Obecnosc zaktualizowana.\n";
        }
        else
        {
            cout << "Brak osoby o podanym numerze indeksu na tym kursie.\n";
        }
    }

    void akcjaZmienImie()
    {
        wybierzListe();

        string nrIndeksu;
        string imie;

        cout << "Podaj numer indeksu osoby: ";
        cin >> nrIndeksu;

        Osoba* osoba = lista->pobierzOsobe(nrIndeksu);

        if(osoba == nullptr)
        {
            cout << "Brak osoby o podanym numerze indeksu na tym kursie.\n";
            return;
        }

        cout << "Nowe imie: ";
        cin >> imie;

        osoba->ustawImie(imie);
        cout << "Imie zmienione.\n";
    }

    void akcjaZmienNazwisko()
    {
        wybierzListe();

        string nrIndeksu;
        string nazwisko;

        cout << "Podaj numer indeksu osoby: ";
        cin >> nrIndeksu;

        Osoba* osoba = lista->pobierzOsobe(nrIndeksu);

        if(osoba == nullptr)
        {
            cout << "Brak osoby o podanym numerze indeksu na tym kursie.\n";
            return;
        }

        cout << "Nowe nazwisko: ";
        cin >> nazwisko;

        osoba->ustawNazwisko(nazwisko);
        cout << "Nazwisko zmienione.\n";
    }

    void akcjaZmienIndeks()
    {
        wybierzListe();

        string staryIndeks;
        string nowyIndeks;

        cout << "Podaj obecny numer indeksu osoby: ";
        cin >> staryIndeks;

        Osoba* osoba = lista->pobierzOsobe(staryIndeks);

        if(osoba == nullptr)
        {
            cout << "Brak osoby o podanym numerze indeksu na tym kursie.\n";
            return;
        }

        cout << "Nowy numer indeksu: ";
        cin >> nowyIndeks;

        if(lista->czyIstniejeIndeks(nowyIndeks))
        {
            cout << "Ten numer indeksu jest juz zajety na tym kursie.\n";
            return;
        }

        osoba->ustawNrIndeksu(nowyIndeks);
        cout << "Numer indeksu zmieniony.\n";
    }

    void akcjaWyswietlWybranyKurs()
    {
        wybierzListe();

        cout << "\n--- Wybrany kurs ---\n";
        lista->wyswietl();
    }

    void akcjaWyswietlWszystkieKursy()
    {
        cout << "\n--- Analiza 1 ---\n";
        analiza1.wyswietl();

        cout << "\n--- PPO 1 ---\n";
        ppo1.wyswietl();
    }

public:
    Interfejs()
    {
        lista = nullptr;
    }

    void uruchom()
    {
        int wybor;

        do
        {
            wyswietlMenu();
            cin >> wybor;

            switch(wybor)
            {
                case 1:
                {
                    akcjaDodajOsobe();
                    break;
                }

                case 2:
                {
                    akcjaEdytujOsobe();
                    break;
                }

                case 3:
                {
                    akcjaUsunOsobe();
                    break;
                }

                case 4:
                {
                    akcjaUstawObecnosc();
                    break;
                }

                case 5:
                {
                    akcjaZmienImie();
                    break;
                }

                case 6:
                {
                    akcjaZmienNazwisko();
                    break;
                }

                case 7:
                {
                    akcjaZmienIndeks();
                    break;
                }

                case 8:
                {
                    akcjaWyswietlWybranyKurs();
                    break;
                }

                case 9:
                {
                    akcjaWyswietlWszystkieKursy();
                    break;
                }

                case 0:
                {
                    cout << "Zamykanie...\n";
                    break;
                }

                default:
                {
                    cout << "Nieznana opcja.\n";
                }
            }

        } while(wybor != 0);
    }
};

int main()
{
    Interfejs interfejs;
    interfejs.uruchom();

    return 0;
}