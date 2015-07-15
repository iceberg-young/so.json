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
        std::string to_string() const override {
            return this->value;
        }

        bool to_boolean() const override {
            return not this->value.empty();
        }

        double to_number() const override {
            return std::stod(this->value);
        }

     public:
        void stringify(std::string& target, const std::string& indent) const override;
    };
}

#endif//INCLUDE_SO_JSON_STRING_ONCE_FLAG
