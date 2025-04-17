#include "calculator.hpp"
#include <iostream>

// Checks if the given character is a number
bool is_num(char c) {
    if (c >= '0' && c <= '9') { // Checks if the character is a number by checking its ascii value
        return true; // Returns true if it is a number
    } else {
        return false; // Returns false if it is not a number
    }
}

bool is_valid_double(const std::string &line) {
    // Returns false if the line is empty
    if (line.empty()) {
        return false;
    }

    const int num_char = line.length() // Gets the number of characters in the line

    int num_dots = 0; // Makes variable to track number of dots in the line

    // Iterates over each character in the line
    for (int i = 0; i < num_char; i++) {
        // Checks if the character is a '+' or '-'
        if (line[i] == '+' or line[i] == '-') {
            if (i != 0) {
                return false; // '+' or '-' only allowed as the first character
            } else if (i + 1 >= num_char) {
                return false // Sign cannot be last character
            } else if (!is_num(line[i + 1]) && line[i + 1] != '.') {
                return false // Sign must be followed by a number or a '.'
            }

        }
        
        // Checks if the character is a dot
        else if (line[i] == '.') {
            if (i + 1 >= num_char) {
                return false // Dot cannot be last character
            } else if (!is_num(line[i + 1])) {
                return false // Dot must be followed by a number
            }

            num_dots++; // Increment the dot counter

        }
        
        // Checks if the character is a valid number
        else if (!is_num(line[i])) {
            return false; // Invalid character in the string
        }
    }

    if (num_dots <= 1) {
        return true;
    }

}

double parse_number(const std::string &expression) {

}