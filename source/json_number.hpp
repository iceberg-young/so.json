#ifndef INCLUDE_SINGULARITY_JSON_NUMBER_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_NUMBER_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    namespace json_uh {
        template<>
        class node<content_t::number> :
          public data
        {
        public:
            node() :
              data(content_t::number) {
            }

        public:
            void be_number(double value) override {
                this->value = value;
            }

        public:
            double to_number() const override {
                return this->value;
            }

        public:
            bool to_boolean() const override {
                return static_cast<bool>(this->value);
            }

            std::string to_string() const override {
                return std::to_string(this->value);
            }

        public:
            data_t clone() override {
                return data_t{new node{*this}};
            }

        private:
            double value;
        };
    }
}

#endif//INCLUDE_SINGULARITY_JSON_NUMBER_ONCE_FLAG
