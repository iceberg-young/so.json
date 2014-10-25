#ifndef INCLUDE_SINGULARITY_JSON_UNDEFINED_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_UNDEFINED_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    template<>
    class json_node<json_type::undefined> :
      public json_data
    {
    public:
        json_node() :
          json_data(json_type::undefined) {
        }

    public:
        bool to_boolean() const override;

        double to_decimal() const override;

        int to_integer() const override;

        std::string to_string() const override;

    public:
        json_detail clone() override {
            return this->shared_from_this();
        }
    };
}

#endif//INCLUDE_SINGULARITY_JSON_UNDEFINED_ONCE_FLAG
