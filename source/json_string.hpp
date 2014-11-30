#ifndef INCLUDE_SINGULARITY_JSON_STRING_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_STRING_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    namespace json_uh {
        template<>
        class node<content_t::string> :
          public data
        {
        public:
            node() :
              data(content_t::string) {
            }

        public:
            void be_string(const std::string &value) override {
                this->value = value;
            }

            void be_string(std::string &&value) override {
                this->value.swap(value);
            }

        public:
            std::string to_string() const override {
                return this->value;
            }

        public:
            bool to_boolean() const override {
                return !this->value.empty();
            }

            double to_number() const override {
                return std::stod(this->value);
            }

        public:
            std::string stringify() const override {
                return '"' + escape(this->to_string()) + '"';
            }

        public:
            data_t clone() override {
                return data_t{new node{*this}};
            }

        private:
            std::string value;
        };
    }
}

#endif//INCLUDE_SINGULARITY_JSON_STRING_ONCE_FLAG
