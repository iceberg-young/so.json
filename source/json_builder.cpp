#include <list>
#include <sstream>
#include <stdexcept>
#include "json_builder.hpp"

namespace singularity {
    using token = json_lexer::token;

    json json_builder::build(const cursor &text) {
        auto first = text;
        auto last = text;
        auto token = json_lexer::parse(first, last);
        json root = json_builder::create(token, first, last);
        switch (root.type()) {
            case json::content_type::array:
                json_builder::fill_array(root, first, last);
                break;

            case json::content_type::object:
                json_builder::fill_object(root, first, last);
                break;
        }
        return root;
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
        for (++now; now != last; ++now) {
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

    void json_builder::fill_array(json &array, const cursor &first, const cursor &last) {
        // TODO
    }

    void json_builder::fill_object(json &object, const cursor &first, const cursor &last) {
        // TODO
    }
}
