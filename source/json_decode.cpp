#include <cmath>
#include "json_null.hpp"
#include "json_boolean.hpp"
#include "json_number.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include "json_object.hpp"
#include "json_decode.hpp"

namespace singularity {
    json json_decode::run() {
        --this->iterator;
        return json{this->cascade(this->next())};
    };

    json::data_t json_decode::cascade(token t) {
        auto node = this->factory(t);
        switch (node->type) {
            case json::content_type::array:
                this->fill_children(node->to_array());
                break;

            case json::content_type::object:
                this->fill_children(node->to_object());
                break;
        }
        return node;
    }

    json::data_t json_decode::factory(token t) {
        switch (t) {
            case token::null:
                this->pass_literals("ull");
                return json_null::solo;

            case token::boolean_false:
                this->pass_literals("alse");
                return json_false::solo;

            case token::boolean_true:
                this->pass_literals("rue");
                return json_true::solo;

            case token::number:
                return json::data_t{new json_number{this->parse_number()}};

            case token::string:
                return json::data_t{new json_string{this->parse_string()}};

            case token::array_begin:
                return json::data_t{new json_array};

            case token::object_begin:
                return json::data_t{new json_object};

            default: {
                throw json_decode_error{this->dump() + " invalid node type."};
            }
        }
    }

    void json_decode::fill_children(json::array_t& array) {
        array.reserve(8);
        token t;
        bool s = true;
        while (token::array_end != (t = this->next())) {
            if (this->separator(t, s)) {continue;}
            array.emplace_back(this->cascade(t));
        }
    }

    void json_decode::fill_children(json::object_t& object) {
        token t;
        bool s = true;
        while (token::object_end != (t = this->next())) {
            if (this->separator(t, s)) {continue;}

            // name
            if (t != token::string) {
                throw json_decode_error{this->dump() + " name (string) is expected."};
            }
            auto name = this->parse_string();

            // separator (:)
            if (this->next() != token::name_separator) {
                throw json_decode_error{this->dump() + " name separator (:) is expected."};
            }

            // value
            object.emplace(std::move(name), this->cascade(this->next()));
        }
    }

    void json_decode::pass_literals(const std::string& expected) {
        for (auto c : expected) {
            if (c != *++this->iterator) {
                throw json_decode_error{this->dump() + " expected: " + c};
            }
        }
    }

    constexpr int DECIMAL_SCALE = 10;

    double json_decode::parse_number() {
        // sign
        int base_sign = this->parse_sign();
        // integer
        double base = 0;
        while (std::isdigit(*this->iterator)) {
            base = base * DECIMAL_SCALE + (*this->iterator++ - '0');
        }
        // fraction
        int frac = 0;
        if (*this->iterator == '.') {
            while (std::isdigit(*++this->iterator)) {
                base = base * DECIMAL_SCALE + (*this->iterator - '0');
                ++frac;
            }
        }
        base *= base_sign;
        // exponent
        int expo = 0;
        if (*this->iterator == 'e') {
            ++this->iterator;
            int expo_sign = this->parse_sign();
            while (std::isdigit(*this->iterator)) {
                expo = expo * DECIMAL_SCALE + (*this->iterator++ - '0');
            }
            expo *= expo_sign;
        }
        --this->iterator;
        return base * std::pow(DECIMAL_SCALE, expo - frac);
    }

    int json_decode::parse_sign() {
        switch (*this->iterator) {
            case '-':
                ++this->iterator;
                return -1;

            case '+':
                ++this->iterator;
            default:
                return +1;
        }
    }

    std::string json_decode::parse_string() {
        std::string target;
        target.reserve(32);
        while (*++this->iterator != '"') {
            char c = *this->iterator;
            if (c == '\\') {
                switch (c = *++this->iterator) {
                    case 'b':
                        c = '\b';
                        break;

                    case 'f':
                        c = '\f';
                        break;

                    case 'n':
                        c = '\n';
                        break;

                    case 'r':
                        c = '\r';
                        break;

                    case 't':
                        c = '\t';
                        break;

                    case 'u':
                        this->iterator += 4;
                        // TODO
                        continue;
                }
            }
            target += c;
        }
        return target;
    }

    std::string json_decode::dump() {
        auto c = std::to_string(int(*this->iterator));
        auto d = std::to_string(this->iterator - this->begin);
        return '[' + c + '@' + d + ']';
    }

    json_decode::token json_decode::next() {
        while (std::isspace(*++this->iterator)) {}
        switch (char c = *this->iterator) {
            case 'n': // null
            case 'f': // false
            case 't': // true
            case '-': // number
            case '"': // string
            case '[': // array begin
            case ']': // array end
            case '{': // object begin
            case '}': // object end
            case ':': // name separator
            case ',': // value separator
                return static_cast<token>(c);

            default:
                if (std::isdigit(c)) {
                    return token::number;
                }
                else {
                    throw json_decode_error{this->dump() + " invalid literal."};
                }
        }
    }

    bool json_decode::separator(token t, bool& s) {
        if (!s and t != token::value_separator) {
            throw json_decode_error{this->dump() + " value separator (,) is expected."};
        }
        return s = !s;
    }
}
