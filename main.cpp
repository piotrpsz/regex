#include <iostream>
//#include <regex>
//#include <regex.h>

#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>
#include "pcregex.h"


int main() {

//    std::string pattern = "\\b(Wło\\w*)\\b";
    std::string pattern = "\\b(Piótr\\w*)\\b";
    std::string subject = "Włodzimierz Piótruś Pszczółkowski \nAbc Cde Piótruś Wxxx \n Piótr\n";
    Regex rgx{pattern.c_str(), subject.c_str(), subject.size()};
    if (auto rs = rgx.run(true); !rs.empty()) {
        for (auto item : rs) {
            auto text = subject.substr(item.offset, item.size);
            std::cout << '(' << item.offset << ", " << item.size << ") " << text << '\n';
        }
    }

    return 0;
/*
    int error_number;
    PCRE2_SIZE error_offset;

    char pattern_string[] = "\\b(Piotr)\\b";
    auto pattern = (PCRE2_SPTR) pattern_string;
    char subject_string[] = "Wodzimierz Piotr Pszczółkowski \nAbc Cde Piotr Wxxx \n";
    auto subject = (PCRE2_SPTR) subject_string;
    auto subject_length = strlen(subject_string);

    auto re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, 0, &error_number, &error_offset, nullptr);
    if (re == nullptr) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(error_number, buffer, 256);
        printf("PCRE2 compilation failed at offset %d: %s\n", (int) error_offset, buffer);
        exit(1);
    }

    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern_8(re, nullptr);

    int offset = 0;

    auto rc = pcre2_match(re, subject, subject_length, offset, 0, match_data, nullptr);
    if (rc < 0) {
        if (rc == PCRE2_ERROR_NOMATCH)
            std::cout << "not found\n";
        else
            std::cerr << "error\n";
        pcre2_match_data_free(match_data);
        pcre2_code_free(re);
        return 0;
    }

    auto ovector = pcre2_get_ovector_pointer(match_data);
    printf("Match succeeded at offset %d\n", (int) ovector[0]);
//    for (int i = 0; i < 128; i++)
//        printf("%c\n", int(ovector[i]));

    if (rc == 0) {
        printf("ovector was not big enough for all the captured substrings\n");
    }
    if (ovector[0] > ovector[1]) {
        std::cerr << "abandon\n";
        return 1;
    }
    std::cout << "rc: " << rc << '\n';
    for (int i = 0; i < rc; i++) {
        PCRE2_SPTR substring_start = subject + ovector[2 * i];
        size_t substring_length = ovector[2 * i + 1] - ovector[2 * i];
        printf("%2d: %.*s\n", i, (int) substring_length, (char *) substring_start);
    }

    uint32_t option_bits{};
    pcre2_pattern_info(re, PCRE2_INFO_ALLOPTIONS, &option_bits);
    auto utf8 = (option_bits & PCRE2_UTF) != 0;

    uint32_t newline{};
    bool crlf_is_newline = newline == PCRE2_NEWLINE_ANY ||
            newline == PCRE2_NEWLINE_CRLF ||
            newline == PCRE2_NEWLINE_ANYCRLF;

    for (;;) {
        uint32_t options{};
        PCRE2_SIZE start_offset = ovector[1];

        if (ovector[0] == ovector[1]) {
            if (ovector[0] == subject_length)
                break;
            options = PCRE2_NOTEMPTY_ATSTART | PCRE2_ANCHORED;
        }
        else {
            PCRE2_SIZE startchar = pcre2_get_startchar(match_data);
            if (start_offset <= startchar) {
                if (startchar >= subject_length)
                    break;
                start_offset = startchar + 1;
                if (utf8)
                    for (;start_offset < subject_length; start_offset++)
                        if ((subject[start_offset] & 0xc0) != 0x80)
                            break;
            }
        }

        // Run the next matching operation
        rc = pcre2_match(re, subject, subject_length, start_offset, options, match_data, nullptr);
        if (rc == PCRE2_ERROR_NOMATCH) {
            if (options == 0)
                break;
            ovector[1] = start_offset + 1;
            if (crlf_is_newline && start_offset < subject_length - 1 && subject[start_offset == '\r' && subject[start_offset + 1] == '\n'])
                ovector[1] += 1;
            else if (utf8) {
                while (ovector[1] < subject_length) {
                    if ((subject[ovector[1]] & 0xc0) != 0x80)
                        break;
                    ovector[1] += 1;
                }
            }
            continue;
        }

        if (rc < 0) {
            printf("Matching error %d\n", rc);
            pcre2_match_data_free(match_data);
            pcre2_code_free(re);
            return 1;
        }

        // Match success
        printf("\nMatch succeeded again at offset %d\n", (int)ovector[0]);

        for (int i = 0; i < rc; i++)
        {
            PCRE2_SPTR substring_start = subject + ovector[2*i];
            size_t substring_length = ovector[2*i+1] - ovector[2*i];
            printf("%2d: %.*s\n", i, (int)substring_length, (char *)substring_start);
        }

//        if (namecount == 0) printf("No named substrings\n"); else
//        {
//            PCRE2_SPTR tabptr = name_table;
//            printf("Named substrings\n");
//            for (i = 0; i < namecount; i++)
//            {
//                int n = (tabptr[0] << 8) | tabptr[1];
//                printf("(%d) %*s: %.*s\n", n, name_entry_size - 3, tabptr + 2,
//                       (int)(ovector[2*n+1] - ovector[2*n]), subject + ovector[2*n]);
//                tabptr += name_entry_size;
//            }
//        }
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);
    return 0;
}
*/

//    auto flags = std::regex::ECMAScript;
//    std::string expression = R"(.*(\n).*\b(Piotr)\b)";
//    auto rgx = std::regex(expression, flags);
//
//    {
//        std::string text = "Wodzimierz Piotr Pszczółkowski\nAbc Cde Piotr xxxx \n";
//        std::smatch smatch;
//        if (std::regex_search(text, smatch, rgx))
//            std::cout << "ok\n";
//    }
/*
    {
        char raw[] = "Wodzimierz Piotr Pszczółkowski";
        char pattern[] = R"(\b(Piotr)\b)";
        regex_t rgt;

        if (auto rc = regcomp(&rgt, "\\b(Piotr)\\b\\", 0); rc != 0) {
            std::cerr << "err1\n";
            return 1;
        }
//        if ((rc = regexec(&preg, string, nmatch, pmatch, 0)) != 0) {

        size_t     nmatch = 1025;
        regmatch_t pmatch[1024];
        if (auto rc = regexec(&rgt, "Wodzimierz Piotr Pszczolkowski", nmatch, pmatch, 0); rc != 0) {
            char msgbuf[1024];
            regerror(rc, &rgt, msgbuf, 1024);
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            return 2;
        }
        std::cout << pmatch[0].rm_so << ", " << pmatch[0].rm_eo << '\n';
    }
*/
}