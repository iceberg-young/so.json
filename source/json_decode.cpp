#include <list>
#include <locale>
#include <sstream>
#include "json_data.hpp"
#include "json_decode.hpp"

namespace singularity {
    using namespace json_uh;

    json::pointer_t cascade(token t, cursor& i);

    double parse_number(cursor& i);

    std::string parse_string(cursor& i);

    const std::locale c_locale{"C"};

    // Cursor information for debug.
    std::stringstream& operator<<(std::stringstream& ss, const cursor& i) {
        ss << '[' << i.position() << ':' << *i << '(' << int(*i) << ")]";
        return ss;
    }

    // Guess type of next node.
    token next(cursor& i) {
        while (std::isspace(*i, c_locale)) {++i;}
        switch (char c = *i) {
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
                if (std::isdigit(c, c_locale)) {
                    return token::number;
                }
                else {
                    std::stringstream ss;
                    ss << i << " invalid value.";
                    throw json_decode_error{ss.str()};
                }
        }
    }

    // Move cursor over the expected literals.
    void pass_literals(cursor& i, const std::string& expected) {
        for (auto c : expected) {
            if (c != *++i) {
                std::stringstream ss;
                ss << i << " expected: " << c;
                throw json_decode_error{ss.str()};
            }
        }
    }

    // Create a node start from the cursor.
    json::pointer_t create(token t, cursor& i) {
        switch (t) {
            case token::null:
                pass_literals(i, "ull");
                return json::pointer_t{new json{}};

            case token::boolean_false:
                pass_literals(i, "alse");
                return json::pointer_t{new json{false}};

            case token::boolean_true:
                pass_literals(i, "rue");
                return json::pointer_t{new json{true}};

            case token::number:
                return json::pointer_t{new json{parse_number(i)}};

            case token::string:
                return json::pointer_t{new json{parse_string(i)}};

            case token::array_begin:
                return json::pointer_t{new json{json::content_type::array}};

            case token::object_begin:
                return json::pointer_t{new json{json::content_type::object}};

            default: {
                std::stringstream ss;
                ss << i << " invalid node type.";
                throw std::invalid_argument{ss.str()};
            }
        }
    }

    // Check value separator take post.
    bool separated(token t, bool& s, const cursor& i) {
        if (!s and t != token::value_separator) {
            std::stringstream ss;
            ss << i << " value separator (,) is expected.";
            throw json_decode_error{ss.str()};
        }
        return !(s = !s);
    }

    void fill_array(json::pointer_t& array, cursor& i) {
        token t;
        bool s = true;
        json::array_t& a = array->as_array();
        while (token::array_end != (t = next(++i))) {
            if (separated(t, s, i)) {
                a.emplace_back(cascade(t, i));
            }
        }
    }

    void fill_object(json::pointer_t& object, cursor& i) {
        token tn;
        bool s = true;
        json::object_t& o = object->as_object();
        while (token::object_end != (tn = next(++i))) {
            if (separated(tn, s, i)) {
                // name
                if (tn != token::string) {
                    std::stringstream ss;
                    ss << i << " name (string) is expected.";
                    throw json_decode_error{ss.str()};
                }
                auto name = parse_string(i);

                // separator (:)
                auto ts = next(++i);
                if (ts != token::name_separator) {
                    std::stringstream ss;
                    ss << i << " name separator (:) is expected.";
                    throw json_decode_error{ss.str()};
                }

                // value
                auto tv = next(++i);
                auto value = cascade(tv, i);
                o.insert(std::make_pair(name, value));
            }
        }
    }

    // Cascade create node.
    json::pointer_t cascade(token t, cursor& i) {
        json::pointer_t node = create(t, i);
        switch (node->type()) {
            case json::content_type::array:
                fill_array(node, i);
                break;

            case json::content_type::object:
                fill_object(node, i);
                break;
        }
        return node;
    }

    json::pointer_t json_uh::decode(const cursor& c) {
        auto i = c;
        auto token = next(i);
        return cascade(token, i);
    }

    double parse_number(cursor& i) {
        sci_t b = i;
        // sign
        if (*i == '-') {++i;}
        // integer
        while (std::isdigit(*i)) {++i;}
        // fraction
        if (*i == '.') {
            while (std::isdigit(*++i)) {}
        }
        // exponent
        if (*i == 'e') {
            char c = *++i;
            if (c == '-' or c == '+') {++i;}
            while (std::isdigit(*i)) {++i;}
        }
        return std::stod(std::string{b, i--});
    }

    std::string parse_string(cursor& i) {
        std::stringstream ss;
        while (*++i != '"') {
            char c = *i;
            if (c == '\\') {
                switch (c = *++i) {
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
                        i += 4;
                        // TODO
                        continue;
                }
            }
            ss << c;
        }
        return ss.str();
    }
}
