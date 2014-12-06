#include "json_data.hpp"
#include "json_decode.hpp"

namespace singularity {
    namespace json_uh {
        double parse_number(cursor& i);

        // Cursor information for debug.
        std::string dump_cursor(const cursor& i) {
            std::string dump;
            dump += '[';
            dump += *i;
            dump += ':';
            dump += int(*i);
            dump += ']';
            return dump;
        }

        // Guess type of next node.
        token next(cursor& i) {
            while (std::isspace(*i)) {++i;}
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
                    if (std::isdigit(c)) {
                        return token::number;
                    }
                    else {
                        throw json_decode_error{dump_cursor(i) + " invalid literal."};
                    }
            }
        }

        // Move cursor over the expected literals.
        void pass_literals(cursor& i, const std::string& expected) {
            for (auto c : expected) {
                if (c != *++i) {
                    throw json_decode_error{dump_cursor(i) + " expected: " + c};
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
                    return json::pointer_t{new json{json_data::un_escape(i)}};

                case token::array_begin:
                    return json::pointer_t{new json{json::content_type::array}};

                case token::object_begin:
                    return json::pointer_t{new json{json::content_type::object}};

                default: {
                    throw json_decode_error{dump_cursor(i) + " invalid node type."};
                }
            }
        }

        // Check value separator take post.
        bool separated(token t, bool& s, const cursor& i) {
            if (!s and t != token::value_separator) {
                throw json_decode_error{dump_cursor(i) + " value separator (,) is expected."};
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
                        throw json_decode_error{dump_cursor(i) + " name (string) is expected."};
                    }
                    auto name = json_data::un_escape(i);

                    // separator (:)
                    auto ts = next(++i);
                    if (ts != token::name_separator) {
                        throw json_decode_error{dump_cursor(i) + " name separator (:) is expected."};
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

        double parse_number(cursor& i) {
            cursor b = i;
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
    }
}
