#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <string>
#include <stack>

const int NUM_TEST_CASES = 20;
const int TEST_NUMBER_WIDTH = 10;
const int TEST_STRING_WIDTH = 15;
const int OUTCOME_WIDTH = 20;

bool isValid(std::string s);

int main() {
    // Create a string for each test case
    std::string label, test_string;
    std::unordered_map<std::string, std::string> test_cases = {
        {"Test 1:", "()"},           // Simple valid case
        {"Test 2:", "{}[]()"},       // Mixed types, valid
        {"Test 3:", "(]"},           // Mismatched types
        {"Test 4:", "([)]"},         // Valid types but wrongly ordered
        {"Test 5:", "(((())))"},     // Nested, valid
        {"Test 6:", "("},            // Single, unmatched
        {"Test 7:", "){"},           // Invalid start with closing
        {"Test 8:", "(()){[()]}"},   // Complex, valid
        {"Test 9:", ""},             // Empty string
        {"Test 10:", "((()(())))"},  // More complex nested, valid
        {"Test 11:", "([{}])"},      // Mixed types nested, valid
        {"Test 12:", "(}"},          // Mismatched pair
        {"Test 13:", "([]{}"},       // Missing closing
        {"Test 14:", "([)]{}"},      // Mixed types with wrong order
        {"Test 15:", "((((((("},     // Multiple unmatched opening
        {"Test 16:", "))))))"},      // Multiple unmatched closing
        {"Test 17:", "([[[{{{{"},    // Multiple unmatched opening of different types
        {"Test 18:", "}]]]))"},      // Multiple unmatched closing of different types
        {"Test 19:", "(())(()"},     // Partially matched
        {"Test 20:", "[([])](){}"}   // Complex, valid with all types
    };

    // Access each test case and print the result
    for (const auto& pair : test_cases) {
        const std::string& label = pair.first;
        const std::string& test_string = pair.second;
        std::cout << std::left << std::setw(TEST_NUMBER_WIDTH) << label << std::setw(TEST_STRING_WIDTH)
            << test_string << std::setw(OUTCOME_WIDTH) << (isValid(test_string) ? "Valid" : "Invalid") << '\n';
    }

    return 0;
}

bool isValid(std::string s) {
    // Odd-length strings cannot be valid
    if (s.length() % 2 != 0) {
        return false;
    }

    // Map parentheses pairs
    std::unordered_map<char, char> parentheses = { {')', '('}, {']', '['}, {'}', '{'} };
    std::stack<char> characters;

    for (char current_char : s) {
        // Check if the current character is a closing parentheses
        if (parentheses.find(current_char) != parentheses.end()) {
            // If the stack is empty or the stack top doesn't match the current closing parentheses type, return false
            if (characters.empty() || characters.top() != parentheses[current_char]) {
                return false;
            }
            // Otherwise, the parentheses match and the top element can be popped
            characters.pop();
        }
        else {
            // If current_char is not in the map, then that means it is an open parentheses, and can be pushed onto the stack
            characters.push(current_char);
        }
    }
    return characters.empty();
}