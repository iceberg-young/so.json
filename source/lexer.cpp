#include <stdexcept>
#include "lexer.hpp"

namespace singularity {

    void lexer::parse(const std::string &text) {
        cursor begin{text.begin(), text.end()};
        do {
            (this->*parser)(begin);
        }
        while (!begin.is_end());
        this->callback(token::done, begin, begin);
    }

    void lexer::parse_value(cursor &begin) {
        switch (*begin) {
            case 'n': // null
                this->parse_literal(begin, "ull");
                break;

            case 'f': // false
                this->parse_literal(begin, "alse");
                break;

            case 't': // true
                this->parse_literal(begin, "rue");
                break;

            case '"': // string
                this->parse_string(begin);
                break;

            case '[':
            case ']':
            case '{':
            case '}':
            case ':':
            case ',':
                this->callback(static_cast<token>(*begin), begin, begin);
                break;

            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                this->parse_number(begin);
                break;

            case 0x09:
            case 0x0A:
            case 0x0D:
            case 0x20:
                break; // skip

            default:
                throw std::invalid_argument(std::string{"Unexpected token: "} + *begin);
        }
    }

    void lexer::parse_literal(cursor &cursor, const std::string &expected) {
        auto begin = cursor;
        for (auto c : expected) {
            if (c != *++cursor) {
                throw std::invalid_argument{std::string{"Expect token: "} + c + ", but got: " + *cursor};
            }
        }
        this->callback(static_cast<token>(*begin), begin, cursor);
    }

    void lexer::parse_number(cursor &cursor) {
        auto begin = cursor;
        while (true) {
            switch (*++cursor) {
                case 'e':
                case 'E':
                case '.':
                case '+':
                case '-':
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    continue;
            }
            break;
        }
        this->callback(token::number, begin, cursor);
    }

    void lexer::parse_string(cursor &cursor) {
        auto begin = cursor;
        bool more = true;
        while (more) {
            switch (*++cursor) {
                case '"':
                    more = false;
                    break;

                case '\\':
                    ++cursor;
                    break;
            }
        }
        this->callback(token::string, begin, cursor);
    }
}
