#ifndef INCLUDE_SINGULARITY_JSON_INTEGER_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_INTEGER_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    template<>
    class json_node<content_t::integer> :
      public json_data
    {
    public:
        json_node() :
          json_data(content_t::integer) {
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
        bool to_boolean() const override {
            return static_cast<bool>(this->value);
        }

        double to_decimal() const override {
            return static_cast<double>(this->value);
        }

        std::string to_string() const override {
            return std::to_string(this->value);
        }

    public:
        detail_t clone() override {
            return detail_t{new json_node{*this}};
        }

    private:
        int value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_INTEGER_ONCE_FLAG
