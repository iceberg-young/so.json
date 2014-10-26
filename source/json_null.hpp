#ifndef INCLUDE_SINGULARITY_JSON_NULL_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_NULL_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    template<>
    class json_node<json_type::null> :
      public json_data
    {
    public:
        json_node() :
          json_data(json_type::null) {
        }

    public:
        bool to_boolean() const override {
            return false;
        }

        double to_decimal() const override {
            return 0.0;
        }

        int to_integer() const override {
            return 0;
        }

        std::string to_string() const override {
            return "";
        }

    public:
        json_detail clone() override {
            return this->shared_from_this();
        }
    };
}

#endif//INCLUDE_SINGULARITY_JSON_NULL_ONCE_FLAG
