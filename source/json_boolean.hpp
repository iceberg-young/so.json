#ifndef INCLUDE_SINGULARITY_JSON_BOOLEAN_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_BOOLEAN_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    template<>
    class json_node<json_type::boolean> :
      public json_data
    {
    public:
        json_node() :
          json_data(json_type::boolean) {
        }

    public:
        void be_boolean(bool value) override {
            this->value = value;
        }

    public:
        bool to_boolean() const override {
            return this->value;
        }

    public:
        double to_decimal() const override {
            return this->value ? 1.0 : 0.0;
        }

        int to_integer() const override {
            return this->value ? 1 : 0;
        }

        std::string to_string() const override {
            return this->value ? "true" : "false";
        }

    public:
        json_detail clone() override {
            return json_detail{new json_node{*this}};
        }

    private:
        bool value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_BOOLEAN_ONCE_FLAG
