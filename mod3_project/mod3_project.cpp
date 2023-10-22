#include <iostream>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <string>
#include <ctype.h>

using json = nlohmann::json;
int mainMenu();

void reset() 
{
    // Clear cin buffer
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    mainMenu();
}

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

int displayCurrencies()
{
    // Clear terminal contents beforehand
    system("cls");

    json bodyData = apiGetter("/api/currencies.json?prettyprint=false&show_alternatives=false");

    // If response was null, return early.
    if (bodyData == NULL) 
    {
        std::cout << "#----------------------------------------#\n"
                  << "# Could not get currency information.    #\n"
                  << "# Press any key to return to menu.       #\n"
                  << "#----------------------------------------#" << std::endl;
        system("pause");
        reset();

        return 1;
    }

    unsigned short currencyAmount = 0;
    std::cout << "#----------------------------------------#" << std::endl;
    for (auto& elem : bodyData.items()) {
        std::cout << elem.key() << ", " << elem.value() << std::endl;
        currencyAmount++;
    }
    std::cout << "There are " << currencyAmount << " supported currencies.\n"
              << "#----------------------------------------#\n"
              << "# Press any key to return to menu.       #\n"
              << "#----------------------------------------#"   << std::endl;
    system("pause");
    reset();

    return 0;
}

int displayExchangeRate()
{
    // Clear terminal contents beforehand
    system("cls");

    // Get exchange rate using api key.
    std::string apiKey = "";
    json latestExchangeRateResp = apiGetter("/api/latest.json?app_id="+apiKey+"&show_alternative = false");

    // If response was null, return early.
    if (latestExchangeRateResp == NULL)
    {
        std::cout << "#----------------------------------------#\n"
                  << "# Could not get currency information.    #\n"
                  << "# Press any key to return to menu.       #\n"
                  << "#----------------------------------------#" << std::endl;
        system("pause");
        reset();

        return 1;
    }

    std::cout << "#----------------------------------------#\n"
              << "# From base USD:                         #" << std::endl;
    for (auto& elem : latestExchangeRateResp["rates"].items()) {
        std::cout << elem.key() << ", " << elem.value() << std::endl;
    }
    std::cout << "#----------------------------------------#\n"
              << "# Press any key to return to menu.       #\n"
              << "#----------------------------------------#" << std::endl;
    system("pause");
    reset();

    return 0;
}

int convertCurrency()
{
    // Clear terminal contents beforehand
    system("cls");

    // Variable initializations
    double amount;
    char fromCurrency[4]{};
    char toCurrency[4]{};
    double toUsd;
    double toTargetCurrency;

    // For error checking the user interaction, we put everything in a try/catch block
    try 
    {
        std::cout << "#----------------------------------------#\n"
                  << "# Input your desired amount:             #\n"
                  << "#----------------------------------------#" << std::endl;

        std::cin >> amount;
        if (std::cin.fail())
            throw 2;

        std::cout << "#----------------------------------------#\n"
                  << "# Input from currency                    #\n"
                  << "#----------------------------------------#" << std::endl;
        std::cin >> fromCurrency;
        if (std::cin.fail())
            throw 3;

        std::cout << "#----------------------------------------#\n"
                  << "# Input to currency                      #\n"
                  << "#----------------------------------------#" << std::endl;
        std::cin >> toCurrency;
        if (std::cin.fail())
            throw 4;
    }
    catch (int errorCode) 
    {
        std::string error;

        switch (errorCode) 
        {
        case 2:
            error = "# Error inputting amount.                #\n";
            break;
        case 3:
            error = "# Error inputting from currency.         #\n";
            break;
        case 4:
            error = "# Error inputting to currency.           #\n";
            break;
        }
        std::cout << "#----------------------------------------#\n"
                  << error 
                  << "# Press any key to return to menu.       #\n"
                  << "#----------------------------------------#" << std::endl;

        system("pause");
        reset();

        return 1;
    }

    // Set fromCurrency and toCurrency uppercase
    toUppercase(fromCurrency);
    toUppercase(toCurrency);
    
    // Get exchange rate using api key.
    std::string apiKey = "";
    json latestExchangeRateResp = apiGetter("/api/latest.json?app_id=" + apiKey + "&show_alternative = false");

    // If response was null, return early.
    if (latestExchangeRateResp == NULL)
    {
        std::cout << "#----------------------------------------#\n"
                  << "# Could not get currency information.    #\n"
                  << "# Press any key to return to menu.       #\n"
                  << "#----------------------------------------#" << std::endl;
        system("pause");
        reset();
        return 1;
    }

    auto& rates = latestExchangeRateResp["rates"];

    if (rates.find(fromCurrency) == rates.end() || rates.find(toCurrency) == rates.end())
    {
        std::cout << "#----------------------------------------#\n"
                  << "# Starting/ending currency is invalid.   #\n"
                  << "# Press any key to return to menu.       #\n"
                  << "#----------------------------------------#" << std::endl;
        system("pause");
        reset();
        return 1;

    }

    // Convert to USD
    toUsd = amount / (double)rates[fromCurrency];

    // Convert from usd to target currency
    toTargetCurrency = toUsd * (double)rates[toCurrency];

    // Output
    std::cout << toTargetCurrency << " " << toCurrency << std::endl;

    system("pause");
    reset();

    return 0;
}

int mainMenu() 
{
    // Clear terminal contents beforehand
    system("cls");

    char choice;

    std::cout << "#----------------------------------------#\n"
              << "# Welcome to the Billing System!         #\n"
              << "# Select from your functions from below: #\n"
              << "# 1. Display all supported currencies    #\n"
              << "# 2. Display current exchange rates      #\n"
              << "# 3. Convert currencies                  #\n"
              << "#----------------------------------------#"   << std::endl;

    std::cin >> choice;

    switch (choice) {
    case '1':
        return displayCurrencies();
        break;
    case '2':
        return displayExchangeRate();
        break;
    case '3':
        return convertCurrency();
        break;
    default:
        reset();
        break;
    }

    return 0;
}

int main()
{
    // Clear terminal contents beforehand
    system("cls");

    // Menu
    return mainMenu();
}
