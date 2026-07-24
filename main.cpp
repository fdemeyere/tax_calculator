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

float get_municipal_regional_sum_tax_rate(std::string mun, std::unordered_map<std::string, std::vector<float>> mun_tax_rates) {
    return mun_tax_rates[mun][0];
}

float get_municipal_tax_rate(std::string mun, std::unordered_map<std::string, std::vector<float>> mun_tax_rates) {
    return mun_tax_rates[mun][2];
}

float get_regional_tax_rate_by_municipality(std::string mun, std::unordered_map<std::string, std::vector<float>> mun_tax_rates) {
    return mun_tax_rates[mun][4];
}

std::vector<std::string> get_municipalites_by_municipal_regional_sum_tax_rate(bool desc) {

}

void terminal_loop(std::unordered_map<std::string, std::vector<float>> mun_tax_rates) {
    std::string input;
    std::cout << "Kommunal och regionalskattesats efter kommun" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::cout << "Kommun: ";
    while (std::getline(std::cin, input)) {

        if (input == "quit") {
            break;
        }

        if (input.empty()) continue;
        if (mun_tax_rates.contains(input)) {
            std::cout << "Kommunalskatt: " << get_municipal_tax_rate(input, mun_tax_rates) << "%" << std::endl;
            std::cout << "Regionalskatt: " << get_regional_tax_rate_by_municipality(input, mun_tax_rates) << "%" << std::endl;
            std::cout << "Totalt: " << get_municipal_regional_sum_tax_rate(input, mun_tax_rates) << "%" << std::endl;
        } else {
            std::cout << "Hittade inte kommunen" << std::endl;
        }

        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Kommun: ";
    }
}

int main()
{
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif

    std::string mun_tax_file = "municipal_tax_rates.txt";
    std::unordered_map<std::string, std::vector<float>> mun_tax_rates = read_municipal_tax_rates(mun_tax_file);

    terminal_loop(mun_tax_rates);

    // std::cout << get_municipal_regional_sum_tax_rate("Alingsås", mun_tax_rates);
    return 0;
}
