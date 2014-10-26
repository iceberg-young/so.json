#include "json_null.hpp"

namespace singularity {
    bool json_node<json_type::null>::to_boolean() const {
        return false;
    }

    double json_node<json_type::null>::to_decimal() const {
        return 0.0;
    }

    int json_node<json_type::null>::to_integer() const {
        return 0;
    }

    std::string json_node<json_type::null>::to_string() const {
        return "null";
    }
}
