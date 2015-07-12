#ifndef INCLUDE_SO_JSON_NUMBER_ONCE_FLAG
#define INCLUDE_SO_JSON_NUMBER_ONCE_FLAG

#include "json_data.hpp"

namespace so {
    class json_number :
      public json_data {
     public:
        json_number() :
          json_data(json::content_type::number) {
        }

        json_number(double value) :
          json_data(json::content_type::number),
          value(value) {
        }

        json::data_t clone() override {
            return json::data_t{new json_number{*this}};
        }

     public: // Downcast helper.
        static void set(const json::data_t& data, double value) {
            dynamic_cast<json_number&>(*data).value = value;
        }

     public:
        double to_number() const override {
            return this->value;
        }

        bool to_boolean() const override {
            return static_cast<bool>(this->value);
        }

        std::string to_string() const override;

     public:
        void stringify(std::string& target, const std::string& indent) const override;

     private:
        double value;
    };
}

#endif//INCLUDE_SO_JSON_NUMBER_ONCE_FLAG
