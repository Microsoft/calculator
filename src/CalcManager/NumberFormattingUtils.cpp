#include "pch.h"
#include "NumberFormattingUtils.h"
#include <iostream>
#include <math.h>
using namespace std;

namespace CalculationManager::NumberFormattingUtils
{
    /// <summary>
    /// Trims out any trailing zeros or decimals in the given input string
    /// </summary>
    /// <param name="number">number to trim</param>
    void TrimTrailingZeros(_Inout_ wstring& number)
    {
        if (number.find(L'.') == wstring::npos)
        {
            return;
        }

        wstring::iterator iter;
        for (iter = number.end() - 1;; iter--)
        {
            if (*iter != L'0')
            {
                number.erase(iter + 1, number.end());
                break;
            }
        }
        if (*(number.end() - 1) == L'.')
        {
            number.erase(number.end() - 1, number.end());
        }
    }

    /// <summary>
    /// Get number of digits (whole number part + decinmal part)</summary>
    /// <param name="value">the number</param>
    unsigned int GetNumberDigits(wstring value)
    {
        TrimTrailingZeros(value);
        unsigned int numberSignificantDigits = static_cast<unsigned int>(value.size());
        if (value.find(L'.') != wstring::npos)
        {
            --numberSignificantDigits;
        }
        if (value.find(L'-') != wstring::npos)
        {
            --numberSignificantDigits;
        }
        return numberSignificantDigits;
    }

    /// <summary>
    /// Get number of digits (whole number part only)</summary>
    /// <param name="value">the number</param>
    unsigned int GetNumberDigitsWholeNumberPart(double value)
    {
        return value == 0 ? 1 : (1 + (int)log10(abs(value)));
    }

    /// <summary>
    /// Rounds the given double to the given number of significant digits
    /// </summary>
    /// <param name="num">input double</param>
    /// <param name="numSignificant">int number of significant digits to round to</param>
    wstring RoundSignificantDigits(double num, int numSignificant)
    {
        wstringstream out(wstringstream::out);
        out << fixed;
        out.precision(numSignificant);
        out << num;
        return out.str();
    }

    /// <summary>
    ///  Convert a Number to Scientific Notation
    /// </summary>
    /// <param name="number">number to convert</param>
    wstring ToScientificNumber(double number)
    {
        wstringstream out(wstringstream::out);
        out << scientific << number;
        return out.str();
    }
}
