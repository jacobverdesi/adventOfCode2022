//
// Created by jacob on 12/23/2022.
//

#include "tokenizer.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

vector<std::string> tokenize(
        const std::string str,
        const std::regex re)
{
    std::sregex_token_iterator it{ str.begin(),
                                   str.end(), re, -1 };
    std::vector<std::string> tokenized{ it, {} };

    // Additional check to remove empty strings
    tokenized.erase(
            std::remove_if(tokenized.begin(),
                           tokenized.end(),
                           [](std::string const& s) {
                               return s.size() == 0;
                           }),
            tokenized.end());

    return tokenized;
}

// Driver Code
int main1()
{
    const std::string str = "Break string a,spaces,and,commas";
    const std::regex re(R"([\s|,]+)");

    // Function Call
    const std::vector<std::string> tokenized =
            tokenize(str, re);

    for (std::string token : tokenized)
        std::cout << token << std::endl;
    return 0;
}