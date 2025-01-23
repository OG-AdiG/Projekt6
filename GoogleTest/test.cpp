/// \file test.cpp
/// \brief Zawiera zestaw testów jednostkowych dla modu³ów RowData, TreeData, Logger i LineValidation.
/// \details Testy jednostkowe zosta³y zaimplementowane z u¿yciem frameworka GoogleTest.

#include "pch.h"
#include "../P6/RowData.h"
#include "../P6/RowData.cpp"
#include "../P6/TreeData.h"
#include "../P6/TreeData.cpp"
#include "../P6/LogManager.h"
#include "../P6/LogManager.cpp"
#include "../P6/LineValidation.h"

using namespace std;

/// \brief Testuje konstruktor klasy RowData.
/// \details Sprawdza, czy wartoœci wczytane z ci¹gu znaków s¹ poprawnie przypisane.
TEST(RowDataTest, ConstructorFromString) {
    string line = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    RowData rd(line);

    EXPECT_EQ(rd.getDate(), "15.10.2023 12:00:00");
    EXPECT_FLOAT_EQ(rd.getConsumption(), 100.5);
    EXPECT_FLOAT_EQ(rd.getExport(), 200.5);
    EXPECT_FLOAT_EQ(rd.getImport(), 300.5);
    EXPECT_FLOAT_EQ(rd.getSelfConsumption(), 400.5);
    EXPECT_FLOAT_EQ(rd.getProduction(), 500.5);
}

/// \brief Testuje serializacjê i deserializacjê klasy RowData.
/// \details Sprawdza, czy dane zapisane do pliku binarnego s¹ poprawnie odczytywane.
TEST(RowDataTest, Serialization) {
    string line = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    RowData rd(line);

    ofstream out("test.bin", ios::binary);
    rd.saveToBinary(out); ///< Serializacja danych do pliku binarnego.
    out.close();

    ifstream in("test.bin", ios::binary);
    RowData rd2(in); ///< Deserializacja danych z pliku binarnego.
    in.close();

    EXPECT_EQ(rd2.getDate(), "15.10.2023 12:00:00");
    EXPECT_FLOAT_EQ(rd2.getSelfConsumption(), 100.5);
    EXPECT_FLOAT_EQ(rd2.getExport(), 200.5);
    EXPECT_FLOAT_EQ(rd2.getImport(), 300.5);
    EXPECT_FLOAT_EQ(rd2.getConsumption(), 400.5);
    EXPECT_FLOAT_EQ(rd2.getProduction(), 500.5);
}

/// \brief Testuje funkcjê waliduj¹c¹ puste linie.
/// \details Sprawdza, czy funkcja zwraca false dla pustej linii.
TEST(LineValidationTest, EmptyLine) {
    string line = "";
    EXPECT_FALSE(lineValidation(line)); ///< Walidacja pustej linii.
}

/// \brief Testuje funkcjê waliduj¹c¹ linie z nag³ówkami.
/// \details Sprawdza, czy funkcja zwraca false dla linii z nag³ówkiem.
TEST(LineValidationTest, HeaderLine) {
    string line = "Time,Autokonsumpcja (W),Eksport (W),Import (W),Pobor (W),Produkcja (W)";
    EXPECT_FALSE(lineValidation(line)); ///< Walidacja linii z nag³ówkiem.
}

/// \brief Testuje funkcjê waliduj¹c¹ linie z nieprawid³owymi znakami.
/// \details Sprawdza, czy funkcja zwraca false dla linii zawieraj¹cych nieprawid³owe znaki.
TEST(LineValidationTest, LineWithInvalidCharacters) {
    string line = "2023-10-15 12:00:00,X,200.5,300.5,400.5,500.5";
    EXPECT_FALSE(lineValidation(line)); ///< Walidacja linii z nieprawid³owymi znakami.
}

/// \brief Testuje dodawanie danych do struktury drzewa.
/// \details Sprawdza, czy dane s¹ poprawnie przechowywane w strukturze drzewa.
TEST(TreeDataTest, AddData) {
    TreeData treeData;
    string line = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    RowData rd(line);
    treeData.addData(rd); ///< Dodanie danych do struktury drzewa.

    vector<RowData> data = treeData.getDataBetweenDates("15.10.2023 00:00", "15.10.2023 23:59");
    ASSERT_EQ(data.size(), 1); ///< Sprawdzenie, czy dodany rekord jest w drzewie.
    EXPECT_EQ(data[0].getDate(), "15.10.2023 12:00:00");
    EXPECT_FLOAT_EQ(data[0].getSelfConsumption(), 100.5);
    EXPECT_FLOAT_EQ(data[0].getExport(), 200.5);
    EXPECT_FLOAT_EQ(data[0].getImport(), 300.5);
    EXPECT_FLOAT_EQ(data[0].getConsumption(), 400.5);
    EXPECT_FLOAT_EQ(data[0].getProduction(), 500.5);
}

/// \brief Testuje obliczanie sum w strukturze drzewa.
/// \details Sprawdza, czy sumy s¹ poprawnie obliczane w okreœlonym przedziale czasowym.
TEST(TreeDataTest, CalculateSumsBetweenDates) {
    TreeData treeData;
    string line1 = "15.10.2023 12:00:00,100.5,200.5,300.5,400.5,500.5";
    string line2 = "15.10.2023 18:00:00,150.5,250.5,350.5,450.5,550.5";
    RowData rd1(line1);
    RowData rd2(line2);
    treeData.addData(rd1);
    treeData.addData(rd2);

    float autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum;
    treeData.calculateSumsBetweenDates("15.10.2023 00:00", "15.10.2023 23:59", autokonsumpcjaSum, eksportSum, importSum, poborSum, produkcjaSum); ///< Obliczanie sum w okreœlonym przedziale czasowym.

    EXPECT_FLOAT_EQ(autokonsumpcjaSum, 251.0); ///< Weryfikacja sum dla autokonsumpcji.
    EXPECT_FLOAT_EQ(eksportSum, 451.0); ///< Weryfikacja sum dla eksportu.
    EXPECT_FLOAT_EQ(importSum, 651.0); ///< Weryfikacja sum dla importu.
    EXPECT_FLOAT_EQ(poborSum, 851.0); ///< Weryfikacja sum dla poboru.
    EXPECT_FLOAT_EQ(produkcjaSum, 1051.0); ///< Weryfikacja sum dla produkcji.
}
