#include <iostream>
#include <vector>
#include <string>

class Uczen {
public:
    int id;
    float numerRejestracyjny;
    std::string imie;
    std::string nazwisko;

    std::ostream& print(std::ostream& wyjscie) const {
        wyjscie << nazwisko << " " << imie << " " << numerRejestracyjny << " " << id;
        return wyjscie;
    }

    std::istream& read(std::istream& wejscie) {
        wejscie >> id >> numerRejestracyjny >> imie >> nazwisko;
        return wejscie;
    }
};

std::ostream& operator<<(std::ostream& wyjscie, const Uczen& obj) {
    return obj.print(wyjscie);
}

std::istream& operator>>(std::istream& wejscie, Uczen& obj) {
    return obj.read(wejscie);
}

bool porownaj(const Uczen& a, const Uczen& b) {
    if (a.nazwisko != b.nazwisko)
        return a.nazwisko < b.nazwisko;
    if (a.imie != b.imie)
        return a.imie < b.imie;
    if (a.numerRejestracyjny != b.numerRejestracyjny)
        return a.numerRejestracyjny < b.numerRejestracyjny;
    return a.id < b.id;
}

void scal(std::vector<Uczen>& tablica, int lewo, int srodek, int prawo) {
    int n1 = srodek - lewo + 1;
    int n2 = prawo - srodek;

    std::vector<Uczen> Lewa(n1), Prawa(n2);

    for (int i = 0; i < n1; i++)
        Lewa[i] = tablica[lewo + i];
    for (int j = 0; j < n2; j++)
        Prawa[j] = tablica[srodek + 1 + j];

    int i = 0, j = 0, k = lewo;
    while (i < n1 && j < n2) {
        if (porownaj(Lewa[i], Prawa[j])) {
            tablica[k] = Lewa[i];
            i++;
        } else {
            tablica[k] = Prawa[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        tablica[k] = Lewa[i];
        i++;
        k++;
    }

    while (j < n2) {
        tablica[k] = Prawa[j];
        j++;
        k++;
    }
}

void sortujPrzezScalanie(std::vector<Uczen>& tablica, int lewo, int prawo) {
    if (lewo >= prawo)
        return;

    int srodek = lewo + (prawo - lewo) / 2;
    sortujPrzezScalanie(tablica, lewo, srodek);
    sortujPrzezScalanie(tablica, srodek + 1, prawo);
    scal(tablica, lewo, srodek, prawo);
}

std::vector<Uczen> wczytajUczniow() {
    std::vector<Uczen> uczniowie;
    Uczen uczen;
    while (std::cin >> uczen) {
        uczniowie.push_back(uczen);
    }
    return uczniowie;
}

void wypiszUczniow(const std::vector<Uczen>& uczniowie) {
    for (size_t i = 0; i < uczniowie.size(); i++) {
        std::cout << i + 1 << " " << uczniowie[i] << "\n";
    }
}

int main() {
    std::vector<Uczen> uczniowie = wczytajUczniow();
    sortujPrzezScalanie(uczniowie, 0, uczniowie.size() - 1);
    wypiszUczniow(uczniowie);
    return 0;
}
