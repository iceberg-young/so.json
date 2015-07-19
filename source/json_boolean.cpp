#include "json_boolean.hpp"

namespace so {
    const json::data_t json_false::solo{std::make_shared<json_false>()};

    const json::data_t json_true::solo{std::make_shared<json_true>()};

    json::json(bool value) :
      data(value ? json_true::solo : json_false::solo) {}

    json& json::be_boolean(bool value) {
        this->data = value ? json_true::solo : json_false::solo;
        return *this;
    }

    bool json::to_boolean() const {
        return this->data->to_boolean();
    }
}
