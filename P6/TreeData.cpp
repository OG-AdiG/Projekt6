/// \file TreeData.cpp
/// \brief Implementacja klasy TreeData do przechowywania i analizy danych w strukturze drzewa.

#include "TreeData.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

/// \brief Dodaje dane do struktury drzewa.
/// \param rowData Obiekt RowData reprezentuj�cy dane wiersza.
/// \details Funkcja ta przetwarza dane z obiektu RowData i dodaje je do odpowiedniej lokalizacji w strukturze drzewa,
/// w zale�no�ci od daty, godziny, minuty oraz kwarta�u. U�ywane s� dane o roku, miesi�cu, dniu, godzinie i minucie,
/// aby odpowiednio wstawi� dane do hierarchii.
void TreeData::addData(const RowData& rowData) {
    // Tworzenie strumienia z dat� z obiektu RowData
    stringstream ss(rowData.getDate());
    string token;
    vector<int> dateParts;

    // Rozdzielenie daty na poszczeg�lne cz�ci (dzie�, miesi�c, rok)
    while (getline(ss, token, '.')) {
        dateParts.push_back(stoi(token));  ///< Parsowanie ka�dej cz�ci daty na liczb�
    }

    // Zmienne dla roku, miesi�ca, dnia, godziny, minuty oraz kwarta�u
    int year = dateParts[2];  ///< Rok wyci�gni�ty z daty
    int month = dateParts[1];  ///< Miesi�c wyci�gni�ty z daty
    int day = dateParts[0];    ///< Dzie� wyci�gni�ty z daty
    int hour = stoi(rowData.getDate().substr(11, 2));  ///< Godzina wyci�gni�ta z daty
    int minute = stoi(rowData.getDate().substr(14, 2));  ///< Minuta wyci�gni�ta z daty
    int quarter = (hour * 60 + minute) / 360;  ///< Wyliczanie kwarta�u na podstawie godziny i minuty

    // Przypisanie warto�ci do struktury drzewa na podstawie wyodr�bnionych danych
    years[year].year = year;  ///< Ustawienie roku w strukturze
    years[year].months[month].month = month;  ///< Ustawienie miesi�ca w strukturze
    years[year].months[month].days[day].day = day;  ///< Ustawienie dnia w strukturze
    years[year].months[month].days[day].quarters[quarter].quarter = quarter;  ///< Ustawienie kwarta�u w strukturze
    years[year].months[month].days[day].quarters[quarter].hour = hour;  ///< Ustawienie godziny w strukturze
    years[year].months[month].days[day].quarters[quarter].minute = minute;  ///< Ustawienie minuty w strukturze
    years[year].months[month].days[day].quarters[quarter].data.push_back(rowData);  ///< Dodanie danych do kwarta�u
}

/// \brief Wy�wietla zawarto�� drzewa na standardowym wyj�ciu.
/// \details Funkcja ta rekurencyjnie przegl�da wszystkie elementy drzewa, pocz�wszy od lat, przez miesi�ce, dni,
/// kwarta�y, a� po same dane. Wypisuje wszystkie dost�pne dane z poszczeg�lnych w�z��w.
void TreeData::print() const {
    // Iterowanie po wszystkich latach w drzewie
    for (const auto& yearPair : years) {
        const YearNode& yearNode = yearPair.second;  ///< Pobieranie w�z�a roku
        cout << "Year: " << yearNode.year << endl;  ///< Wypisanie roku

        // Iterowanie po wszystkich miesi�cach w danym roku
        for (const auto& monthPair : yearNode.months) {
            const MonthNode& monthNode = monthPair.second;  ///< Pobieranie w�z�a miesi�ca
            cout << "\tMonth: " << monthNode.month << endl;  ///< Wypisanie miesi�ca

            // Iterowanie po dniach w danym miesi�cu
            for (const auto& dayPair : monthNode.days) {
                const DayNode& dayNode = dayPair.second;  ///< Pobieranie w�z�a dnia
                cout << "\t\tDay: " << dayNode.day << endl;  ///< Wypisanie dnia

                // Iterowanie po kwarta�ach w danym dniu
                for (const auto& quarterPair : dayNode.quarters) {
                    const QuarterNode& quarterNode = quarterPair.second;  ///< Pobieranie w�z�a kwarta�u
                    cout << "\t\t\tQuarter: " << quarterNode.quarter
                        << " (Hour: " << quarterNode.hour << ", Minute: " << quarterNode.minute << ")" << endl;  ///< Wypisanie kwarta�u, godziny i minuty

                    // Wypisanie danych przypisanych do tego kwarta�u
                    for (const auto& rowData : quarterNode.data) {
                        rowData.displayData();  ///< Wywo�anie metody wypisuj�cej dane z RowData
                    }
                }
            }
        }
    }
}

/// \brief Pobiera dane z drzewa w okre�lonym przedziale czasowym.
/// \param startDate Data pocz�tkowa w formacie dd.mm.yyyy hh:mm.
/// \param endDate Data ko�cowa w formacie dd.mm.yyyy hh:mm.
/// \return Wektor obiekt�w RowData w podanym przedziale czasowym.
/// \details Funkcja ta iteruje po wszystkich danych w strukturze drzewa, por�wnuj�c daty i zwracaj�c dane
/// znajduj�ce si� w podanym przedziale czasowym.
std::vector<RowData> TreeData::getDataBetweenDates(const std::string& startDate, const std::string& endDate) const {
    std::vector<RowData> result;  ///< Wektor do przechowywania wynik�w

    // Konwersja daty pocz�tkowej na struktur� tm
    std::tm tm = {};
    std::istringstream ss(startDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");  ///< Wczytanie daty pocz�tkowej
    time_t start = mktime(&tm);  ///< Konwersja na typ time_t

    // Konwersja daty ko�cowej na struktur� tm
    ss.clear();  ///< Czyszczenie strumienia
    ss.str(endDate);  ///< Ustawienie strumienia na dat� ko�cow�
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");  ///< Wczytanie daty ko�cowej
    time_t end = mktime(&tm);  ///< Konwersja na typ time_t

    // Iterowanie po wszystkich latach w drzewie
    for (const auto& yearPair : years) {
        const YearNode& yearNode = yearPair.second;  ///< Pobieranie w�z�a roku
        for (const auto& monthPair : yearNode.months) {
            const MonthNode& monthNode = monthPair.second;  ///< Pobieranie w�z�a miesi�ca
            for (const auto& dayPair : monthNode.days) {
                const DayNode& dayNode = dayPair.second;  ///< Pobieranie w�z�a dnia
                for (const auto& quarterPair : dayNode.quarters) {
                    const QuarterNode& quarterNode = quarterPair.second;  ///< Pobieranie w�z�a kwarta�u
                    for (const auto& rowData : quarterNode.data) {
                        std::tm tm = {};
                        std::istringstream ss(rowData.getDate());
                        ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");  ///< Wczytanie daty z danych
                        time_t dataTime = mktime(&tm);  ///< Konwersja na typ time_t

                        // Por�wnanie czasu danych z przedzia�em czasowym
                        if (dataTime >= start && dataTime <= end) {
                            result.push_back(rowData);  ///< Dodanie danych do wynik�w, je�li mieszcz� si� w przedziale
                        }
                    }
                }
            }
        }
    }

    return result;  ///< Zwr�cenie wynik�w
}

/// \brief Oblicza sumy warto�ci w okre�lonym przedziale czasowym.
/// \param startDate Data pocz�tkowa w formacie dd.mm.yyyy hh:mm.
/// \param endDate Data ko�cowa w formacie dd.mm.yyyy hh:mm.
/// \param[out] selfConsumptionSum Suma autokonsumpcji.
/// \param[out] exportSum Suma eksportu.
/// \param[out] importSum Suma importu.
/// \param[out] consumptionSum Suma poboru.
/// \param[out] productionSum Suma produkcji.
/// \details Funkcja ta przetwarza dane w okre�lonym przedziale czasowym i oblicza sumy dla poszczeg�lnych
/// parametr�w: autokonsumpcji, eksportu, importu, poboru i produkcji.
void TreeData::calculateSumsBetweenDates(const std::string& startDate, const std::string& endDate,
    float& selfConsumptionSum, float& exportSum, float& importSum,
    float& consumptionSum, float& productionSum) const {
    // Inicjalizacja sum na 0
    selfConsumptionSum = 0.0f;
    exportSum = 0.0f;
    importSum = 0.0f;
    consumptionSum = 0.0f;
    productionSum = 0.0f;

    // Pobranie danych w podanym przedziale czasowym
    std::vector<RowData> data = getDataBetweenDates(startDate, endDate);
    for (const auto& rowData : data) {
        selfConsumptionSum += rowData.getSelfConsumption();  ///< Dodanie warto�ci autokonsumpcji
        exportSum += rowData.getExport();  ///< Dodanie warto�ci eksportu
        importSum += rowData.getImport();  ///< Dodanie warto�ci importu
        consumptionSum += rowData.getConsumption();  ///< Dodanie warto�ci poboru
        productionSum += rowData.getProduction();  ///< Dodanie warto�ci produkcji
    }
}

/// \brief Oblicza �rednie warto�ci w okre�lonym przedziale czasowym.
/// \param startDate Data pocz�tkowa w formacie dd.mm.yyyy hh:mm.
/// \param endDate Data ko�cowa w formacie dd.mm.yyyy hh:mm.
/// \param[out] selfConsumptionAvg �rednia autokonsumpcji.
/// \param[out] exportAvg �rednia eksportu.
/// \param[out] importAvg �rednia importu.
/// \param[out] consumptionAvg �rednia poboru.
/// \param[out] productionAvg �rednia produkcji.
/// \details Funkcja ta przetwarza dane w okre�lonym przedziale czasowym, obliczaj�c �rednie warto�ci dla
/// autokonsumpcji, eksportu, importu, poboru i produkcji.
void TreeData::calculateAveragesBetweenDates(const std::string& startDate, const std::string& endDate,
    float& selfConsumptionAvg, float& exportAvg, float& importAvg,
    float& consumptionAvg, float& productionAvg) const {
    // Inicjalizacja zmiennych sumuj�cych oraz liczby danych
    float selfConsumptionSum = 0.0f, exportSum = 0.0f, importSum = 0.0f, consumptionSum = 0.0f, productionSum = 0.0f;
    int count = 0;

    // Pobranie danych w podanym przedziale czasowym
    std::vector<RowData> data = getDataBetweenDates(startDate, endDate);
    for (const auto& rowData : data) {
        selfConsumptionSum += rowData.getSelfConsumption();  ///< Sumowanie autokonsumpcji
        exportSum += rowData.getExport();  ///< Sumowanie eksportu
        importSum += rowData.getImport();  ///< Sumowanie importu
        consumptionSum += rowData.getConsumption();  ///< Sumowanie poboru
        productionSum += rowData.getProduction();  ///< Sumowanie produkcji
        count++;  ///< Zwi�kszanie liczby danych
    }

    // Obliczanie �rednich, je�li dane istniej�
    if (count > 0) {
        selfConsumptionAvg = selfConsumptionSum / count;  ///< Obliczanie �redniej autokonsumpcji
        exportAvg = exportSum / count;  ///< Obliczanie �redniej eksportu
        importAvg = importSum / count;  ///< Obliczanie �redniej importu
        consumptionAvg = consumptionSum / count;  ///< Obliczanie �redniej poboru
        productionAvg = productionSum / count;  ///< Obliczanie �redniej produkcji
    }
}
