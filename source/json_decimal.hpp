#ifndef INCLUDE_SINGULARITY_JSON_DECIMAL_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_DECIMAL_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    template<>
    class json_node<json_type::decimal> :
      public json_data
    {
    public:
        json_node() :
          json_data(json_type::decimal) {
        }

    public:
        void be_decimal(double value) override {
            this->value = value;
        }

    public:
        double to_decimal() const override {
            return this->value;
        }

    public:
        bool to_boolean() const override;

        int to_integer() const override;

        std::string to_string() const override;

    public:
        json_detail clone() override {
            return json_detail{new json_node{*this}};
        }

    private:
        double value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_DECIMAL_ONCE_FLAG
