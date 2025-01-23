/// \file TreeData.h
/// \brief Deklaracja klasy TreeData do przechowywania i analizy danych w strukturze drzewa.

#ifndef TREEDATA_H
#define TREEDATA_H

#include <map>
#include <string>
#include <vector>
#include "RowData.h" ///< Za³¹czenie pliku nag³ówkowego zawieraj¹cego klasê RowData.

/// \class TreeData
/// \brief Klasa przechowuj¹ca dane w hierarchicznej strukturze drzewa na podstawie danych z pliku CSV.
/// Klasa ta umo¿liwia organizowanie danych w strukturze drzewa, gdzie dane s¹ przechowywane wed³ug roku, miesi¹ca, dnia i kwarta³u.
/// Dziêki tej strukturze mo¿liwa jest analiza oraz obliczenia na danych w zale¿noœci od zakresu czasowego.
class TreeData {
public:
    /// \struct QuarterNode
    /// \brief Reprezentuje dane z podzia³em na kwarta³y dnia.
    /// Struktura ta zawiera informacje o godzinie, minucie oraz dane przypisane do danego kwarta³u.
    struct QuarterNode {
        int quarter; ///< Numer kwarta³u (0-3), np. 0 - pierwsza czêœæ godziny, 1 - druga czêœæ godziny itd.
        int hour; ///< Godzina rozpoczêcia kwarta³u (0-23).
        int minute; ///< Minuta rozpoczêcia kwarta³u (0-59).
        std::vector<RowData> data; ///< Dane przypisane do kwarta³u, przechowywane jako wektor obiektów RowData.
    };

    /// \struct DayNode
    /// \brief Reprezentuje dane dzienne.
    /// Struktura ta zawiera informacje o danym dniu oraz mapê kwartalnych danych w tym dniu.
    struct DayNode {
        int day; ///< Dzieñ miesi¹ca (1-31).
        std::map<int, QuarterNode> quarters; ///< Mapa kwartalnych danych w dniu, gdzie kluczem jest numer kwarta³u.
    };

    /// \struct MonthNode
    /// \brief Reprezentuje dane miesiêczne.
    /// Struktura ta zawiera informacje o danym miesi¹cu oraz mapê dziennych danych w tym miesi¹cu.
    struct MonthNode {
        int month; ///< Numer miesi¹ca (1-12).
        std::map<int, DayNode> days; ///< Mapa dziennych danych w miesi¹cu, gdzie kluczem jest numer dnia.
    };

    /// \struct YearNode
    /// \brief Reprezentuje dane roczne.
    /// Struktura ta zawiera informacje o roku oraz mapê miesiêcznych danych w tym roku.
    struct YearNode {
        int year; ///< Rok (np. 2023).
        std::map<int, MonthNode> months; ///< Mapa miesiêcznych danych w roku, gdzie kluczem jest numer miesi¹ca.
    };

    /// \brief Dodaje dane do struktury drzewa.
    /// \param rowData Obiekt RowData reprezentuj¹cy wiersz danych do dodania.
    /// \details Funkcja ta dodaje dane do odpowiedniej pozycji w hierarchii drzewa na podstawie daty i czasu.
    /// Tworzy lub aktualizuje odpowiednie wêz³y drzewa, wstawiaj¹c dane w odpowiednim roku, miesi¹cu, dniu i kwartale.
    void addData(const RowData& rowData);

    /// \brief Wyœwietla ca³¹ strukturê drzewa.
    /// \details Funkcja ta wypisuje ca³¹ strukturê danych, pocz¹wszy od lat, przez miesi¹ce, dni, a¿ po kwarta³y.
    /// Pozwala na wizualizacjê danych w drzewiastej strukturze hierarchicznej.
    void print() const;

    /// \brief Pobiera dane w okreœlonym przedziale czasowym.
    /// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
    /// \return Wektor obiektów RowData, które mieszcz¹ siê w podanym przedziale czasowym.
    /// \details Funkcja ta filtruje dane i zwraca wszystkie rekordy, które mieszcz¹ siê w okreœlonym zakresie dat.
    std::vector<RowData> getDataBetweenDates(const std::string& startDate, const std::string& endDate) const;

    /// \brief Oblicza sumy danych w okreœlonym przedziale czasowym.
    /// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
    /// \param[out] selfConsumptionSum Suma autokonsumpcji w podanym okresie.
    /// \param[out] exportSum Suma eksportu w podanym okresie.
    /// \param[out] importSum Suma importu w podanym okresie.
    /// \param[out] consumptionSum Suma poboru w podanym okresie.
    /// \param[out] productionSum Suma produkcji w podanym okresie.
    /// \details Funkcja ta przeszukuje dane w podanym przedziale czasowym i oblicza sumy wartoœci autokonsumpcji, eksportu,
    /// importu, poboru oraz produkcji.
    void calculateSumsBetweenDates(const std::string& startDate, const std::string& endDate,
        float& selfConsumptionSum, float& exportSum, float& importSum,
        float& consumptionSum, float& productionSum) const;

    /// \brief Oblicza œrednie wartoœci danych w okreœlonym przedziale czasowym.
    /// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
    /// \param[out] selfConsumptionAvg Œrednia autokonsumpcji w podanym okresie.
    /// \param[out] exportAvg Œrednia eksportu w podanym okresie.
    /// \param[out] importAvg Œrednia importu w podanym okresie.
    /// \param[out] consumptionAvg Œrednia poboru w podanym okresie.
    /// \param[out] productionAvg Œrednia produkcji w podanym okresie.
    /// \details Funkcja ta oblicza œrednie wartoœci dla autokonsumpcji, eksportu, importu, poboru i produkcji
    /// na podstawie danych z wybranego okresu czasu.
    void calculateAveragesBetweenDates(const std::string& startDate, const std::string& endDate,
        float& selfConsumptionAvg, float& exportAvg, float& importAvg,
        float& consumptionAvg, float& productionAvg) const;

    /// \brief Porównuje dane miêdzy dwoma zakresami czasowymi.
    /// \param startDate1 Data pocz¹tkowa pierwszego zakresu.
    /// \param endDate1 Data koñcowa pierwszego zakresu.
    /// \param startDate2 Data pocz¹tkowa drugiego zakresu.
    /// \param endDate2 Data koñcowa drugiego zakresu.
    /// \param[out] selfConsumptionDiff Ró¿nica autokonsumpcji miêdzy dwoma zakresami czasowymi.
    /// \param[out] exportDiff Ró¿nica eksportu miêdzy dwoma zakresami czasowymi.
    /// \param[out] importDiff Ró¿nica importu miêdzy dwoma zakresami czasowymi.
    /// \param[out] consumptionDiff Ró¿nica poboru miêdzy dwoma zakresami czasowymi.
    /// \param[out] productionDiff Ró¿nica produkcji miêdzy dwoma zakresami czasowymi.
    /// \details Funkcja ta porównuje dane w dwóch okreœlonych zakresach czasowych i oblicza ró¿nice w wartoœciach dla 
    /// autokonsumpcji, eksportu, importu, poboru i produkcji.
    void compareDataBetweenDates(const std::string& startDate1, const std::string& endDate1,
        const std::string& startDate2, const std::string& endDate2,
        float& selfConsumptionDiff, float& exportDiff, float& importDiff,
        float& consumptionDiff, float& productionDiff) const;

    /// \brief Wyszukuje rekordy w okreœlonym zakresie czasowym z uwzglêdnieniem tolerancji.
    /// \param startDate Data pocz¹tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data koñcowa w formacie dd.mm.yyyy hh:mm.
    /// \param value Wartoœæ wyszukiwana.
    /// \param tolerance Tolerancja dla wartoœci wyszukiwania.
    /// \return Wektor obiektów RowData, które spe³niaj¹ kryteria wyszukiwania.
    /// \details Funkcja ta umo¿liwia wyszukiwanie danych w okreœlonym przedziale czasowym, uwzglêdniaj¹c tolerancjê 
    /// dla wyszukiwanej wartoœci.
    std::vector<RowData> searchRecordsWithTolerance(const std::string& startDate, const std::string& endDate,
        float value, float tolerance) const;

private:
    std::map<int, YearNode> years; ///< Mapa lat, w których znajduj¹ siê dane w strukturze drzewa.
};

#endif // TREEDATA_H
