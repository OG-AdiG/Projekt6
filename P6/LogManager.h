/// \file LogManager.h
/// \brief Deklaracja klasy LogManager do obs³ugi logowania komunikatów.

#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <fstream>
#include <string>

/// \class LogManager
/// \brief Klasa obs³uguj¹ca logowanie komunikatów do plików tekstowych.
class LogManager {
public:
    /// \brief Konstruktor klasy LogManager.
    /// \details Tworzy plik logu z unikaln¹ nazw¹ opart¹ na aktualnej dacie i godzinie.
    /// \param filename Nazwa podstawowa pliku logu, która bêdzie u¿yta do stworzenia pe³nej nazwy pliku.
    /// Konstruktor inicjalizuje strumieñ wyjœciowy do zapisywania komunikatów logu do pliku.
    LogManager(const std::string& filename);

    /// \brief Destruktor klasy LogManager.
    /// \details Zamyka otwarty plik logu, zapewniaj¹c, ¿e wszystkie dane zosta³y zapisane.
    ~LogManager();

    /// \brief Zapisuje komunikat do pliku logu.
    /// \param message Komunikat do zapisania w pliku logu.
    /// Funkcja ta zapisuje podany komunikat do otwartego pliku logu.
    void log(const std::string& message);

private:
    std::ofstream logFile; ///< Strumieñ pliku logu, u¿ywany do zapisywania komunikatów.
};

/// \var globalLogger
/// \brief Globalny logger dla standardowych komunikatów.
/// Logger ten jest u¿ywany do zapisywania komunikatów informacyjnych oraz standardowych.
extern LogManager globalLogger;


/// \var errorLogger
/// \brief Globalny logger dla komunikatów b³êdów.
/// Logger ten jest u¿ywany do zapisywania komunikatów zwi¹zanych z b³êdami oraz wyj¹tkami.
extern LogManager errorLogger;


/// \var errorLogCount
/// \brief Licznik wyst¹pieñ b³êdów logowanych przez errorLogger.
/// Zmienna ta przechowuje liczbê b³êdów zarejestrowanych przez errorLogger.
extern int errorLogCount;

#endif // LOGMANAGER_H
