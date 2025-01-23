/// \file TreeData.h
/// \brief Deklaracja klasy TreeData do przechowywania i analizy danych w strukturze drzewa.

#ifndef TREEDATA_H
#define TREEDATA_H

#include <map>
#include <string>
#include <vector>
#include "RowData.h" ///< Za��czenie pliku nag��wkowego zawieraj�cego klas� RowData.

/// \class TreeData
/// \brief Klasa przechowuj�ca dane w hierarchicznej strukturze drzewa na podstawie danych z pliku CSV.
/// Klasa ta umo�liwia organizowanie danych w strukturze drzewa, gdzie dane s� przechowywane wed�ug roku, miesi�ca, dnia i kwarta�u.
/// Dzi�ki tej strukturze mo�liwa jest analiza oraz obliczenia na danych w zale�no�ci od zakresu czasowego.
class TreeData {
public:
    /// \struct QuarterNode
    /// \brief Reprezentuje dane z podzia�em na kwarta�y dnia.
    /// Struktura ta zawiera informacje o godzinie, minucie oraz dane przypisane do danego kwarta�u.
    struct QuarterNode {
        int quarter; ///< Numer kwarta�u (0-3), np. 0 - pierwsza cz�� godziny, 1 - druga cz�� godziny itd.
        int hour; ///< Godzina rozpocz�cia kwarta�u (0-23).
        int minute; ///< Minuta rozpocz�cia kwarta�u (0-59).
        std::vector<RowData> data; ///< Dane przypisane do kwarta�u, przechowywane jako wektor obiekt�w RowData.
    };

    /// \struct DayNode
    /// \brief Reprezentuje dane dzienne.
    /// Struktura ta zawiera informacje o danym dniu oraz map� kwartalnych danych w tym dniu.
    struct DayNode {
        int day; ///< Dzie� miesi�ca (1-31).
        std::map<int, QuarterNode> quarters; ///< Mapa kwartalnych danych w dniu, gdzie kluczem jest numer kwarta�u.
    };

    /// \struct MonthNode
    /// \brief Reprezentuje dane miesi�czne.
    /// Struktura ta zawiera informacje o danym miesi�cu oraz map� dziennych danych w tym miesi�cu.
    struct MonthNode {
        int month; ///< Numer miesi�ca (1-12).
        std::map<int, DayNode> days; ///< Mapa dziennych danych w miesi�cu, gdzie kluczem jest numer dnia.
    };

    /// \struct YearNode
    /// \brief Reprezentuje dane roczne.
    /// Struktura ta zawiera informacje o roku oraz map� miesi�cznych danych w tym roku.
    struct YearNode {
        int year; ///< Rok (np. 2023).
        std::map<int, MonthNode> months; ///< Mapa miesi�cznych danych w roku, gdzie kluczem jest numer miesi�ca.
    };

    /// \brief Dodaje dane do struktury drzewa.
    /// \param rowData Obiekt RowData reprezentuj�cy wiersz danych do dodania.
    /// \details Funkcja ta dodaje dane do odpowiedniej pozycji w hierarchii drzewa na podstawie daty i czasu.
    /// Tworzy lub aktualizuje odpowiednie w�z�y drzewa, wstawiaj�c dane w odpowiednim roku, miesi�cu, dniu i kwartale.
    void addData(const RowData& rowData);

    /// \brief Wy�wietla ca�� struktur� drzewa.
    /// \details Funkcja ta wypisuje ca�� struktur� danych, pocz�wszy od lat, przez miesi�ce, dni, a� po kwarta�y.
    /// Pozwala na wizualizacj� danych w drzewiastej strukturze hierarchicznej.
    void print() const;

    /// \brief Pobiera dane w okre�lonym przedziale czasowym.
    /// \param startDate Data pocz�tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data ko�cowa w formacie dd.mm.yyyy hh:mm.
    /// \return Wektor obiekt�w RowData, kt�re mieszcz� si� w podanym przedziale czasowym.
    /// \details Funkcja ta filtruje dane i zwraca wszystkie rekordy, kt�re mieszcz� si� w okre�lonym zakresie dat.
    std::vector<RowData> getDataBetweenDates(const std::string& startDate, const std::string& endDate) const;

    /// \brief Oblicza sumy danych w okre�lonym przedziale czasowym.
    /// \param startDate Data pocz�tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data ko�cowa w formacie dd.mm.yyyy hh:mm.
    /// \param[out] selfConsumptionSum Suma autokonsumpcji w podanym okresie.
    /// \param[out] exportSum Suma eksportu w podanym okresie.
    /// \param[out] importSum Suma importu w podanym okresie.
    /// \param[out] consumptionSum Suma poboru w podanym okresie.
    /// \param[out] productionSum Suma produkcji w podanym okresie.
    /// \details Funkcja ta przeszukuje dane w podanym przedziale czasowym i oblicza sumy warto�ci autokonsumpcji, eksportu,
    /// importu, poboru oraz produkcji.
    void calculateSumsBetweenDates(const std::string& startDate, const std::string& endDate,
        float& selfConsumptionSum, float& exportSum, float& importSum,
        float& consumptionSum, float& productionSum) const;

    /// \brief Oblicza �rednie warto�ci danych w okre�lonym przedziale czasowym.
    /// \param startDate Data pocz�tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data ko�cowa w formacie dd.mm.yyyy hh:mm.
    /// \param[out] selfConsumptionAvg �rednia autokonsumpcji w podanym okresie.
    /// \param[out] exportAvg �rednia eksportu w podanym okresie.
    /// \param[out] importAvg �rednia importu w podanym okresie.
    /// \param[out] consumptionAvg �rednia poboru w podanym okresie.
    /// \param[out] productionAvg �rednia produkcji w podanym okresie.
    /// \details Funkcja ta oblicza �rednie warto�ci dla autokonsumpcji, eksportu, importu, poboru i produkcji
    /// na podstawie danych z wybranego okresu czasu.
    void calculateAveragesBetweenDates(const std::string& startDate, const std::string& endDate,
        float& selfConsumptionAvg, float& exportAvg, float& importAvg,
        float& consumptionAvg, float& productionAvg) const;

    /// \brief Por�wnuje dane mi�dzy dwoma zakresami czasowymi.
    /// \param startDate1 Data pocz�tkowa pierwszego zakresu.
    /// \param endDate1 Data ko�cowa pierwszego zakresu.
    /// \param startDate2 Data pocz�tkowa drugiego zakresu.
    /// \param endDate2 Data ko�cowa drugiego zakresu.
    /// \param[out] selfConsumptionDiff R�nica autokonsumpcji mi�dzy dwoma zakresami czasowymi.
    /// \param[out] exportDiff R�nica eksportu mi�dzy dwoma zakresami czasowymi.
    /// \param[out] importDiff R�nica importu mi�dzy dwoma zakresami czasowymi.
    /// \param[out] consumptionDiff R�nica poboru mi�dzy dwoma zakresami czasowymi.
    /// \param[out] productionDiff R�nica produkcji mi�dzy dwoma zakresami czasowymi.
    /// \details Funkcja ta por�wnuje dane w dw�ch okre�lonych zakresach czasowych i oblicza r�nice w warto�ciach dla 
    /// autokonsumpcji, eksportu, importu, poboru i produkcji.
    void compareDataBetweenDates(const std::string& startDate1, const std::string& endDate1,
        const std::string& startDate2, const std::string& endDate2,
        float& selfConsumptionDiff, float& exportDiff, float& importDiff,
        float& consumptionDiff, float& productionDiff) const;

    /// \brief Wyszukuje rekordy w okre�lonym zakresie czasowym z uwzgl�dnieniem tolerancji.
    /// \param startDate Data pocz�tkowa w formacie dd.mm.yyyy hh:mm.
    /// \param endDate Data ko�cowa w formacie dd.mm.yyyy hh:mm.
    /// \param value Warto�� wyszukiwana.
    /// \param tolerance Tolerancja dla warto�ci wyszukiwania.
    /// \return Wektor obiekt�w RowData, kt�re spe�niaj� kryteria wyszukiwania.
    /// \details Funkcja ta umo�liwia wyszukiwanie danych w okre�lonym przedziale czasowym, uwzgl�dniaj�c tolerancj� 
    /// dla wyszukiwanej warto�ci.
    std::vector<RowData> searchRecordsWithTolerance(const std::string& startDate, const std::string& endDate,
        float value, float tolerance) const;

private:
    std::map<int, YearNode> years; ///< Mapa lat, w kt�rych znajduj� si� dane w strukturze drzewa.
};

#endif // TREEDATA_H
