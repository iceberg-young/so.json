#ifndef INCLUDE_SO_JSON_BOOLEAN_ONCE_FLAG
#define INCLUDE_SO_JSON_BOOLEAN_ONCE_FLAG

#include "json_data.hpp"

namespace so {
    class json_false :
      public json_solo<json::content_type::boolean> {
     public:
        bool to_boolean() const override {
            return false;
        }

        double to_number() const override {
            return 0.0;
        }

        std::string to_string() const override {
            return "false";
        }

     public:
        static json::data_t solo;
    };

    class json_true :
      public json_solo<json::content_type::boolean> {
     public:
        bool to_boolean() const override {
            return true;
        }

        double to_number() const override {
            return 1.0;
        }

        std::string to_string() const override {
            return "true";
        }

     public:
        static json::data_t solo;
    };
}

#endif//INCLUDE_SO_JSON_BOOLEAN_ONCE_FLAG
