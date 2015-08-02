/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include "json_data.hpp"

namespace so {
    class json_null :
      public json_solo<json_null, json::content_type::null> {
     public:
        bool to_boolean() const final override {
            return false;
        }

        double to_number() const final override {
            return 0.0;
        }

        std::string to_string() const final override {
            return "";
        }

        json::array_t to_array() const final override {
            return json::array_t{};
        }

        json::object_t to_object() const final override {
            return json::object_t{};
        }

     public:
        void stringify(std::string& target, const std::string& indent) const final override {
            target += "null";
        }

     public:
        static const json::data_t solo;
    };
}
