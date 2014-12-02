#include "json_boolean.hpp"

namespace singularity {
    json::data_t json_true_solo{new json_true};

    json::data_t json_false_solo{new json_false};

    json::json(bool value) :
      data(value ? json_true_solo : json_false_solo) {
    }

    json &json::be_boolean(bool value) {
        this->data = value ? json_true_solo : json_false_solo;
        return *this;
    }

    bool json::to_boolean() const {
        return this->data->to_boolean();
    }
}
