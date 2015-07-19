#ifndef INCLUDE_SO_JSON_ARRAY_ONCE_FLAG
#define INCLUDE_SO_JSON_ARRAY_ONCE_FLAG

#include "json_data.hpp"

namespace so {
    class json_array :
      public json_copy<json_array, json::array_t, json::content_type::array> {
     public:
        json_array() :
          json_copy() {}

        json_array(const json::array_t& value) :
          json_copy(value) {}

        json_array(json::array_t&& value) noexcept :
          json_copy(std::move(value)) {}

     public:
        bool to_boolean() const final override {
            return not this->value.empty();
        }

        double to_number() const final override;

        std::string to_string() const final override;

        json::array_t to_array() const final override {
            return this->value;
        }

        json::object_t to_object() const final override;

     public:
        void stringify(std::string& target, const std::string& indent) const final override;
    };
}

#endif//INCLUDE_SO_JSON_ARRAY_ONCE_FLAG
