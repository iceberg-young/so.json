#ifndef INCLUDE_SINGULARITY_JSON_BOOLEAN_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_BOOLEAN_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    class json_false :
      public json_data
    {
    public:
        json_false() :
          json_data(json::content_type::boolean) {
        }

    public:
        bool to_boolean() const override {
            return false;
        }

    public:
        double to_number() const override {
            return 0.0;
        }

        std::string to_string() const override {
            return "false";
        }

    public:
        void stringify(std::string& target) const override {
            target += "false";
        }
    };

    class json_true :
      public json_data
    {
    public:
        json_true() :
          json_data(json::content_type::boolean) {
        }

    public:
        bool to_boolean() const override {
            return true;
        }

    public:
        double to_number() const override {
            return 1.0;
        }

        std::string to_string() const override {
            return "true";
        }

    public:
        void stringify(std::string& target) const override {
            target += "true";
        }
    };
}

#endif//INCLUDE_SINGULARITY_JSON_BOOLEAN_ONCE_FLAG
