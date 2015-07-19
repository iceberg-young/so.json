#include "json_null.hpp"

namespace so {
    const json::data_t json_null::solo{std::make_shared<json_null>()};

    json::json(std::nullptr_t value) :
      data(json_null::solo) {}

    json& json::be_null() {
        this->data = json_null::solo;
        return *this;
    }
}
