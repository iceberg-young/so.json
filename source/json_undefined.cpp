#include "json_undefined.hpp"

namespace singularity {
    bool json_node<json_type::undefined>::to_boolean() const {
        return false;
    }

    double json_node<json_type::undefined>::to_decimal() const {
        return 0.0;
    }

    int json_node<json_type::undefined>::to_integer() const {
        return 0;
    }

    std::string json_node<json_type::undefined>::to_string() const {
        return std::string{"undefined"};
    }
}
