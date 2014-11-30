#ifndef INCLUDE_SINGULARITY_JSON_NULL_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_NULL_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    namespace json_uh {
        template<>
        class node<content_t::null> :
          public data
        {
        public:
            node() :
              data(content_t::null) {
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
            std::string stringify() const override {
                return "null";
            }

        public:
            data_t clone() override {
                return this->shared_from_this();
            }
        };
    }
}

#endif//INCLUDE_SINGULARITY_JSON_NULL_ONCE_FLAG
