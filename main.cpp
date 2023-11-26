#include <iostream>
//#include <regex>
//#include <regex.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>
#include "pcregex.h"


int main() {
    std::string pattern = "\\b(Piótr\\w*)\\b";
    std::string subject = "Włodzimierz Piótr Pszczółkowski \nAbc Cde Piótruś Wxxx \n Piótr\n";
    Regex rgx{pattern.c_str(), subject.c_str(), subject.size()};
    if (auto rs = rgx.run(true); !rs.empty()) {
        for (auto item : rs) {
            auto text = subject.substr(item.offset, item.size);
            std::cout << '(' << item.offset << ", " << item.size << ") " << text << '\n';
        }
    }

    return 0;
}