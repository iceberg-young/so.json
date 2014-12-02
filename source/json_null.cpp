#include "json_null.hpp"

namespace singularity {
    json::data_t json_null_solo{new json_null};

    json::json() :
      data(json_null_solo) {
    }

    json &json::be_null() {
        this->data = json_null_solo;
        return *this;
    }
}
