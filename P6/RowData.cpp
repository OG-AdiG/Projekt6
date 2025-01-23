/// \file RowData.cpp
/// \brief Implementacja klasy RowData do obs�ugi danych wierszy z pliku CSV.

#include "RowData.h"
#include "LogManager.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

/// \brief Konstruktor przetwarzaj�cy wiersz danych z formatu CSV.
/// \param line Wiersz danych wej�ciowych, zawieraj�cy warto�ci oddzielone przecinkami.
/// Konstruktor dzieli wiersz na poszczeg�lne elementy, konwertuje warto�ci na odpowiednie typy
/// i zapisuje je w odpowiednich polach obiektu.
RowData::RowData(const string& line) {
    vector<string> values; ///< Wektor przechowuj�cy rozdzielone warto�ci z wiersza CSV.
    stringstream ss(line); ///< Strumie� do rozdzielania wiersza na elementy.
    string value; ///< Zmienna do przechowywania pojedynczej warto�ci wczytanej z wiersza.

    // Przetwarzanie ka�dej warto�ci z wiersza CSV, usuwanie cudzys�ow�w i dodawanie do wektora.
    while (getline(ss, value, ',')) {
        value.erase(remove(value.begin(), value.end(), '\"'), value.end()); ///< Usuwanie cudzys�ow�w.
        values.push_back(value); ///< Dodawanie warto�ci do wektora.
    }

    // Inicjalizacja p�l obiektu na podstawie wczytanych warto�ci.
    this->date = values[0]; ///< Data wiersza.
    this->selfConsumption = stof(values[1]); ///< Autokonsumpcja (w watach).
    this->exportValue = stof(values[2]); ///< Eksport energii (w watach).
    this->importValue = stof(values[3]); ///< Import energii (w watach).
    this->consumption = stof(values[4]); ///< Pob�r energii (w watach).
    this->production = stof(values[5]); ///< Produkcja energii (w watach).

    globalLogger.log("Wczytano linie: " + this->toString()); ///< Logowanie wczytanego wiersza.
}

/// \brief Konstruktor odczytuj�cy dane z pliku binarnego.
/// \param in Strumie� wej�ciowy, z kt�rego wczytywane s� dane z pliku binarnego.
/// Konstruktor ten deserializuje dane zapisane w pliku binarnym i inicjalizuje obiekt na ich podstawie.
RowData::RowData(ifstream& in) {
    loadFromBinary(in); ///< Deserializacja danych z pliku binarnego.
}

/// \brief Wypisuje wszystkie dane na standardowe wyj�cie.
/// Funkcja ta drukuje dat� oraz wszystkie warto�ci energetyczne obiektu wiersza.
void RowData::display() const {
    cout << date << " " << selfConsumption << " " << exportValue << " " << importValue << " " << consumption << " " << production << endl;
}

/// \brief Wypisuje tylko dane liczbowe (bez daty) na standardowe wyj�cie.
/// Drukuje tylko warto�ci energetyczne, pomijaj�c dat�.
void RowData::displayData() const {
    cout << "\t\t\t\t" << selfConsumption << " " << exportValue << " " << importValue << " " << consumption << " " << production << endl;
}

/// \brief Zwraca dane jako ci�g znak�w.
/// \return Dane w formacie tekstowym, zawieraj�ce wszystkie warto�ci wiersza.
/// Funkcja ta zamienia dane obiektu na ci�g znak�w, co mo�e by� przydatne do zapisania
/// lub wy�wietlenia danych w postaci tekstowej.
string RowData::toString() {
    return date + " " + to_string(selfConsumption) + " " + to_string(exportValue) + " " + to_string(importValue) + " " +
        to_string(consumption) + " " + to_string(production);
}

/// \brief Serializuje obiekt do pliku binarnego.
/// \param out Strumie� wyj�ciowy, do kt�rego zapisane b�d� dane obiektu.
/// Funkcja zapisuje dane obiektu w formacie binarnym, umo�liwiaj�c ich p�niejsze odczytanie.
void RowData::saveToBinary(ofstream& out) const {
    size_t dateSize = date.size(); ///< Rozmiar daty wiersza w bajtach.
    out.write(reinterpret_cast<const char*>(&dateSize), sizeof(dateSize)); ///< Zapisanie rozmiaru daty.
    out.write(date.c_str(), dateSize); ///< Zapisanie daty w postaci tekstowej.
    out.write(reinterpret_cast<const char*>(&selfConsumption), sizeof(selfConsumption)); ///< Zapisanie warto�ci autokonsumpcji.
    out.write(reinterpret_cast<const char*>(&exportValue), sizeof(exportValue)); ///< Zapisanie warto�ci eksportu.
    out.write(reinterpret_cast<const char*>(&importValue), sizeof(importValue)); ///< Zapisanie warto�ci importu.
    out.write(reinterpret_cast<const char*>(&consumption), sizeof(consumption)); ///< Zapisanie warto�ci poboru.
    out.write(reinterpret_cast<const char*>(&production), sizeof(production)); ///< Zapisanie warto�ci produkcji.
}

/// \brief Deserializuje obiekt z pliku binarnego.
/// \param in Strumie� wej�ciowy, z kt�rego wczytywane b�d� zserializowane dane obiektu.
/// Funkcja ta odczytuje dane zapisane w formacie binarnym i rekonstruuje obiekt na ich podstawie.
void RowData::loadFromBinary(ifstream& in) {
    size_t dateSize; ///< Zmienna przechowuj�ca rozmiar daty.
    in.read(reinterpret_cast<char*>(&dateSize), sizeof(dateSize)); ///< Wczytanie rozmiaru daty.
    date.resize(dateSize); ///< Zmienna do przechowywania daty.
    in.read(&date[0], dateSize); ///< Wczytanie samej daty.
    in.read(reinterpret_cast<char*>(&selfConsumption), sizeof(selfConsumption)); ///< Wczytanie warto�ci autokonsumpcji.
    in.read(reinterpret_cast<char*>(&exportValue), sizeof(exportValue)); ///< Wczytanie warto�ci eksportu.
    in.read(reinterpret_cast<char*>(&importValue), sizeof(importValue)); ///< Wczytanie warto�ci importu.
    in.read(reinterpret_cast<char*>(&consumption), sizeof(consumption)); ///< Wczytanie warto�ci poboru.
    in.read(reinterpret_cast<char*>(&production), sizeof(production)); ///< Wczytanie warto�ci produkcji.
}
