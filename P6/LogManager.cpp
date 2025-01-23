/// \file LogManager.cpp
/// \brief Implementacja klasy LogManager do obs³ugi logowania komunikatów.

#include "LogManager.h"
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <sstream>

/// \var globalLogger
/// \brief Globalny logger dla standardowych komunikatów.
/// Logger ten jest u¿ywany do zapisywania standardowych komunikatów informacyjnych do pliku.
LogManager globalLogger("log");

/// \var errorLogger
/// \brief Globalny logger dla komunikatów b³êdów.
/// Logger ten jest u¿ywany do zapisywania komunikatów zwi¹zanych z b³êdami do pliku.
LogManager errorLogger("log_error");

/// \var errorLogCount
/// \brief Licznik wyst¹pieñ b³êdów logowanych przez errorLogger.
/// Licznik jest zwiêkszany za ka¿dym razem, gdy loggerError zapisuje komunikat b³êdu.
int errorLogCount = 0;


/// \brief Konstruktor klasy LogManager.
/// \details Tworzy plik logu z unikaln¹ nazw¹ opart¹ na aktualnej dacie i godzinie.
/// \param filename Nazwa podstawowa pliku logu, która bêdzie u¿yta do stworzenia pe³nej nazwy pliku.
/// Konstruktor generuje nazwê pliku logu opart¹ na dacie i godzinie, a nastêpnie otwiera ten plik do zapisu.
LogManager::LogManager(const std::string& filename) {
    auto t = std::time(nullptr); ///< Pobranie bie¿¹cego czasu.
    std::tm tm; ///< Struktura przechowuj¹ca czas w formacie lokalnym.
    localtime_s(&tm, &t); ///< Konwersja czasu na lokalny format.
    std::ostringstream oss; ///< Strumieñ do tworzenia ³añcucha tekstowego z nazw¹ pliku.
    oss << filename << "_" << std::put_time(&tm, "%d%m%Y_%H%M%S") << ".txt"; ///< Budowanie pe³nej nazwy pliku.
    std::string datedFilename = oss.str(); ///< Nazwa pliku z dat¹ i godzin¹.

    // Usuwanie istniej¹cego pliku logu, jeœli ju¿ istnieje.
    if (std::remove(datedFilename.c_str()) != 0) {
        // Plik nie istnieje lub nie mo¿na go usun¹æ.
    }

    logFile.open(datedFilename, std::ios::out | std::ios::app); ///< Otwieranie pliku logu w trybie do zapisu.
    if (!logFile.is_open()) {
        throw std::runtime_error("Nie mo¿na otworzyæ pliku logu"); ///< Rzucenie wyj¹tku, jeœli nie uda³o siê otworzyæ pliku.
    }
}

/// \brief Destruktor klasy LogManager.
/// \details Zamyka otwarty plik logu, zapewniaj¹c, ¿e wszystkie dane zosta³y zapisane.
LogManager::~LogManager() {
    if (logFile.is_open()) {
        logFile.close(); ///< Zamkniêcie strumienia pliku logu.
    }
}

/// \brief Zapisuje komunikat do pliku logu.
/// \param message Komunikat do zapisania w pliku logu.
/// Funkcja zapisuje podany komunikat do pliku logu wraz z bie¿¹c¹ dat¹ i godzin¹.
void LogManager::log(const std::string& message) {
    if (logFile.is_open()) {
        auto t = std::time(nullptr); ///< Pobranie bie¿¹cego czasu.
        std::tm tm; ///< Struktura przechowuj¹ca czas w formacie lokalnym.
        localtime_s(&tm, &t); ///< Konwersja czasu na lokalny format.
        logFile << std::put_time(&tm, "%d.%m.%Y %H:%M:%S") << " " << message << std::endl; ///< Zapisanie komunikatu z dat¹ i godzin¹.
    }

    // Zwiêkszanie licznika b³êdów, jeœli logowany komunikat pochodzi z errorLogger.
    if (this == &errorLogger) {
        ++errorLogCount;
    }
}
