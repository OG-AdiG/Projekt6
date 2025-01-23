/// \file TreeData.cpp
/// \brief Implementacja klasy TreeData do przechowywania i analizy danych w strukturze drzewa.

#include "TreeData.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

/// \brief Dodaje dane do struktury drzewa.
/// \param rowData Obiekt RowData reprezentuj¹cy dane wiersza.
/// \details Funkcja ta przetwarza dane z obiektu RowData i dodaje je do odpowiedniej lokalizacji w strukturze drzewa,
/// w zale¿noœci od daty, godziny, minuty oraz kwarta³u. U¿ywane s¹ dane o roku, miesi¹cu, dniu, godzinie i minucie,
/// aby odpowiednio wstawiæ dane do hierarchii.
void TreeData::addData(const RowData& rowData) {
    // Tworzenie strumienia z dat¹ z obiektu RowData
    stringstream ss(rowData.getDate());
    string token;
    vector<int> dateParts;

    // Rozdzielenie daty na poszczególne czêœci (dzieñ, miesi¹c, rok)
    while (getline(ss, token, '.')) {
        dateParts.push_back(stoi(token));  ///< Parsowanie ka¿dej czêœci daty na liczbê
    }

    // Zmienne dla roku, miesi¹ca, dnia, godziny, minuty oraz kwarta³u
    int year = dateParts[2];  ///< Rok wyci¹gniêty z daty
    int month = dateParts[1];  ///< Miesi¹c wyci¹gniêty z daty
    int day = dateParts[0];    ///< Dzieñ wyci¹gniêty z daty
    int hour = stoi(rowData.getDate().substr(11, 2));  ///< Godzina wyci¹gniêta z daty
    int minute = stoi(rowData.getDate().substr(14, 2));  ///< Minuta wyci¹gniêta z daty
    int quarter = (hour * 60 + minute) / 360;  ///< Wyliczanie kwarta³u na podstawie godziny i minuty

    // Przypisanie wartoœci do struktury drzewa na podstawie wyodrêbnionych danych
    years[year].year = year;  ///< Ustawienie roku w strukturze
    years[year].months[month].month = month;  ///< Ustawienie miesi¹ca w strukturze
    years[year].months[month].days[day].day = day;  ///< Ustawienie dnia w strukturze
    years[year].months[month].days[day].quarters[quarter].quarter = quarter;  ///< Ustawienie kwarta³u w strukturze
    years[year].months[month].days[day].quarters[quarter].hour = hour;  ///< Ustawienie godziny w strukturze
    years[year].months[month].days[day].quarters[quarter].minute = minute;  ///< Ustawienie minuty w strukturze
    years[year].months[month].days[day].quarters[quarter].data.push_back(rowData);  ///< Dodanie danych do kwarta³u
}

/// \brief Wyœwietla zawartoœæ drzewa na standardowym wyjœciu.
/// \details Funkcja ta rekurencyjnie przegl¹da wszystkie elementy drzewa, pocz¹wszy od lat, przez miesi¹ce, dni,
/// kwarta³y, a¿ po same dane. Wypisuje wszystkie dostêpne dane z poszczególnych wêz³ów.
void TreeData::print() const {
    // Iterowanie po wszystkich latach w drzewie
    for (const auto& yearPair : years) {
        const YearNode& yearNode = yearPair.second;  ///< Pobieranie wêz³a roku
        cout << "Year: " << yearNode.year << endl;  ///< Wypisanie roku

        // Iterowanie po wszystkich miesi¹cach w danym roku
        for (const auto& monthPair : yearNode.months) {
            const MonthNode& monthNode = monthPair.second;  ///< Pobieranie wêz³a miesi¹ca
            cout << "\tMonth: " << monthNode.month << endl;  ///< Wypisanie miesi¹ca

            // Iterowanie po dniach w danym miesi¹cu
            for (const auto& dayPair : monthNode.days) {
                const DayNode& dayNode = dayPair.second;  ///< Pobieranie wêz³a dnia
                cout << "\t\tDay: " << dayNode.day << endl;  ///< Wypisanie dnia

                // Iterowanie po kwarta³ach w danym dniu
                for (const auto& quarterPair : dayNode.quarters) {
                    const QuarterNode& quarterNode = quarterPair.second;  ///< Pobieranie wêz³a kwarta³u
                    cout << "\t\t\tQuarter: " << quarterNode.quarter
                        << " (Hour: " << quarterNode.hour << ", Minute: " << quarterNode.minute << ")" << endl;  ///< Wypisanie kwarta³u, godziny i minuty

                    // Wypisanie danych przypisanych do tego kwarta³u
                    for (const auto& rowData : quarterNode.data) {
                        rowData.displayData();  ///< Wywo³anie metody wypisuj¹cej dane z RowData
                    }
                }
            }
        }
    }
}

/// \brief Pobiera dane z drzewa w okreœlonym przedziale czasowym.
/// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
/// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
/// \return Wektor obiektów RowData w podanym przedziale czasowym.
/// \details Funkcja ta iteruje po wszystkich danych w strukturze drzewa, porównuj¹c daty i zwracaj¹c dane
/// znajduj¹ce siê w podanym przedziale czasowym.
std::vector<RowData> TreeData::getDataBetweenDates(const std::string& startDate, const std::string& endDate) const {
    std::vector<RowData> result;  ///< Wektor do przechowywania wyników

    // Konwersja daty pocz¹tkowej na strukturê tm
    std::tm tm = {};
    std::istringstream ss(startDate);
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");  ///< Wczytanie daty pocz¹tkowej
    time_t start = mktime(&tm);  ///< Konwersja na typ time_t

    // Konwersja daty koñcowej na strukturê tm
    ss.clear();  ///< Czyszczenie strumienia
    ss.str(endDate);  ///< Ustawienie strumienia na datê koñcow¹
    ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");  ///< Wczytanie daty koñcowej
    time_t end = mktime(&tm);  ///< Konwersja na typ time_t

    // Iterowanie po wszystkich latach w drzewie
    for (const auto& yearPair : years) {
        const YearNode& yearNode = yearPair.second;  ///< Pobieranie wêz³a roku
        for (const auto& monthPair : yearNode.months) {
            const MonthNode& monthNode = monthPair.second;  ///< Pobieranie wêz³a miesi¹ca
            for (const auto& dayPair : monthNode.days) {
                const DayNode& dayNode = dayPair.second;  ///< Pobieranie wêz³a dnia
                for (const auto& quarterPair : dayNode.quarters) {
                    const QuarterNode& quarterNode = quarterPair.second;  ///< Pobieranie wêz³a kwarta³u
                    for (const auto& rowData : quarterNode.data) {
                        std::tm tm = {};
                        std::istringstream ss(rowData.getDate());
                        ss >> std::get_time(&tm, "%d.%m.%Y %H:%M");  ///< Wczytanie daty z danych
                        time_t dataTime = mktime(&tm);  ///< Konwersja na typ time_t

                        // Porównanie czasu danych z przedzia³em czasowym
                        if (dataTime >= start && dataTime <= end) {
                            result.push_back(rowData);  ///< Dodanie danych do wyników, jeœli mieszcz¹ siê w przedziale
                        }
                    }
                }
            }
        }
    }

    return result;  ///< Zwrócenie wyników
}

/// \brief Oblicza sumy wartoœci w okreœlonym przedziale czasowym.
/// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
/// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
/// \param[out] selfConsumptionSum Suma autokonsumpcji.
/// \param[out] exportSum Suma eksportu.
/// \param[out] importSum Suma importu.
/// \param[out] consumptionSum Suma poboru.
/// \param[out] productionSum Suma produkcji.
/// \details Funkcja ta przetwarza dane w okreœlonym przedziale czasowym i oblicza sumy dla poszczególnych
/// parametrów: autokonsumpcji, eksportu, importu, poboru i produkcji.
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
        selfConsumptionSum += rowData.getSelfConsumption();  ///< Dodanie wartoœci autokonsumpcji
        exportSum += rowData.getExport();  ///< Dodanie wartoœci eksportu
        importSum += rowData.getImport();  ///< Dodanie wartoœci importu
        consumptionSum += rowData.getConsumption();  ///< Dodanie wartoœci poboru
        productionSum += rowData.getProduction();  ///< Dodanie wartoœci produkcji
    }
}

/// \brief Oblicza œrednie wartoœci w okreœlonym przedziale czasowym.
/// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
/// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
/// \param[out] selfConsumptionAvg Œrednia autokonsumpcji.
/// \param[out] exportAvg Œrednia eksportu.
/// \param[out] importAvg Œrednia importu.
/// \param[out] consumptionAvg Œrednia poboru.
/// \param[out] productionAvg Œrednia produkcji.
/// \details Funkcja ta przetwarza dane w okreœlonym przedziale czasowym, obliczaj¹c œrednie wartoœci dla
/// autokonsumpcji, eksportu, importu, poboru i produkcji.
void TreeData::calculateAveragesBetweenDates(const std::string& startDate, const std::string& endDate,
    float& selfConsumptionAvg, float& exportAvg, float& importAvg,
    float& consumptionAvg, float& productionAvg) const {
    // Inicjalizacja zmiennych sumuj¹cych oraz liczby danych
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
        count++;  ///< Zwiêkszanie liczby danych
    }

    // Obliczanie œrednich, jeœli dane istniej¹
    if (count > 0) {
        selfConsumptionAvg = selfConsumptionSum / count;  ///< Obliczanie œredniej autokonsumpcji
        exportAvg = exportSum / count;  ///< Obliczanie œredniej eksportu
        importAvg = importSum / count;  ///< Obliczanie œredniej importu
        consumptionAvg = consumptionSum / count;  ///< Obliczanie œredniej poboru
        productionAvg = productionSum / count;  ///< Obliczanie œredniej produkcji
    }
}
