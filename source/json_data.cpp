#include "json_null.hpp"
#include "json_boolean.hpp"
#include "json_number.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include "json_object.hpp"

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
