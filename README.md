# mod3_project (A C++ Currency Converter)

## About

This is a school project. It converts currency from one to the other. It depends on the [Open Exchange Rate API](https://openexchangerates.org/) for currency data.

## Building

### Requirements

- Windows 11
- Visual Studio 2022
- Qt 6
- [microsoft/vcpkg](https://github.com/microsoft/vcpkg)
- [nlohmann/json](https://github.com/nlohmann/json)
- [yhirose/cpp-httplib](https://github.com/yhirose/cpp-httplib)
- An api key from [Open Exchange Rates](https://openexchangerates.org/)

### How to Compile

1. Setup vcpkg:
    - Follow these instructions! <https://github.com/microsoft/vcpkg#getting-started> 
2. Install the json and http library through vcpkg:
    - For 64-bit targets:
        - `vcpkg install nlohmann-json:x64-windows-static`
        - `vcpkg install cpp-httplib:x64-windows-static`
        - `vcpkg integrate install`
3. Add your API key in the Processing.cpp file.
4. Compile through Visual Studio 2022 or MSVC.

## License

This project uses the MIT license. [Learn more here.](https://choosealicense.com/licenses/mit/)
