#include <sstream>
#include "json_array.hpp"

namespace singularity {
    std::string json_node<json_type::array>::to_string() const {
        std::stringstream ss{"["};
        for (auto &i : this->value) {
            ss << i.to_string() << ',';
        }
        std::string r = ss.str();
        *--r.end() = ']';
        return r;
    }
}
