#pragma once

namespace Processing 
{
	#include <string>

	// define function protos

	void toUppercase(char* charArray);
	std::string displayCurrencies();
	std::string displayExchangeRate();
	std::string convertCurrency(double amount, char fromCurrency[], char toCurrency[]);
}