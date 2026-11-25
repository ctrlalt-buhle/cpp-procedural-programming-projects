// input_utils.h
// Small helpers for safe console input.
//
// Why this exists: `cin >> number` leaves the stream in a failed state when the
// user types letters, which causes infinite loops in menu programs. These
// helpers read a whole line, check that it is a complete valid value, and ask
// again until it is. If input ends (Ctrl+D / Ctrl+Z or a closed pipe) the
// program exits cleanly instead of looping forever.
#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace input {

// Show a prompt and read one full line. Exits cleanly if input has ended.
inline std::string readLine(const std::string& prompt) {
    std::string line;
    std::cout << prompt;
    if (!std::getline(std::cin, line)) {
        std::cout << "\nInput closed. Exiting program.\n";
        std::exit(EXIT_FAILURE);
    }
    return line;
}

// Remove leading and trailing spaces/tabs.
inline std::string trim(const std::string& text) {
    const std::string whitespace = " \t\r\n";
    const std::size_t first = text.find_first_not_of(whitespace);
    if (first == std::string::npos) return "";
    const std::size_t last = text.find_last_not_of(whitespace);
    return text.substr(first, last - first + 1);
}

// Keep asking until the user types something other than blank space.
inline std::string readNonEmpty(const std::string& prompt) {
    while (true) {
        const std::string value = trim(readLine(prompt));
        if (!value.empty()) return value;
        std::cout << "Input cannot be empty. Please try again.\n";
    }
}

// Keep asking until the user types a whole number between min and max.
inline int readInt(const std::string& prompt, int min, int max) {
    while (true) {
        std::istringstream stream(trim(readLine(prompt)));
        int value = 0;
        // The value must parse AND nothing else may be left on the line,
        // so "12abc" and "3.5" are rejected.
        if ((stream >> value) && (stream >> std::ws).eof() && value >= min && value <= max) {
            return value;
        }
        std::cout << "Invalid input. Please enter a whole number between "
                  << min << " and " << max << ".\n";
    }
}

// Keep asking until the user types a number greater than 0.
inline double readPositiveDouble(const std::string& prompt) {
    while (true) {
        std::istringstream stream(trim(readLine(prompt)));
        double value = 0.0;
        if ((stream >> value) && (stream >> std::ws).eof() && value > 0.0) {
            return value;
        }
        std::cout << "Invalid input. Please enter a number greater than 0.\n";
    }
}

// Keep asking until the user answers y or n (upper or lower case).
inline bool readYesNo(const std::string& prompt) {
    while (true) {
        const std::string answer = trim(readLine(prompt));
        if (answer == "y" || answer == "Y") return true;
        if (answer == "n" || answer == "N") return false;
        std::cout << "Please answer with y or n.\n";
    }
}

}  // namespace input

#endif  // INPUT_UTILS_H
