#include "json_data.hpp"
#include "json_undefined.hpp"
#include "json_null.hpp"
#include "json_boolean.hpp"
#include "json_decimal.hpp"
#include "json_integer.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include "json_object.hpp"

namespace singularity {
    json_detail json_node_undefined{new json_node<json_type::undefined>};

    json_detail json_node_null{new json_node<json_type::null>};

    json_detail json_data::factory(json_type type) {
        switch (type) {
            case json_type::undefined:
                return json_node_undefined;

            case json_type::null:
                return json_node_null;

            case json_type::boolean:
                return json_detail{new json_node<json_type::boolean>};

            case json_type::decimal:
                return json_detail{new json_node<json_type::decimal>};

            case json_type::integer:
                return json_detail{new json_node<json_type::integer>};

            case json_type::string:
                return json_detail{new json_node<json_type::string>};

            case json_type::array:
                return json_detail{new json_node<json_type::array>};

            case json_type::object:
                return json_detail{new json_node<json_type::object>};
        }
    }
}
