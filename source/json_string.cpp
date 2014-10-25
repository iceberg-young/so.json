#include "json_string.hpp"

namespace singularity {
    bool json_node<json_type::string>::to_boolean() const {
        return this->value.empty();
    }

    double json_node<json_type::string>::to_decimal() const {
        return std::stod(this->value);
    }

    int json_node<json_type::string>::to_integer() const {
        return std::stoi(this->value);
    }
}
