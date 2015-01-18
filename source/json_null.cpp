#include "json_null.hpp"

namespace singularity {
    json::data_t json_null::solo{new json_null};

    json::json(std::nullptr_t value) :
      data(json_null::solo) {
    }

    json &json::be_null() {
        this->data = json_null::solo;
        return *this;
    }
}
