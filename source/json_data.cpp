#include <iomanip>
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

    std::string data::escape(const std::string &content) {
        std::stringstream ss;
        ss << std::hex;
        for (auto c : content) {
            if (c < 0x20) {
                switch (c) {
                    case '\b':
                        ss << "\\b";
                        break;

                    case '\f':
                        ss << "\\f";
                        break;

                    case '\n':
                        ss << "\\n";
                        break;

                    case '\r':
                        ss << "\\r";
                        break;

                    case '\t':
                        ss << "\\t";
                        break;

                    default:
                        ss << "\\u" << std::setfill('0') << std::setw(4) << int(c);
                        break;
                }
            }
            else {
                if (c == '"' or c == '\\') {
                    ss << '\\';
                }
                ss << c;
            }
        }
        return ss.str();
    }
}
