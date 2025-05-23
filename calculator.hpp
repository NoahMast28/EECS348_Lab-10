#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>

// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression);

bool is_valid_double(const std::string &line);
bool is_num(char c);
std::string add_string_doubles(const std::string &input_num);
long long string_to_long(const std::string &input_string);

#endif // __CALCULATOR_HPP
