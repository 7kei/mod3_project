#include <iostream>
#include <httplib.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
int mainMenu();

int displayCurrencies()
{
    // Clear terminal contents beforehand
    system("cls");

    httplib::Client cli("openexchangerates.org");
    cli.set_default_headers({{"accept","application/json"}});
    auto res = cli.Get("/api/currencies.json?prettyprint=false&show_alternatives=false");

    if (res == nullptr)
        return 1;
    
    std::string bodyResponse = res->body;
    json bodyData = json::parse(bodyResponse);

    printf("#----------------------------------------#\n");
    for (auto& elem : bodyData.items()) {
        std::string key = elem.key();
        std::string value = elem.value();
        printf("%s, %s\n", key.c_str(), value.c_str());
    }
    printf("#----------------------------------------#\n");
    printf("# Press any key to return to menu.       #\n");
    printf("#----------------------------------------#\n");
    system("pause");
    mainMenu();

    return 0;
}

int mainMenu() {
    system("cls");
    unsigned char choice;

    printf("#----------------------------------------#\n");
    printf("# Welcome to the Billing System!         #\n");
    printf("# Select from your functions from below: #\n");
    printf("# 1. Display all supported currencies    #\n");
    printf("# 2. Convert currencies                  #\n");
    printf("#----------------------------------------#\n");
    scanf_s("%c", &choice);

    switch (choice) {
    case '1':
        return displayCurrencies();
        break;
    case '2':
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
    mainMenu();
        
}

