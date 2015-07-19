#ifndef INCLUDE_SO_JSON_BOOLEAN_ONCE_FLAG
#define INCLUDE_SO_JSON_BOOLEAN_ONCE_FLAG

#include "json_data.hpp"

namespace so {
    class json_false :
      public json_solo<json_false, json::content_type::boolean> {
     public:
        bool to_boolean() const final override {
            return false;
        }

        double to_number() const final override {
            return 0.0;
        }

        std::string to_string() const final override {
            return "false";
        }

     public:
        static const json::data_t solo;
    };

    class json_true :
      public json_solo<json_true, json::content_type::boolean> {
     public:
        bool to_boolean() const final override {
            return true;
        }

        double to_number() const final override {
            return 1.0;
        }

        std::string to_string() const final override {
            return "true";
        }

     public:
        static const json::data_t solo;
    };
}

#endif//INCLUDE_SO_JSON_BOOLEAN_ONCE_FLAG
