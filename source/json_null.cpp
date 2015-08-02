/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

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
