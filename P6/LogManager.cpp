/// \file LogManager.cpp
/// \brief Implementacja klasy LogManager do obs�ugi logowania komunikat�w.

#include "LogManager.h"
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <sstream>

/// \var globalLogger
/// \brief Globalny logger dla standardowych komunikat�w.
/// Logger ten jest u�ywany do zapisywania standardowych komunikat�w informacyjnych do pliku.
LogManager globalLogger("log");

/// \var errorLogger
/// \brief Globalny logger dla komunikat�w b��d�w.
/// Logger ten jest u�ywany do zapisywania komunikat�w zwi�zanych z b��dami do pliku.
LogManager errorLogger("log_error");

/// \var errorLogCount
/// \brief Licznik wyst�pie� b��d�w logowanych przez errorLogger.
/// Licznik jest zwi�kszany za ka�dym razem, gdy loggerError zapisuje komunikat b��du.
int errorLogCount = 0;


/// \brief Konstruktor klasy LogManager.
/// \details Tworzy plik logu z unikaln� nazw� opart� na aktualnej dacie i godzinie.
/// \param filename Nazwa podstawowa pliku logu, kt�ra b�dzie u�yta do stworzenia pe�nej nazwy pliku.
/// Konstruktor generuje nazw� pliku logu opart� na dacie i godzinie, a nast�pnie otwiera ten plik do zapisu.
LogManager::LogManager(const std::string& filename) {
    auto t = std::time(nullptr); ///< Pobranie bie��cego czasu.
    std::tm tm; ///< Struktura przechowuj�ca czas w formacie lokalnym.
    localtime_s(&tm, &t); ///< Konwersja czasu na lokalny format.
    std::ostringstream oss; ///< Strumie� do tworzenia �a�cucha tekstowego z nazw� pliku.
    oss << filename << "_" << std::put_time(&tm, "%d%m%Y_%H%M%S") << ".txt"; ///< Budowanie pe�nej nazwy pliku.
    std::string datedFilename = oss.str(); ///< Nazwa pliku z dat� i godzin�.

    // Usuwanie istniej�cego pliku logu, je�li ju� istnieje.
    if (std::remove(datedFilename.c_str()) != 0) {
        // Plik nie istnieje lub nie mo�na go usun��.
    }

    logFile.open(datedFilename, std::ios::out | std::ios::app); ///< Otwieranie pliku logu w trybie do zapisu.
    if (!logFile.is_open()) {
        throw std::runtime_error("Nie mo�na otworzy� pliku logu"); ///< Rzucenie wyj�tku, je�li nie uda�o si� otworzy� pliku.
    }
}

/// \brief Destruktor klasy LogManager.
/// \details Zamyka otwarty plik logu, zapewniaj�c, �e wszystkie dane zosta�y zapisane.
LogManager::~LogManager() {
    if (logFile.is_open()) {
        logFile.close(); ///< Zamkni�cie strumienia pliku logu.
    }
}

/// \brief Zapisuje komunikat do pliku logu.
/// \param message Komunikat do zapisania w pliku logu.
/// Funkcja zapisuje podany komunikat do pliku logu wraz z bie��c� dat� i godzin�.
void LogManager::log(const std::string& message) {
    if (logFile.is_open()) {
        auto t = std::time(nullptr); ///< Pobranie bie��cego czasu.
        std::tm tm; ///< Struktura przechowuj�ca czas w formacie lokalnym.
        localtime_s(&tm, &t); ///< Konwersja czasu na lokalny format.
        logFile << std::put_time(&tm, "%d.%m.%Y %H:%M:%S") << " " << message << std::endl; ///< Zapisanie komunikatu z dat� i godzin�.
    }

    // Zwi�kszanie licznika b��d�w, je�li logowany komunikat pochodzi z errorLogger.
    if (this == &errorLogger) {
        ++errorLogCount;
    }
}
