#include "json_integer.hpp"

namespace singularity {
    bool json_node<json_type::integer>::to_boolean() const {
        return static_cast<bool>(this->value);
    }

    double json_node<json_type::integer>::to_decimal() const {
        return static_cast<double>(this->value);
    }

    std::string json_node<json_type::integer>::to_string() const {
        return std::to_string(this->value);
    }
}
