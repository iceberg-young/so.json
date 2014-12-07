#ifndef INCLUDE_SINGULARITY_JSON_NULL_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_NULL_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    class json_null :
      public json_data
    {
    public:
        json_null() :
          json_data(json::content_type::null) {
        }

    public:
        bool to_boolean() const override {
            return false;
        }

        double to_number() const override {
            return 0.0;
        }

        std::string to_string() const override {
            return "";
        }

    public:
        void stringify(std::string& target) const override {
            target += "null";
        }

    public:
        static json::data_t solo;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_NULL_ONCE_FLAG
