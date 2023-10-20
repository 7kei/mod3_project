#include <iostream>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;
int mainMenu();

json apiGetter(std::string urlToGet)
{
    httplib::Client cli("openexchangerates.org");
    cli.set_default_headers({ {"accept","application/json"} });
    auto res = cli.Get(urlToGet);

    if (res == nullptr)
        return 1;

    std::string bodyResponse = res->body;
    return json::parse(bodyResponse);
}

int displayCurrencies()
{
    // Clear terminal contents beforehand
    system("cls");

    json bodyData = apiGetter("/api/currencies.json?prettyprint=false&show_alternatives=false");

    std::cout << "#----------------------------------------#" << std::endl;
    for (auto& elem : bodyData.items()) {
        std::cout << elem.key() << ", " << elem.value() << std::endl;
    }
    std::cout << "#----------------------------------------#\n"
              << "# Press any key to return to menu.       #\n"
              << "#----------------------------------------#"   << std::endl;
    system("pause");
    mainMenu();

    return 0;
}

int displayExchangeRate()
{
    system("cls");

    std::string apiKey = "";
    json latestExchangeRateResp = apiGetter("/api/latest.json?app_id="+apiKey+"&show_alternative = false");

    std::cout << "#----------------------------------------#\n"
              << "# From base USD:                         #" << std::endl;
    for (auto& elem : latestExchangeRateResp["rates"].items()) {
        std::cout << elem.key() << ", " << elem.value() << std::endl;
    }
    std::cout << "#----------------------------------------#\n"
              << "# Press any key to return to menu.       #\n"
              << "#----------------------------------------#" << std::endl;
    system("pause");
    mainMenu();

    return 0;
}

int convertCurrency()
{
    system("cls");

    long double amount;
    char fromCurrency[4]{};
    char toCurrency[4]{};

    long double toUsd;
    long double toTargetCurrency;

    std::cout << "#----------------------------------------#\n"
              << "# Input your desired amount:             #\n"
              << "#----------------------------------------#" << std::endl;

    std::cin >> amount;

    std::cout << "#----------------------------------------#\n"
              << "# Input from currency                    #\n"
              << "#----------------------------------------#" << std::endl;
    std::cin >> fromCurrency;

    std::cout << "#----------------------------------------#\n"
              << "# Input to currency                      #\n"
              << "#----------------------------------------#" << std::endl;
    std::cin >> toCurrency;

    std::string apiKey = "";
    json latestExchangeRateResp = apiGetter("/api/latest.json?app_id=" + apiKey + "&show_alternative = false");

    // convert to usd
    toUsd = amount / (long double)latestExchangeRateResp["rates"][fromCurrency];
    std::cout << amount << " / " << (long double)latestExchangeRateResp["rates"][fromCurrency] << " = " << toUsd << std::endl;
    toTargetCurrency = toUsd * (long double)latestExchangeRateResp["rates"][toCurrency];
    std::cout << toUsd << " * " << (long double)latestExchangeRateResp["rates"][toCurrency] << " = " << toTargetCurrency << std::endl;

    std::cout << toTargetCurrency << std::endl;

    system("pause");
    mainMenu();

    return 0;
}

int mainMenu() {
    system("cls");
    unsigned char choice;

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
        mainMenu();
        break;
    }
}

int main()
{
    
    // Clear terminal contents beforehand
    system("cls");

    // Menu
    return mainMenu();
        
}

