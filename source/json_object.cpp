#include <sstream>
#include "json_object.hpp"

namespace singularity {
    std::string json_node<json_type::object>::to_string() const {
        std::stringstream ss{"{"};
        for (auto &i : this->value) {
            ss << i.first << ':' << i.second.to_string() << ',';
        }
        std::string r = ss.str();
        *--r.end() = '}';
        return r;
    }
}
