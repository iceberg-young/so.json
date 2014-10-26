#include "json_boolean.hpp"

namespace singularity {
    double json_node<json_type::boolean>::to_decimal() const {
        return this->value ? 1.0 : 0.0;
    }

    int json_node<json_type::boolean>::to_integer() const {
        return this->value ? 1 : 0;
    }

    std::string json_node<json_type::boolean>::to_string() const {
        return this->value ? "true" : "false";
    }
}
