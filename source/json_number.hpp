#ifndef INCLUDE_SO_JSON_NUMBER_ONCE_FLAG
#define INCLUDE_SO_JSON_NUMBER_ONCE_FLAG

#include "json_data.hpp"

namespace so {
    class json_number :
      public json_copy<json_number, double, json::content_type::number> {
     public:
        json_number() :
          json_copy() {}

        json_number(double value) :
          json_copy(value) {}

     public:
        bool to_boolean() const final override {
            return static_cast<bool>(this->value);
        }

        double to_number() const final override {
            return this->value;
        }

        std::string to_string() const final override;

        json::array_t to_array() const final override;

        json::object_t to_object() const final override;
    };
}

#endif//INCLUDE_SO_JSON_NUMBER_ONCE_FLAG
