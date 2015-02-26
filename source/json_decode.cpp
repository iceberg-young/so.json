#include <cmath>
#include "json_null.hpp"
#include "json_boolean.hpp"
#include "json_number.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include "json_object.hpp"
#include "json_decode.hpp"
#include "unicode.hpp"

namespace so {
    json json_decode::run(json::literal_t& begin) {
        json_decode decoder{begin};
        return json{decoder.cascade(decoder.next())};
    }

    std::string json_decode::dump() {
        auto c = std::to_string(int(*this->iterator));
        auto d = std::to_string(this->iterator - this->begin);
        return '[' + c + '@' + d + ']';
    }

    json::data_t json_decode::cascade(token t) {
        auto node = this->factory(t);
        switch (node->type) {
            case json::content_type::array: {
                this->fill_children(json_array::get(node));
                break;
            }
            case json::content_type::object: {
                this->fill_children(json_object::get(node));
                break;
            }
        }
        return node;
    }

    json::data_t json_decode::factory(token t) {
        switch (t) {
            case token::null: {
                this->pass_literals("ull");
                return json_null::solo;
            }
            case token::boolean_false: {
                this->pass_literals("alse");
                return json_false::solo;
            }
            case token::boolean_true: {
                this->pass_literals("rue");
                return json_true::solo;
            }
            case token::number: {
                return json::data_t{new json_number{this->parse_number()}};
            }
            case token::string: {
                return json::data_t{new json_string{this->parse_string()}};
            }
            case token::array_begin: {
                return json::data_t{new json_array};
            }
            case token::object_begin: {
                return json::data_t{new json_object};
            }
            default: {
                throw json_decode_error{this->dump() + " invalid node type."};
            }
        }
    }

    void json_decode::fill_children(json::array_t& array) {
        bool initial = true;
        token child;
        while (this->next(token::array_end, initial, child)) {
            array.emplace_back(this->cascade(child));
        }
    }

    void json_decode::fill_children(json::object_t& object) {
        bool initial = true;
        token child;
        while (this->next(token::object_end, initial, child)) {
            // name
            if (child != token::string) {
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

    char json_decode::forward() {
        char c = *++this->iterator;
        if (!c) {
            throw json_decode_error{this->dump() + " unexpected end."};
        }
        return c;
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

            default: {
                if (std::isdigit(c)) {
                    return token::number;
                }
                else {
                    throw json_decode_error{this->dump() + " invalid literal."};
                }
            }
        }
    }

    bool json_decode::next(token end, bool& initial, token& child) {
        child = this->next();
        if (initial) {
            initial = false;
            return end != child;
        }
        if (child == end) return false;
        if (child != token::value_separator) {
            throw json_decode_error{this->dump() + " value separator (,) is expected."};
        }
        if ((child = this->next()) == end) {
            throw json_decode_error{this->dump() + " redundant value separator (,)."};
        }
        return true;
    }

    void json_decode::pass_literals(const std::string& expected) {
        for (auto c : expected) {
            if (c != *++this->iterator) {
                throw json_decode_error{this->dump() + " expected: " + c};
            }
        }
    }

    double json_decode::parse_number() {
        const char* begin = &*this->iterator;
        char* end = nullptr;
        double value = strtod(begin, &end);
        if (end == begin) {
            throw json_decode_error{this->dump() + " invalid number."};
        }
        this->iterator += end - begin - 1;
        return value;
    }

    std::string json_decode::parse_string() {
        std::string target;
        target.reserve(32); //< FIXME: HACK
        char c;
        while ((c = this->forward()) != '"') {
            if (c == '\\') {
                switch (c = this->forward()) {
                    case 'b': {
                        c = '\b';
                        break;
                    }
                    case 'f': {
                        c = '\f';
                        break;
                    }
                    case 'n': {
                        c = '\n';
                        break;
                    }
                    case 'r': {
                        c = '\r';
                        break;
                    }
                    case 't': {
                        c = '\t';
                        break;
                    }
                    case 'u': {
                        target += utf8(escaped(--this->iterator));
                        --this->iterator;
                        continue;
                    }
                }
            }
            target += c;
        }
        return target;
    }
}
