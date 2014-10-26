#ifndef INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    template<>
    class json_node<json_type::array> :
      public json_data
    {
    public:
        json_node() :
          json_data(json_type::array) {
        }

    public:
        void be_array(const json_array &value) override {
            this->value = value;
        }

    public:
        json_array &to_array() override {
            return this->value;
        }

    public:
        std::string to_string() const override;

    public:
        json_detail clone() override {
            return json_detail{new json_node{*this}};
        }

    private:
        json_array value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG
