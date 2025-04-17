#include <iostream>
#include <fstream>
#include <string>

#include "calculator.hpp"

int main(int argc, char *argv[]) {
    // Tells the user to add a filename when running the file
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]); // Opens the file

    std::string line;

    while (std::getline(file, line)) { // Iterates over each line of the file
        if (is_valid_double(line)) { // Checks if the line contains a valid double number
            std::string result = add_string_doubles(line); // Adds the double with the double specified in the lab instructions
            std::cout << line << " + (-123.456) = " << result << std::endl; // Prints the result
        } else {
            std::cout << line << " is not a valid double" << std::endl // Informs the user that the line did not contain a vaild double
        }
    }

    file.close(); // Closes the file

    return 0;
}
