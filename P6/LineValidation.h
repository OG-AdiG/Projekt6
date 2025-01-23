/// \file LineValidation.h
/// \brief Zawiera funkcj� waliduj�c� wiersze z pliku CSV.

#ifndef LINEVALIDATION_H
#define LINEVALIDATION_H

#include <string>
#include <cctype>
#include <algorithm>
#include "LogManager.h" ///< Za��czenie pliku nag��wkowego do obs�ugi logowania.

/// \brief Funkcja sprawdzaj�ca poprawno�� wiersza danych.
/// \details Sprawdza, czy wiersz zawiera odpowiedni� liczb� parametr�w, czy nie jest pusty i czy nie zawiera liter.
/// \param line Wiersz danych wej�ciowych.
/// \return true, je�li wiersz jest poprawny, false w przeciwnym razie.
/// Funkcja ta waliduje wiersz CSV poprzez sprawdzenie jego zawarto�ci, takich jak liczba parametr�w oraz obecno�� niepo��danych liter.
bool lineValidation(const std::string& line)
{
    // Sprawdzenie, czy wiersz jest pusty.
    if (line.empty())
    {
        errorLogger.log("Pusta linia"); ///< Logowanie b��du, gdy linia jest pusta.
        return false;
    }
    // Sprawdzenie, czy wiersz zawiera nag��wek.
    else if (line.find("Time") != std::string::npos)
    {
        errorLogger.log("Znaleziono nag��wek: " + line); ///< Logowanie b��du, gdy wiersz zawiera nag��wek.
        return false;
    }
    // Sprawdzenie, czy wiersz zawiera litery.
    else if (std::any_of(line.begin(), line.end(), [](char c) { return std::isalpha(c); }))
    {
        errorLogger.log("Znaleziono inne dane: " + line); ///< Logowanie b��du, gdy wiersz zawiera litery.
        return false;
    }
    // Sprawdzenie, czy wiersz zawiera odpowiedni� liczb� parametr�w (5 przecink�w).
    else if (std::count(line.begin(), line.end(), ',') != 5)
    {
        errorLogger.log("Nieprawid�owa liczba parametr�w: " + line); ///< Logowanie b��du, gdy liczba parametr�w jest niepoprawna.
        return false;
    }
    else
    {
        return true; ///< Zwracanie true, je�li wiersz jest poprawny.
    }
}

#endif // LINEVALIDATION_H
