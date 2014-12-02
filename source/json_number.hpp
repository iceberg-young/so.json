#ifndef INCLUDE_SINGULARITY_JSON_NUMBER_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_NUMBER_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    class json_number :
      public json_data
    {
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

    public:
        void be_number(double value) override {
            this->value = value;
        }

        double to_number() const override {
            return this->value;
        }

    public:
        bool to_boolean() const override {
            return static_cast<bool>(this->value);
        }

        std::string to_string() const override;

    public:
        void stringify(std::string& target) const override;

    private:
        double value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_NUMBER_ONCE_FLAG
