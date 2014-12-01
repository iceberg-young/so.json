#include "json_null.hpp"
#include "json_boolean.hpp"
#include "json_number.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include "json_object.hpp"

namespace singularity {
    using namespace json_uh;

    data_t json_node_null{new node<content_t::null>};

    data_t data::factory(content_t type) {
        switch (type) {
            case content_t::null:
                return json_node_null;

            case content_t::boolean:
                return data_t{new node<content_t::boolean>};

            case content_t::number:
                return data_t{new node<content_t::number>};

            case content_t::string:
                return data_t{new node<content_t::string>};

            case content_t::array:
                return data_t{new node<content_t::array>};

            case content_t::object:
                return data_t{new node<content_t::object>};
        }
    }

    void data::escape(const std::string &source, std::string &target) {
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
}
