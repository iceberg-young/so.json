#include "json_data.hpp"
#include "json_decode.hpp"

namespace singularity {
    json::pointer_t json_decode::cascade(token t) {
        json::pointer_t node = this->create(t);
        switch (node->type()) {
            case json::content_type::array:
                this->fill_array(node);
                break;

            case json::content_type::object:
                this->fill_object(node);
                break;
        }
        return node;
    }

    json::pointer_t json_decode::create(token t) {
        switch (t) {
            case token::null:
                this->pass_literals("ull");
                return json::pointer_t{new json{}};

            case token::boolean_false:
                this->pass_literals("alse");
                return json::pointer_t{new json{false}};

            case token::boolean_true:
                this->pass_literals("rue");
                return json::pointer_t{new json{true}};

            case token::number:
                return json::pointer_t{new json{this->parse_number()}};

            case token::string:
                return json::pointer_t{new json{json_data::un_escape(this->iterator)}};

            case token::array_begin:
                return json::pointer_t{new json{json::content_type::array}};

            case token::object_begin:
                return json::pointer_t{new json{json::content_type::object}};

            default: {
                throw json_decode_error{this->dump() + " invalid node type."};
            }
        }
    }

    void json_decode::fill_array(json::pointer_t& array) {
        token t;
        bool s = true;
        json::array_t& a = array->as_array();
        while (token::array_end != (t = this->next())) {
            if (this->separated(t, s)) {
                a.emplace_back(this->cascade(t));
            }
        }
    }

    void json_decode::fill_object(json::pointer_t& object) {
        token tn;
        bool s = true;
        json::object_t& o = object->as_object();
        while (token::object_end != (tn = this->next())) {
            if (separated(tn, s)) {
                // name
                if (tn != token::string) {
                    throw json_decode_error{this->dump() + " name (string) is expected."};
                }
                auto name = json_data::un_escape(this->iterator);

                // separator (:)
                auto ts = this->next();
                if (ts != token::name_separator) {
                    throw json_decode_error{this->dump() + " name separator (:) is expected."};
                }

                // value
                auto tv = this->next();
                auto value = this->cascade(tv);
                o.insert(std::make_pair(name, value));
            }
        }
    }

    void json_decode::pass_literals(const std::string& expected) {
        for (auto c : expected) {
            if (c != *++this->iterator) {
                throw json_decode_error{this->dump() + " expected: " + c};
            }
        }
    }

    double json_decode::parse_number() {
        iterator_t head = this->iterator;
        // sign
        if (*this->iterator == '-') {++this->iterator;}
        // integer
        while (std::isdigit(*this->iterator)) {++this->iterator;}
        // fraction
        if (*this->iterator == '.') {
            while (std::isdigit(*++this->iterator)) {}
        }
        // exponent
        if (*this->iterator == 'e') {
            char c = *++this->iterator;
            if (c == '-' or c == '+') {++this->iterator;}
            while (std::isdigit(*this->iterator)) {++this->iterator;}
        }
        return std::stod(std::string{head, this->iterator--});
    }

    std::string json_decode::dump() {
        auto c = std::to_string(int(*this->iterator));
        auto d = std::to_string(this->iterator - this->begin);
        return '[' + c + ':' + '@' + d + ']';
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

    bool json_decode::separated(token t, bool& s) {
        if (!s and t != token::value_separator) {
            throw json_decode_error{this->dump() + " value separator (,) is expected."};
        }
        return !(s = !s);
    }
}
