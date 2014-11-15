#include <sstream>
#include <stdexcept>
#include "json_builder.hpp"

namespace singularity {
    using token = json_lexer::token;

    json json_builder::build(const cursor &text) {
        auto first = text;
        auto last = text;
        auto token = json_lexer::parse(first, last);
        return json_builder::cascade(token, first, last);
    }

    json json_builder::cascade(json_lexer::token token, cursor &first, cursor &last) {
        json node = json_builder::create(token, first, last);
        first = last;
        switch (node.type()) {
            case json::content_type::array:
                json_builder::fill_array(node, first, last);
                break;

            case json::content_type::object:
                json_builder::fill_object(node, first, last);
                break;
        }
        return node;
    }

    json json_builder::create(token t, const cursor &first, const cursor &last) {
        switch (t) {
            case token::null:
                return json{};

            case token::boolean_false:
                return json{false};

            case token::boolean_true:
                return json{true};

            case token::number:
                return json{std::stod(std::string{first, last})};

            case token::string:
                return json{json_builder::unescape(first, last)};

            case token::array_begin:
                return json{json::content_type::array};

            case token::object_begin:
                return json{json::content_type::object};

            default:
                throw std::logic_error{std::string{"Cannot create node from token: "} + static_cast<char>(t)};
        }
    }

    std::string json_builder::unescape(const cursor &first, const cursor &last) {
        std::stringstream ss;
        auto now = first;
        auto end = last;
        for (++now, --end; now != end; ++now) {
            char c = *now;
            if (c == '\\') {
                switch (c = *++now) {
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
                        // TODO
                        break;
                }
            }
            ss << c;
        }
        return ss.str();
    }

    void json_builder::fill_array(json &array, cursor &first, cursor &last) {
        token t;
        bool separated = true;
        json::array_t &a = array;
        while (token::array_end != (t = json_lexer::parse(first, last))) {
            if (json_builder::pass_comma(t, separated)) {
                a.push_back(json_builder::cascade(t, first, last));
            }
            else first = last;
        }
    }

    void json_builder::fill_object(json &object, cursor &first, cursor &last) {
        token t;
        bool separated = true;
        json::object_t &o = object;
        while (token::object_end != (t = json_lexer::parse(first, last))) {
            if (json_builder::pass_comma(t, separated)) {
                // key
                json_builder::assert(token::string, t);
                auto key = json_builder::unescape(first, last);

                // colon (:)
                auto ts = json_lexer::parse(first, last);
                json_builder::assert(token::name_separator, ts);

                // value
                auto tv = json_lexer::parse(first, last);
                auto value = json_builder::cascade(tv, first, last);
                o.insert(std::make_pair(key, value));
            }
            else first = last;
        }
    }

    bool json_builder::pass_comma(token t, bool &separated) {
        if (!separated and t != token::value_separator) {
            throw std::logic_error{"Value separator (,) is expected."};
        }
        return !(separated = !separated);
    }

    void json_builder::assert(token expected, token real) {
        if (expected != real) {
            throw std::logic_error{
              std::string{"Expected: "} + static_cast<char>(expected)
                + ", but got: " + static_cast<char>(real)
            };
        }
    }
}
