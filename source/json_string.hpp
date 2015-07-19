#ifndef INCLUDE_SO_JSON_STRING_ONCE_FLAG
#define INCLUDE_SO_JSON_STRING_ONCE_FLAG

#include "json_data.hpp"

namespace so {
    class json_string :
      public json_copy<json_string, std::string, json::content_type::string> {
     public:
        json_string() :
          json_copy() {}

        json_string(const std::string& value) :
          json_copy(value) {}

        json_string(std::string&& value) noexcept :
          json_copy(std::move(value)) {}

     public:
        bool to_boolean() const final override {
            return not this->value.empty();
        }

        double to_number() const final override {
            return std::stod(this->value);
        }

        std::string to_string() const final override {
            return this->value;
        }

        json::array_t to_array() const final override {
            return this->value.empty()
              ? json::array_t{}
              : json::array_t{this->value};
        }

        json::object_t to_object() const final override {
            return this->value.empty()
              ? json::object_t{}
              : json::object_t{{"0", this->value}};
        }

     public:
        void stringify(std::string& target, const std::string& indent) const final override;
    };
}

#endif//INCLUDE_SO_JSON_STRING_ONCE_FLAG
