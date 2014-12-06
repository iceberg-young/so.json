#include "json_number.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include "json_object.hpp"
#include "json_decode.hpp"

namespace singularity {
    void json_data::escape(const std::string& source, std::string& target) {
        for (auto c : source) {
            if (c < 0x20) {
                target += '\\';
                switch (c) {
                    case '\b':
                        target += 'b';
                        break;

                    case '\f':
                        target += 'f';
                        break;

                    case '\n':
                        target += 'n';
                        break;

                    case '\r':
                        target += 'r';
                        break;

                    case '\t':
                        target += 't';
                        break;

                    default: {
                        char buffer[6];
                        std::sprintf(buffer, "u%04X", c);
                        target += buffer;
                        break;
                    }
                }
            }
            else {
                if (c == '"' or c == '\\') {
                    target += '\\';
                }
                target += c;
            }
        }
    }

    std::string json_data::un_escape(typename std::string::const_iterator& i) {
        std::string target;
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
            target += c;
        }
        return target;
    }

    extern json::data_t json_null_solo, json_false_solo;

    json::data_t json_data::factory(json::content_type type) {
        switch (type) {
            case json::content_type::null:
                return json_null_solo;

            case json::content_type::boolean:
                return json_false_solo;

            case json::content_type::number:
                return json::data_t{new json_number};

            case json::content_type::string:
                return json::data_t{new json_string};

            case json::content_type::array:
                return json::data_t{new json_array};

            case json::content_type::object:
                return json::data_t{new json_object};
        }
    }
}
