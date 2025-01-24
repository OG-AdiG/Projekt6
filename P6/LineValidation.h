/// \file LineValidation.h
/// \brief Zawiera funkcję walidującą wiersze z pliku CSV.

#ifndef LINEVALIDATION_H
#define LINEVALIDATION_H

#include <string>
#include <cctype>
#include <algorithm>
#include "LogManager.h" ///< Załączenie pliku nagłówkowego do obsługi logów

/// \brief Funkcja sprawdzająca poprawność wiersza danych.
/// \details Sprawdza, czy wiersz zawiera odpowiednią liczbę parametrów, czy nie jest pusty i czy nie zawiera liter.
/// \param line Wiersz danych wejściowych.
/// \return true, jeśli wiersz jest poprawny, false w przeciwnym razie.
/// Funkcja ta waliduje wiersz CSV poprzez sprawdzenie jego zawartości, takich jak liczba parametrów oraz obecność niepożądanych liter.
bool lineValidation(const std::string& line)
{
    // Sprawdzenie, czy wiersz jest pusty.
    if (line.empty())
    {
        errorLogger.log("Pusta linia"); ///< Logowanie błędu, gdy linia jest pusta.
        return false;
    }
    // Sprawdzenie, czy wiersz zawiera nagłówek.
    else if (line.find("Time") != std::string::npos)
    {
        errorLogger.log("Znaleziono nagłówek: " + line); ///< Logowanie błędu, gdy wiersz zawiera nagłówek.
        return false;
    }
    // Sprawdzenie, czy wiersz zawiera litery.
    else if (std::any_of(line.begin(), line.end(), [](char c) { return std::isalpha(c); }))
    {
        errorLogger.log("Znaleziono inne dane: " + line); ///< Logowanie błędu, gdy wiersz zawiera litery.
        return false;
    }
    // Sprawdzenie, czy wiersz zawiera odpowiednią liczbę parametrów (5 przecinków).
    else if (std::count(line.begin(), line.end(), ',') != 5)
    {
        errorLogger.log("Nieprawidłowa liczba parametrów: " + line); ///< Logowanie błędu, gdy liczba parametrów jest niepoprawna.
        return false;
    }
    else
    {
        return true; ///< Zwracanie true, jeśli wiersz jest poprawny.
    }
}

#endif // LINEVALIDATION_H
