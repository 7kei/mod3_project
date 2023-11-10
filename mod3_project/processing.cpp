#include <iostream>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <string>
#include <ctype.h>

namespace Processing 
{

    using json = nlohmann::json;

    std::string apiKey = "INSERT_APIKEY_HERE";

    void toUppercase(char* charArray)
    {
        int i = 0;
        while (charArray[i] != '\0')
        {
            charArray[i++] = toupper((unsigned char)charArray[i]);
        }
    }

    // Function to to get JSON responses from the openexchangerates API
    json apiGetter(std::string urlToGet)
    {
        httplib::Client cli("openexchangerates.org");
        cli.set_default_headers({ {"accept","application/json"} });
        auto res = cli.Get(urlToGet);

        // If response was an error, return null
        if (res->status >= 400)
            return NULL;

        std::string bodyResponse = res->body;
        return json::parse(bodyResponse);
    }

    std::string displayCurrencies()
    {

        std::string stringToReturn = "";

        json bodyData = apiGetter("/api/currencies.json?prettyprint=false&show_alternatives=false");

        if (bodyData == NULL)
        {
            return "NULL";
        }

        unsigned short currencyAmount = 0;
        for (auto& elem : bodyData.items()) {
            stringToReturn = stringToReturn + elem.key() + ", " + (std::string)elem.value() + "\n";
            currencyAmount++;
        }

        stringToReturn = stringToReturn + "There are " + std::to_string(currencyAmount) + " supported currencies.\n";

        return stringToReturn;
    }

    std::string displayExchangeRate()
    {

        std::string stringToReturn = "";

        // Get exchange rate using api key.
        json latestExchangeRateResp = apiGetter("/api/latest.json?app_id=" + apiKey + "&show_alternative = false");

        // If response was null, return early.
        if (latestExchangeRateResp == NULL)
        {
            return "NULL";
        }

        for (auto& elem : latestExchangeRateResp["rates"].items()) {
            stringToReturn += elem.key() + ", " + elem.value().dump() + "\n";
        }

        return stringToReturn;
    }

    std::string convertCurrency(double amount, char fromCurrency[], char toCurrency[])
    {
        double toUsd;
        double toTargetCurrency;

        std::string stringToReturn = "";

        // Set fromCurrency and toCurrency uppercase
        toUppercase(fromCurrency);
        toUppercase(toCurrency);

        // Get exchange rate using api key.
        json latestExchangeRateResp = apiGetter("/api/latest.json?app_id=" + apiKey + "&show_alternative = false");

        // If response was null, return early.
        if (latestExchangeRateResp == NULL)
        {
            return "NULL";
        }

        auto& rates = latestExchangeRateResp["rates"];

        if (rates.find(fromCurrency) == rates.end() || rates.find(toCurrency) == rates.end())
        {
            return "NULL";
        }

        // Convert to USD
        toUsd = amount / (double)rates[fromCurrency];

        // Convert from usd to target currency
        toTargetCurrency = toUsd * (double)rates[toCurrency];

        // Output
        std::ostringstream stringstream;
        
        stringstream.imbue(std::locale(""));
        stringstream << std::put_money(toTargetCurrency * 100) << " " << toCurrency << std::endl;

        stringToReturn = stringstream.str();

        return stringToReturn;
    }

}
