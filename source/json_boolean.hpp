#ifndef INCLUDE_SINGULARITY_JSON_BOOLEAN_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_BOOLEAN_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    namespace json_uh {
        template<>
        class node<content_t::boolean> :
          public data
        {
        public:
            node() :
              data(content_t::boolean) {
            }

        public:
            void be_boolean(bool value) override {
                this->value = value;
            }

        public:
            bool to_boolean() const override {
                return this->value;
            }

        public:
            double to_number() const override {
                return this->value ? 1.0 : 0.0;
            }

            std::string to_string() const override {
                return this->value ? "true" : "false";
            }

        public:
            data_t clone() override {
                return data_t{new node{*this}};
            }

        private:
            bool value;
        };
    }
}

#endif//INCLUDE_SINGULARITY_JSON_BOOLEAN_ONCE_FLAG
