#ifndef INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    template<>
    class json_node<json_type::object> :
      public json_data
    {
    public:
        json_node() :
          json_data(json_type::object) {
        }

    public:
        void be_object(const json_object &value) override {
            this->value = value;
        }

    public:
        json_object &to_object() override {
            return this->value;
        }

    public:
        std::string to_string() const override;

    public:
        json_detail clone() override {
            return json_detail{new json_node{*this}};
        }

    private:
        json_object value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG
