#include <iomanip>
#include "json_data.hpp"
#include "json_null.hpp"
#include "json_boolean.hpp"
#include "json_decimal.hpp"
#include "json_integer.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include "json_object.hpp"

namespace singularity {
    detail_t json_node_null{new json_node<content_t::null>};

    detail_t json_data::factory(content_t type) {
        switch (type) {
            case content_t::null:
                return json_node_null;

            case content_t::boolean:
                return detail_t{new json_node<content_t::boolean>};

            case content_t::decimal:
                return detail_t{new json_node<content_t::decimal>};

            case content_t::integer:
                return detail_t{new json_node<content_t::integer>};

            case content_t::string:
                return detail_t{new json_node<content_t::string>};

            case content_t::array:
                return detail_t{new json_node<content_t::array>};

            case content_t::object:
                return detail_t{new json_node<content_t::object>};
        }
    }

    std::string json_data::escape(const std::string &content) {
        std::stringstream ss;
        ss << std::hex;
        for (auto c : content) {
            if (c < 0x20) {
                ss << "\\u" << std::setfill('0') << std::setw(4) << int(c);
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
