#include "json_decimal.hpp"

namespace singularity {
    bool json_node<json_type::decimal>::to_boolean() const {
        return static_cast<bool>(this->value);
    }

    int json_node<json_type::decimal>::to_integer() const {
        return static_cast<int>(this->value);
    }

    std::string json_node<json_type::decimal>::to_string() const {
        return std::to_string(this->value);
    }
}
