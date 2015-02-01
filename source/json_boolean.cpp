#include "json_boolean.hpp"

namespace so {
    json::data_t json_true::solo{new json_true};

    json::data_t json_false::solo{new json_false};

    json::json(bool value) :
      data(value ? json_true::solo : json_false::solo) {
    }

    json &json::be_boolean(bool value) {
        this->data = value ? json_true::solo : json_false::solo;
        return *this;
    }

    bool json::to_boolean() const {
        return this->data->to_boolean();
    }
}
