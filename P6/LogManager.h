/// \file LogManager.h
/// \brief Deklaracja klasy LogManager do obs�ugi logowania komunikat�w.

#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <fstream>
#include <string>

/// \class LogManager
/// \brief Klasa obs�uguj�ca logowanie komunikat�w do plik�w tekstowych.
class LogManager {
public:
    /// \brief Konstruktor klasy LogManager.
    /// \details Tworzy plik logu z unikaln� nazw� opart� na aktualnej dacie i godzinie.
    /// \param filename Nazwa podstawowa pliku logu, kt�ra b�dzie u�yta do stworzenia pe�nej nazwy pliku.
    /// Konstruktor inicjalizuje strumie� wyj�ciowy do zapisywania komunikat�w logu do pliku.
    LogManager(const std::string& filename);

    /// \brief Destruktor klasy LogManager.
    /// \details Zamyka otwarty plik logu, zapewniaj�c, �e wszystkie dane zosta�y zapisane.
    ~LogManager();

    /// \brief Zapisuje komunikat do pliku logu.
    /// \param message Komunikat do zapisania w pliku logu.
    /// Funkcja ta zapisuje podany komunikat do otwartego pliku logu.
    void log(const std::string& message);

private:
    std::ofstream logFile; ///< Strumie� pliku logu, u�ywany do zapisywania komunikat�w.
};

/// \var globalLogger
/// \brief Globalny logger dla standardowych komunikat�w.
/// Logger ten jest u�ywany do zapisywania komunikat�w informacyjnych oraz standardowych.
extern LogManager globalLogger;


/// \var errorLogger
/// \brief Globalny logger dla komunikat�w b��d�w.
/// Logger ten jest u�ywany do zapisywania komunikat�w zwi�zanych z b��dami oraz wyj�tkami.
extern LogManager errorLogger;


/// \var errorLogCount
/// \brief Licznik wyst�pie� b��d�w logowanych przez errorLogger.
/// Zmienna ta przechowuje liczb� b��d�w zarejestrowanych przez errorLogger.
extern int errorLogCount;

#endif // LOGMANAGER_H
