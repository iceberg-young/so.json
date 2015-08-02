/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include "json_data.hpp"

namespace so {
    class json_object :
      public json_copy<json_object, json::object_t, json::content_type::object> {
     public:
        json_object() :
          json_copy() {}

        json_object(const json::object_t& value) :
          json_copy(value) {}

        json_object(json::object_t&& value) noexcept :
          json_copy(std::move(value)) {}

     public:
        bool to_boolean() const final override {
            return not this->value.empty();
        }

        double to_number() const final override;

        std::string to_string() const final override;

        json::array_t to_array() const final override;

        json::object_t to_object() const final override {
            return this->value;
        }

     public:
        void stringify(std::string& target, const std::string& indent) const final override;
    };
}
