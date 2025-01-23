/// \file LineValidation.h
/// \brief Zawiera funkcjê waliduj¹c¹ wiersze z pliku CSV.

#ifndef LINEVALIDATION_H
#define LINEVALIDATION_H

#include <string>
#include <cctype>
#include <algorithm>
#include "LogManager.h" ///< Za³¹czenie pliku nag³ówkowego do obs³ugi logowania.

/// \brief Funkcja sprawdzaj¹ca poprawnoœæ wiersza danych.
/// \details Sprawdza, czy wiersz zawiera odpowiedni¹ liczbê parametrów, czy nie jest pusty i czy nie zawiera liter.
/// \param line Wiersz danych wejœciowych.
/// \return true, jeœli wiersz jest poprawny, false w przeciwnym razie.
/// Funkcja ta waliduje wiersz CSV poprzez sprawdzenie jego zawartoœci, takich jak liczba parametrów oraz obecnoœæ niepo¿¹danych liter.
bool lineValidation(const std::string& line)
{
    // Sprawdzenie, czy wiersz jest pusty.
    if (line.empty())
    {
        errorLogger.log("Pusta linia"); ///< Logowanie b³êdu, gdy linia jest pusta.
        return false;
    }
    // Sprawdzenie, czy wiersz zawiera nag³ówek.
    else if (line.find("Time") != std::string::npos)
    {
        errorLogger.log("Znaleziono nag³ówek: " + line); ///< Logowanie b³êdu, gdy wiersz zawiera nag³ówek.
        return false;
    }
    // Sprawdzenie, czy wiersz zawiera litery.
    else if (std::any_of(line.begin(), line.end(), [](char c) { return std::isalpha(c); }))
    {
        errorLogger.log("Znaleziono inne dane: " + line); ///< Logowanie b³êdu, gdy wiersz zawiera litery.
        return false;
    }
    // Sprawdzenie, czy wiersz zawiera odpowiedni¹ liczbê parametrów (5 przecinków).
    else if (std::count(line.begin(), line.end(), ',') != 5)
    {
        errorLogger.log("Nieprawid³owa liczba parametrów: " + line); ///< Logowanie b³êdu, gdy liczba parametrów jest niepoprawna.
        return false;
    }
    else
    {
        return true; ///< Zwracanie true, jeœli wiersz jest poprawny.
    }
}

#endif // LINEVALIDATION_H
