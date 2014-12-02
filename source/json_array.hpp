#ifndef INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    class json_array :
      public json_data
    {
    public:
        json_array() :
          json_data(json::content_type::array) {
        }

        json_array(const json::array_t& value) :
          json_data(json::content_type::array),
          value(value) {
        }

        json_array(json::array_t&& value) :
          json_data(json::content_type::array),
          value(std::move(value)) {
        }

        json::data_t clone() override {
            return json::data_t{new json_array{*this}};
        }

    public:
        void be_array(const json::array_t& value) override {
            this->value = value;
        }

        void be_array(json::array_t&& value) override {
            this->value.swap(value);
        }

        json::array_t& to_array() override {
            return this->value;
        }

    public:
        bool to_boolean() const override {
            return !this->value.empty();
        }

        std::string to_string() const override;

    public:
        void stringify(std::string& target) const override;

    private:
        json::array_t value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG
