#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

bool is_numeric(std::string str) {
    for (char ch : str) {
        if (!isdigit(ch) && ch != '-' && ch != ','){
            return false;
        }
    }
    return true;
}

std::unordered_map<std::string, std::vector<float>> read_municipal_tax_rates(std::string mun_tax_file) {

    std::ifstream file(mun_tax_file);

    try {
        if (!file.is_open()) {
            throw 505;
        }
    } catch (int num) {
        std::cout << "Could not open file: " + mun_tax_file;

    }

    std::unordered_map<std::string, std::vector<float>> mun_tax_rates;
    std::string row;
    while (std::getline (file, row)) {
        std::stringstream ss(row);

        std::string token;
        std::vector<std::string> mun_name_parts;
        std::vector<float> numerics;
        while (ss >> token) {

            std::string weird_minus = "‑";
            size_t pos = token.find(weird_minus);
            if (pos != std::string::npos) {
                token.replace(pos, weird_minus.length(), "-");
            }

            std::ranges::replace(token, ',', '.');

            try {
                float numeric = std::stof(token);
                numerics.push_back(numeric);
            } catch (std::exception e) {
                mun_name_parts.push_back(token);
            }
        }

        std::string mun_name;
        for (int i = 0; i < mun_name_parts.size(); i++) {
            if (i != 0) {
                mun_name += " ";
            }
            mun_name += mun_name_parts[i];
        }

        mun_tax_rates[mun_name] = numerics;

    }

    file.close();

    return mun_tax_rates;
}

int main()
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    std::string mun_tax_file = "municipal_tax_rates.txt";
    std::unordered_map<std::string, std::vector<float>> mun_tax_rates = read_municipal_tax_rates(mun_tax_file);
    std::cout << mun_tax_rates["Ale"][4];
    return 0;
}
