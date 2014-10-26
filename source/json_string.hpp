#ifndef INCLUDE_SINGULARITY_JSON_STRING_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_STRING_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    template<>
    class json_node<json_type::string> :
      public json_data
    {
    public:
        json_node() :
          json_data(json_type::string) {
        }

    public:
        void be_string(const std::string &value) override {
            this->value = value;
        }

    public:
        std::string to_string() const override {
            return this->value;
        }

    public:
        bool to_boolean() const override {
            return this->value.empty();
        }

        double to_decimal() const override {
            return std::stod(this->value);
        }

        int to_integer() const override {
            return std::stoi(this->value);
        }

    public:
        json_detail clone() override {
            return json_detail{new json_node{*this}};
        }

    private:
        std::string value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_STRING_ONCE_FLAG
