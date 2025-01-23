/// \file RowData.cpp
/// \brief Implementacja klasy RowData do obs³ugi danych wierszy z pliku CSV.

#include "RowData.h"
#include "LogManager.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

/// \brief Konstruktor przetwarzaj¹cy wiersz danych z formatu CSV.
/// \param line Wiersz danych wejœciowych, zawieraj¹cy wartoœci oddzielone przecinkami.
/// Konstruktor dzieli wiersz na poszczególne elementy, konwertuje wartoœci na odpowiednie typy
/// i zapisuje je w odpowiednich polach obiektu.
RowData::RowData(const string& line) {
    vector<string> values; ///< Wektor przechowuj¹cy rozdzielone wartoœci z wiersza CSV.
    stringstream ss(line); ///< Strumieñ do rozdzielania wiersza na elementy.
    string value; ///< Zmienna do przechowywania pojedynczej wartoœci wczytanej z wiersza.

    // Przetwarzanie ka¿dej wartoœci z wiersza CSV, usuwanie cudzys³owów i dodawanie do wektora.
    while (getline(ss, value, ',')) {
        value.erase(remove(value.begin(), value.end(), '\"'), value.end()); ///< Usuwanie cudzys³owów.
        values.push_back(value); ///< Dodawanie wartoœci do wektora.
    }

    // Inicjalizacja pól obiektu na podstawie wczytanych wartoœci.
    this->date = values[0]; ///< Data wiersza.
    this->selfConsumption = stof(values[1]); ///< Autokonsumpcja (w watach).
    this->exportValue = stof(values[2]); ///< Eksport energii (w watach).
    this->importValue = stof(values[3]); ///< Import energii (w watach).
    this->consumption = stof(values[4]); ///< Pobór energii (w watach).
    this->production = stof(values[5]); ///< Produkcja energii (w watach).

    globalLogger.log("Wczytano linie: " + this->toString()); ///< Logowanie wczytanego wiersza.
}

/// \brief Konstruktor odczytuj¹cy dane z pliku binarnego.
/// \param in Strumieñ wejœciowy, z którego wczytywane s¹ dane z pliku binarnego.
/// Konstruktor ten deserializuje dane zapisane w pliku binarnym i inicjalizuje obiekt na ich podstawie.
RowData::RowData(ifstream& in) {
    loadFromBinary(in); ///< Deserializacja danych z pliku binarnego.
}

/// \brief Wypisuje wszystkie dane na standardowe wyjœcie.
/// Funkcja ta drukuje datê oraz wszystkie wartoœci energetyczne obiektu wiersza.
void RowData::display() const {
    cout << date << " " << selfConsumption << " " << exportValue << " " << importValue << " " << consumption << " " << production << endl;
}

/// \brief Wypisuje tylko dane liczbowe (bez daty) na standardowe wyjœcie.
/// Drukuje tylko wartoœci energetyczne, pomijaj¹c datê.
void RowData::displayData() const {
    cout << "\t\t\t\t" << selfConsumption << " " << exportValue << " " << importValue << " " << consumption << " " << production << endl;
}

/// \brief Zwraca dane jako ci¹g znaków.
/// \return Dane w formacie tekstowym, zawieraj¹ce wszystkie wartoœci wiersza.
/// Funkcja ta zamienia dane obiektu na ci¹g znaków, co mo¿e byæ przydatne do zapisania
/// lub wyœwietlenia danych w postaci tekstowej.
string RowData::toString() {
    return date + " " + to_string(selfConsumption) + " " + to_string(exportValue) + " " + to_string(importValue) + " " +
        to_string(consumption) + " " + to_string(production);
}

/// \brief Serializuje obiekt do pliku binarnego.
/// \param out Strumieñ wyjœciowy, do którego zapisane bêd¹ dane obiektu.
/// Funkcja zapisuje dane obiektu w formacie binarnym, umo¿liwiaj¹c ich póŸniejsze odczytanie.
void RowData::saveToBinary(ofstream& out) const {
    size_t dateSize = date.size(); ///< Rozmiar daty wiersza w bajtach.
    out.write(reinterpret_cast<const char*>(&dateSize), sizeof(dateSize)); ///< Zapisanie rozmiaru daty.
    out.write(date.c_str(), dateSize); ///< Zapisanie daty w postaci tekstowej.
    out.write(reinterpret_cast<const char*>(&selfConsumption), sizeof(selfConsumption)); ///< Zapisanie wartoœci autokonsumpcji.
    out.write(reinterpret_cast<const char*>(&exportValue), sizeof(exportValue)); ///< Zapisanie wartoœci eksportu.
    out.write(reinterpret_cast<const char*>(&importValue), sizeof(importValue)); ///< Zapisanie wartoœci importu.
    out.write(reinterpret_cast<const char*>(&consumption), sizeof(consumption)); ///< Zapisanie wartoœci poboru.
    out.write(reinterpret_cast<const char*>(&production), sizeof(production)); ///< Zapisanie wartoœci produkcji.
}

/// \brief Deserializuje obiekt z pliku binarnego.
/// \param in Strumieñ wejœciowy, z którego wczytywane bêd¹ zserializowane dane obiektu.
/// Funkcja ta odczytuje dane zapisane w formacie binarnym i rekonstruuje obiekt na ich podstawie.
void RowData::loadFromBinary(ifstream& in) {
    size_t dateSize; ///< Zmienna przechowuj¹ca rozmiar daty.
    in.read(reinterpret_cast<char*>(&dateSize), sizeof(dateSize)); ///< Wczytanie rozmiaru daty.
    date.resize(dateSize); ///< Zmienna do przechowywania daty.
    in.read(&date[0], dateSize); ///< Wczytanie samej daty.
    in.read(reinterpret_cast<char*>(&selfConsumption), sizeof(selfConsumption)); ///< Wczytanie wartoœci autokonsumpcji.
    in.read(reinterpret_cast<char*>(&exportValue), sizeof(exportValue)); ///< Wczytanie wartoœci eksportu.
    in.read(reinterpret_cast<char*>(&importValue), sizeof(importValue)); ///< Wczytanie wartoœci importu.
    in.read(reinterpret_cast<char*>(&consumption), sizeof(consumption)); ///< Wczytanie wartoœci poboru.
    in.read(reinterpret_cast<char*>(&production), sizeof(production)); ///< Wczytanie wartoœci produkcji.
}
