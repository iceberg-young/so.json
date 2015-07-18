#ifndef INCLUDE_SO_JSON_OBJECT_ONCE_FLAG
#define INCLUDE_SO_JSON_OBJECT_ONCE_FLAG

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
        json::object_t to_object() final override {
            return this->value;
        }

        bool to_boolean() const final override {
            return not this->value.empty();
        }

        std::string to_string() const final override {
            return "[object Object]";
        }

        json::array_t to_array() final override;

     public:
        void stringify(std::string& target, const std::string& indent) const final override;
    };
}

#endif//INCLUDE_SO_JSON_OBJECT_ONCE_FLAG
