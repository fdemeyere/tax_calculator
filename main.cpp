#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

void read_municipal_tax_rates(std::string mun_tax_file) {

    std::ifstream file(mun_tax_file);

    if (!file.is_open()) {
        std::cout << "Could not open file: " + mun_tax_file;
        return;
    } else {
        std::cout << "Successfully opened file" << std::endl;
    }

    std::string row;
    int i = 0;
    while (std::getline (file, row)) {
        if (i == 2) break;
        std::stringstream ss(row);

        std::string token;
        while (ss >> token) {
            std::cout << token << std::endl;
        }

        i++;
    }

    // Close the file
    file.close();

}

int main()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    std::string mun_tax_file = "municipal_tax_rates.txt";
    read_municipal_tax_rates(mun_tax_file);
    return 0;
}
