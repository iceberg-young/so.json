#ifndef INCLUDE_SINGULARITY_JSON_INTEGER_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_INTEGER_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    template<>
    class json_node<json_type::integer> :
      public json_data
    {
    public:
        json_node() :
          json_data(json_type::integer) {
        }

    public:
        void be_integer(int value) override {
            this->value = value;
        }

    public:
        int to_integer() const override {
            return this->value;
        }

    public:
        bool to_boolean() const override;

        double to_decimal() const override;

        std::string to_string() const override;

    public:
        json_detail clone() override {
            return json_detail{new json_node{*this}};
        }

    private:
        int value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_INTEGER_ONCE_FLAG
