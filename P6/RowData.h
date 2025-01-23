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
/// \brief Klasa reprezentuj�ca dane jednego wiersza z pliku CSV, zawieraj�ca r�ne parametry energetyczne.
class RowData {
public:
    /// \brief Konstruktor przetwarzaj�cy wiersz danych wej�ciowych w formacie CSV.
    /// \param line Wiersz danych w formacie tekstowym, zawieraj�cy r�ne warto�ci oddzielone przecinkami.
    /// Przetwarza wiersz CSV na odpowiednie pola obiektu, konwertuj�c warto�ci na odpowiednie typy.
    RowData(const string& line);

    /// \brief Konstruktor odczytuj�cy dane z pliku binarnego.
    /// \param in Strumie� wej�ciowy, z kt�rego odczytywane s� zserializowane dane.
    /// Inicjalizuje obiekt na podstawie zserializowanych danych zapisanych w pliku binarnym.
    RowData(ifstream& in);

    /// \brief Wypisuje wszystkie dane obiektu na standardowe wyj�cie.
    /// Funkcja ta drukuje pe�ne dane wiersza, w tym dat� i wszystkie warto�ci energetyczne.
    void display() const;

    /// \brief Wypisuje tylko warto�ci energetyczne, pomijaj�c dat�, na standardowe wyj�cie.
    /// Drukuje warto�ci autokonsumpcji, eksportu, importu, poboru i produkcji, ale bez daty.
    void displayData() const;

    /// \brief Zwraca dane w formie tekstowego ci�gu znak�w.
    /// \return Dane w formacie tekstowym, kt�re reprezentuj� wszystkie warto�ci wiersza.
    /// Funkcja ta zamienia dane obiektu na jedn� lini� tekstu w celu �atwego zapisu lub wy�wietlenia.
    string toString();

    /// \brief Serializuje obiekt do pliku binarnego.
    /// \param out Strumie� wyj�ciowy, do kt�rego zapisane b�d� dane obiektu w formacie binarnym.
    /// Funkcja ta zapisuje wszystkie warto�ci obiektu w postaci binarnej, umo�liwiaj�c p�niejsze odczytanie.
    void saveToBinary(ofstream& out) const;

    /// \brief Deserializuje obiekt z pliku binarnego.
    /// \param in Strumie� wej�ciowy, z kt�rego wczytywane b�d� zserializowane dane obiektu.
    /// Inicjalizuje obiekt na podstawie danych w formacie binarnym.
    void loadFromBinary(ifstream& in);

    /// \brief Zwraca dat�, kt�ra znajduje si� w wierszu.
    /// \return Data wiersza w formacie tekstowym (np. "YYYY-MM-DD").
    /// Funkcja ta umo�liwia pobranie daty przypisanej do danego wiersza danych.
    string getDate() const { return date; }

    /// \brief Zwraca warto�� autokonsumpcji z wiersza danych.
    /// \return Warto�� autokonsumpcji w watach (W) jako liczba zmiennoprzecinkowa.
    /// Funkcja ta umo�liwia dost�p do warto�ci autokonsumpcji dla danego wiersza danych.
    float getSelfConsumption() const { return selfConsumption; }

    /// \brief Zwraca warto�� eksportu z wiersza danych.
    /// \return Warto�� eksportu w watach (W) jako liczba zmiennoprzecinkowa.
    /// Funkcja ta zwraca warto�� eksportu energii przypisan� do danego wiersza.
    float getExport() const { return exportValue; }

    /// \brief Zwraca warto�� importu z wiersza danych.
    /// \return Warto�� importu w watach (W) jako liczba zmiennoprzecinkowa.
    /// Funkcja ta zwraca warto�� importu energii dla danego wiersza.
    float getImport() const { return importValue; }

    /// \brief Zwraca warto�� poboru energii z wiersza danych.
    /// \return Warto�� poboru energii w watach (W) jako liczba zmiennoprzecinkowa.
    /// Funkcja ta zwraca warto�� poboru energii z sieci przypisan� do danego wiersza danych.
    float getConsumption() const { return consumption; }

    /// \brief Zwraca warto�� produkcji energii z wiersza danych.
    /// \return Warto�� produkcji energii w watach (W) jako liczba zmiennoprzecinkowa.
    /// Funkcja ta umo�liwia dost�p do warto�ci produkcji energii przypisanej do danego wiersza.
    float getProduction() const { return production; }

private:
    string date; ///< Data wiersza w formacie tekstowym (np. "YYYY-MM-DD").
    float selfConsumption; ///< Autokonsumpcja w watach (W), ilo�� energii zu�ytej lokalnie.
    float exportValue; ///< Eksport energii w watach (W), ilo�� energii oddanej do sieci.
    float importValue; ///< Import energii w watach (W), ilo�� energii pobranej z sieci.
    float consumption; ///< Pob�r energii z sieci w watach (W).
    float production; ///< Produkcja energii w watach (W), energia wytworzona przez system.
};

#endif // ROWDATA_H
