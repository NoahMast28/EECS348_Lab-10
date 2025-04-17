#include "calculator.hpp"
#include <iostream>
#include <string>
#include <sstream> // Not used for validation, only used in parse_number which is after validation
#include <cstdlib> // For std::abs

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

    const int num_char = line.length(); // Gets the number of characters in the line

    int num_dots = 0; // Makes variable to track number of dots in the line

    // Iterates over each character in the line
    for (int i = 0; i < num_char; i++) {
        // Checks if the character is a '+' or '-'
        if (line[i] == '+' or line[i] == '-') {
            if (i != 0) {
                return false; // '+' or '-' only allowed as the first character
            } else if (i + 1 >= num_char) {
                return false; // Sign cannot be last character
            } else if (!is_num(line[i + 1]) && line[i + 1] != '.') {
                return false; // Sign must be followed by a number or a '.'
            }
        }
        
        // Checks if the character is a dot
        else if (line[i] == '.') {
            if (i + 1 >= num_char) {
                return false; // Dot cannot be last character
            } else if (!is_num(line[i + 1])) {
                return false; // Dot must be followed by a number
            }

            num_dots++; // Increment the dot counter
        }
        
        // Checks if the character is a valid number
        else if (!is_num(line[i])) {
            return false; // Invalid character in the string
        }
    }

    // If there is only 0 or 1 dots it returns true
    if (num_dots <= 1) {
        return true;
    }

    return false; // If there are more than one dots it returns false
}

// Converts a given string into an integer
// I am allowed to do this because I am not converting to a double for validation or arithmetic operations
double parse_number(const std::string &expression) {
    std::stringstream ss(expression);
    double d;
    ss >> d;
    return d;
}

// Converts a given string into an integer
int string_to_int(const std::string &input_string) {
    int result = 0; // Initializes the result variable

    for (std::size_t i = 0; i < input_string.length(); i++) {
        result = result * 10 + (input_string[i] - '0'); // Shifts left and adds digit
    }

    return result;
}

std::string add_string_doubles(const std::string &input_num) {
    int mode; // Initialize variable for mode (addition/subtraction)

    std::string num = input_num; // Initializes variable to hold num after sign is removed

    // Sets the mode of operation, and removes sign if a sign exists
    if (input_num[0] == '+') {
        mode = 1; // Sets mode to subtraction (a - b)
        num = num.substr(1); // Removes the sign character
    } else if (input_num[0] == '-') {
        mode = 0; // Sets mode to addition (-(a + b)) which is equivalent to (-a - b)
        num = num.substr(1); // Removes the sign character
    } else {
        mode = 1; // If no sign character then a positive value is inferred
    }

    // Finds the position of '.' if one exists
    int dot_pos = -1; // Initialize to sentinel value
    for (std::size_t i = 0; i < num.length(); i++) {
        // Sets the value of the dot position
        if (num[i] == '.') {
            dot_pos = i;
        }
    }

    // Initialize strings for the parts of the numbers
    std::string str_int_num;
    std::string str_frac_num;
    std::string str_int_num2 = "123";
    std::string str_frac_num2 = "456";

    // Splits the number into two strings which contain the integer and fractional parts respectively
    if (dot_pos != -1) {
        str_int_num = num.substr(0, dot_pos);
        str_frac_num = num.substr(dot_pos + 1);
    } else {
        str_int_num = num.substr(0);
        str_frac_num = "0";
    }
    
    // Finds the length of the longest fractional section
    std::size_t max_frac_len = 0;
    if (str_frac_num.length() < str_frac_num2.length()) {
        max_frac_len = str_frac_num2.length();
    } else {
        max_frac_len = str_frac_num.length();
    }

    // Normalizes the number of digits between the fractional section by padding with 0's
    while (str_frac_num.length() < max_frac_len) {
        str_frac_num += '0';
    }
    while (str_frac_num2.length() < max_frac_len) {
        str_frac_num2 += '0';
    }

    // Combines each numbers parts together
    std::string full_num = str_int_num + str_frac_num;
    std::string full_num2 = str_int_num2 + str_frac_num2;

    // Converts each number to an integer
    // This is allowed because I am not converting to a double and because I am
    // keeping the input and output as strings, and the only having separate
    // variables representing parts of the numbers as integers
    int num1 = string_to_int(full_num);
    int num2 = string_to_int(full_num2);

    // Performs addition or subtraction
    int result;
    if (mode == 0) {
        result = num1 + num2;
    } else {
        result = num1 - num2;
    }

    // Converts result to string to maintain input and output being strings
    std::string result_str = std::to_string(std::abs(result));

    // Adds "0." if the result is just decimal places
    // Else, it adds the '.' in the correct place
    std::string final_result;
    if (result_str.length() <= max_frac_len) {
        final_result = "0." + std::string(max_frac_len - result_str.length(), '0') + result_str;
    } else {
        final_result = result_str.substr(0, result_str.length() - max_frac_len) + "." + result_str.substr(result_str.length() - max_frac_len);
    }

    // Appends a "-" to the front if the result is negative
    // or, if the mode is 0 (-(a + b) or (-a -b))
    if (result < 0 || mode == 0) {
        final_result = "-" + final_result;
    }

    return final_result; // Returns the final result as a string
}