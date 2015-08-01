#include "json_null.hpp"
#include "json_boolean.hpp"
#include "json_number.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include "json_object.hpp"
#include "json_parser.hpp"
#include "unicode.hpp"

namespace so {
    enum class json_token :
      char {
        null = 'n',
        boolean_false = 'f',
        boolean_true = 't',
        number = '-',
        string = '"',
        array_begin = '[',
        array_end = ']',
        object_begin = '{',
        object_end = '}',
        name_separator = ':',
        value_separator = ',',
    };

    json json_parser::run(literal_t& begin) {
        json_parser parser{begin};
        return json{parser.cascade(parser.next())};
    }

    std::string json_parser::location() {
        auto c = std::to_string(int(*this->iterator));
        auto d = std::to_string(this->iterator - this->begin);
        return '[' + c + '@' + d + ']';
    }

    json::data_t json_parser::cascade(json_token t) {
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
            default: {
                // Nothing to do.
                break;
            }
        }
        return node;
    }

    json::data_t json_parser::factory(json_token t) {
        switch (t) {
            case json_token::null: {
                this->pass_literals("ull");
                return json_null::solo;
            }
            case json_token::boolean_false: {
                this->pass_literals("alse");
                return json_false::solo;
            }
            case json_token::boolean_true: {
                this->pass_literals("rue");
                return json_true::solo;
            }
            case json_token::number: {
                return std::make_shared<json_number>(this->parse_number());
            }
            case json_token::string: {
                return std::make_shared<json_string>(this->parse_string());
            }
            case json_token::array_begin: {
                return std::make_shared<json_array>();
            }
            case json_token::object_begin: {
                return std::make_shared<json_object>();
            }
            default: {
                throw json_parse_error{
                  this->location() + " invalid node type."
                };
            }
        }
    }

    void json_parser::fill_children(json::array_t& array) {
        json_token child = this->next();
        while (child != json_token::array_end) {
            array.emplace_back(this->cascade(child));
            child = this->next_peer(json_token::array_end);
        }
    }

    void json_parser::fill_children(json::object_t& object) {
        json_token child = this->next();
        while (child != json_token::object_end) {
            // name
            if (child != json_token::string) {
                throw json_parse_error{
                  this->location() + " name (string) is expected."
                };
            }
            auto name = this->parse_string();

            // separator (:)
            if (this->next() != json_token::name_separator) {
                throw json_parse_error{
                  this->location() + " name separator (:) is expected."
                };
            }

            // value
            object.emplace(std::move(name), this->cascade(this->next()));

            // more
            child = this->next_peer(json_token::object_end);
        }
    }

    namespace {
        const std::string whitespaces{"\t\n\r "};
        const std::string token_leads{"nft-\"[]{}:,"};
    }

    json_token json_parser::next() {
        char c;
        while (whitespaces.find(c = *this->iterator) != std::string::npos) {
            ++this->iterator;
        }
        json_token t;
        auto pos = token_leads.find(c);
        if (pos != std::string::npos) {
            t = static_cast<json_token>(c);
        }
        else if (c >= '0' and c <= '9') {
            t = json_token::number;
        }
        else {
            throw json_parse_error{
              this->location() + " invalid literal."
            };
        }
        ++this->iterator;
        return t;
    }

    json_token json_parser::next_peer(json_token end) {
        json_token child = this->next();
        if (child != end) {
            if (child != json_token::value_separator) {
                throw json_parse_error{
                  this->location() + " value separator (,) is expected."
                };
            }
            child = this->next();
            if (child == end) {
                throw json_parse_error{
                  this->location() + " redundant value separator (,)."
                };
            }
        }
        return child;
    }

    void json_parser::pass_literals(const std::string& expected) {
        for (char c : expected) {
            if (c != *this->iterator++) {
                throw json_parse_error{this->location() + " expected: " + c};
            }
        }
    }

    double json_parser::parse_number() {
        const char* begin = &*--this->iterator;
        char* end = nullptr;
        double value = strtod(begin, &end);
        if (end == begin) {
            throw json_parse_error{this->location() + " invalid number."};
        }
        this->iterator += end - begin;
        return value;
    }

    std::string json_parser::parse_string() {
        std::string target;
        target.reserve(32); //< FIXME: HACK
        char c;
        while (this->pick(c) != '"') {
            if (c == '\\') {
                ++this->iterator;
                if (this->pick(c) == 'u') {
                    target += utf8(unicode::escaped(--this->iterator));
                    continue;
                }
                auto pos = json_data::esc_label.find(c);
                if (pos != std::string::npos) {
                    c = json_data::esc_value[pos];
                }
            }
            target += c;
            ++this->iterator;
        }
        ++this->iterator;
        return target;
    }

    char json_parser::pick(char& c) {
        if (not (c = *this->iterator)) {
            throw json_parse_error{this->location() + " unexpected end."};
        }
        return c;
    }
}
