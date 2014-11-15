#include <stdexcept>
#include "json_lexer.hpp"

namespace singularity {
    using token = json_lexer::token;

    token json_lexer::parse(cursor &first, cursor &last) {
        token t;
        while (token::space == (t = json_lexer::parse_value(last))) {
            first = ++last;
        }
        if (t != token::number) ++last;
        return t;
    }

    token json_lexer::parse_value(cursor &cursor) {
        switch (*cursor) {
            case 'n': // null
                return json_lexer::parse_literal(cursor, "ull");

            case 'f': // false
                return json_lexer::parse_literal(cursor, "alse");

            case 't': // true
                return json_lexer::parse_literal(cursor, "rue");

            case '"': // string
                return json_lexer::parse_string(cursor);

            case '[':
            case ']':
            case '{':
            case '}':
            case ':':
            case ',':
                return static_cast<token>(*cursor);

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
                return json_lexer::parse_number(cursor);

            case 0x09:
            case 0x0A:
            case 0x0D:
            case 0x20:
                return token::space;

            default:
                throw std::invalid_argument(std::string{"Unexpected token: "} + *cursor);
        }
    }

    token json_lexer::parse_literal(cursor &cursor, const std::string &expected) {
        token t = static_cast<token>(*cursor);
        for (auto c : expected) {
            if (c != *++cursor) {
                throw std::invalid_argument{std::string{"Expect token: "} + c + ", but got: " + *cursor};
            }
        }
        return t;
    }

    token json_lexer::parse_number(cursor &cursor) {
        while (true) {
            switch (*++cursor) {
                case '+':
                case '-':
                case '.':
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
                case 'E':
                case 'e':
                    continue;
            }
            break;
        }
        return token::number;
    }

    token json_lexer::parse_string(cursor &cursor) {
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
        return token::string;
    }
}
