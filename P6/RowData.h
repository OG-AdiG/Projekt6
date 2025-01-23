/// \file RowData.h
/// \brief Deklaracja klasy RowData do przechowywania i przetwarzania danych z pliku CSV.

#ifndef ROWDATA_H
#define ROWDATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/// \class RowData
/// \brief Klasa reprezentuj¹ca dane jednego wiersza z pliku CSV, zawieraj¹ca ró¿ne parametry energetyczne.
class RowData {
public:
    /// \brief Konstruktor przetwarzaj¹cy wiersz danych wejœciowych w formacie CSV.
    /// \param line Wiersz danych w formacie tekstowym, zawieraj¹cy ró¿ne wartoœci oddzielone przecinkami.
    /// Przetwarza wiersz CSV na odpowiednie pola obiektu, konwertuj¹c wartoœci na odpowiednie typy.
    RowData(const string& line);

    /// \brief Konstruktor odczytuj¹cy dane z pliku binarnego.
    /// \param in Strumieñ wejœciowy, z którego odczytywane s¹ zserializowane dane.
    /// Inicjalizuje obiekt na podstawie zserializowanych danych zapisanych w pliku binarnym.
    RowData(ifstream& in);

    /// \brief Wypisuje wszystkie dane obiektu na standardowe wyjœcie.
    /// Funkcja ta drukuje pe³ne dane wiersza, w tym datê i wszystkie wartoœci energetyczne.
    void display() const;

    /// \brief Wypisuje tylko wartoœci energetyczne, pomijaj¹c datê, na standardowe wyjœcie.
    /// Drukuje wartoœci autokonsumpcji, eksportu, importu, poboru i produkcji, ale bez daty.
    void displayData() const;

    /// \brief Zwraca dane w formie tekstowego ci¹gu znaków.
    /// \return Dane w formacie tekstowym, które reprezentuj¹ wszystkie wartoœci wiersza.
    /// Funkcja ta zamienia dane obiektu na jedn¹ liniê tekstu w celu ³atwego zapisu lub wyœwietlenia.
    string toString();

    /// \brief Serializuje obiekt do pliku binarnego.
    /// \param out Strumieñ wyjœciowy, do którego zapisane bêd¹ dane obiektu w formacie binarnym.
    /// Funkcja ta zapisuje wszystkie wartoœci obiektu w postaci binarnej, umo¿liwiaj¹c póŸniejsze odczytanie.
    void saveToBinary(ofstream& out) const;

    /// \brief Deserializuje obiekt z pliku binarnego.
    /// \param in Strumieñ wejœciowy, z którego wczytywane bêd¹ zserializowane dane obiektu.
    /// Inicjalizuje obiekt na podstawie danych w formacie binarnym.
    void loadFromBinary(ifstream& in);

    /// \brief Zwraca datê, która znajduje siê w wierszu.
    /// \return Data wiersza w formacie tekstowym (np. "YYYY-MM-DD").
    /// Funkcja ta umo¿liwia pobranie daty przypisanej do danego wiersza danych.
    string getDate() const { return date; }

    /// \brief Zwraca wartoœæ autokonsumpcji z wiersza danych.
    /// \return Wartoœæ autokonsumpcji w watach (W) jako liczba zmiennoprzecinkowa.
    /// Funkcja ta umo¿liwia dostêp do wartoœci autokonsumpcji dla danego wiersza danych.
    float getSelfConsumption() const { return selfConsumption; }

    /// \brief Zwraca wartoœæ eksportu z wiersza danych.
    /// \return Wartoœæ eksportu w watach (W) jako liczba zmiennoprzecinkowa.
    /// Funkcja ta zwraca wartoœæ eksportu energii przypisan¹ do danego wiersza.
    float getExport() const { return exportValue; }

    /// \brief Zwraca wartoœæ importu z wiersza danych.
    /// \return Wartoœæ importu w watach (W) jako liczba zmiennoprzecinkowa.
    /// Funkcja ta zwraca wartoœæ importu energii dla danego wiersza.
    float getImport() const { return importValue; }

    /// \brief Zwraca wartoœæ poboru energii z wiersza danych.
    /// \return Wartoœæ poboru energii w watach (W) jako liczba zmiennoprzecinkowa.
    /// Funkcja ta zwraca wartoœæ poboru energii z sieci przypisan¹ do danego wiersza danych.
    float getConsumption() const { return consumption; }

    /// \brief Zwraca wartoœæ produkcji energii z wiersza danych.
    /// \return Wartoœæ produkcji energii w watach (W) jako liczba zmiennoprzecinkowa.
    /// Funkcja ta umo¿liwia dostêp do wartoœci produkcji energii przypisanej do danego wiersza.
    float getProduction() const { return production; }

private:
    string date; ///< Data wiersza w formacie tekstowym (np. "YYYY-MM-DD").
    float selfConsumption; ///< Autokonsumpcja w watach (W), iloœæ energii zu¿ytej lokalnie.
    float exportValue; ///< Eksport energii w watach (W), iloœæ energii oddanej do sieci.
    float importValue; ///< Import energii w watach (W), iloœæ energii pobranej z sieci.
    float consumption; ///< Pobór energii z sieci w watach (W).
    float production; ///< Produkcja energii w watach (W), energia wytworzona przez system.
};

#endif // ROWDATA_H
