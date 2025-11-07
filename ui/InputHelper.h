#ifndef INPUTHELPER_H
#define INPUTHELPER_H
#include <string>
#include <iostream>
#include <numeric>


class InputHelper {
public:
    static int ReadInt(const std::string& prompt, int min, int max) {
        int value;
        while (true) {
            std::cout << prompt << std::endl;
            std::cin >> value;

            // Если ввод не число
            if (std::cin.fail()) {
                std::cout << "Error: please enter a valid integer." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер ввода
                continue;
            }

            // Очищаем оставшуюся часть строки в буфере
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (value >= min && value <= max) {
                return value;
            }
            std::cout << "Error: the number must be between " << min << " and " << max << "." << std::endl;
        }
    }

    static std::string ReadString(const std::string& prompt) {
        std::cout << prompt << std::endl;
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    static double ReadDouble(const std::string& prompt, bool allow_negative = false) {
        double value;
        while (true) {
            std::cout << prompt << std::endl;
            std::cin >> value;

            if (std::cin.fail()) {
                std::cout << "Error: Please enter a valid number (e.g., 123.45)." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!allow_negative && value < 0) {
                std::cout << "Error: The amount cannot be negative." << std::endl;
                continue;
            }
            return value;
        }
    }

private:
    InputHelper() = default;
};


#endif //INPUTHELPER_H
