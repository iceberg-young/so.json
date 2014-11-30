#ifndef INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG

#include <sstream>
#include "json_data.hpp"

namespace singularity {
    namespace json_uh {
        template<>
        class node<content_t::array> :
          public data
        {
        public:
            node() :
              data(content_t::array) {
            }

        public:
            void be_array(const array_t &value) override {
                this->value = value;
            }

            void be_array(array_t &&value) override {
                this->value.swap(value);
            }

        public:
            array_t &to_array() override {
                return this->value;
            }

        public:
            bool to_boolean() const override {
                return !this->value.empty();
            }

            std::string to_string() const override {
                std::stringstream ss;
                for (auto &i : this->value) {
                    ss << ',' << i.to_string();
                }
                return ss.str().substr(1);
            }

        public:
            std::string stringify() const override {
                std::stringstream ss;
                for (auto &i : this->value) {
                    ss << ',' << i.stringify();
                }
                return '[' + ss.str().substr(1) + ']';
            }

        public:
            data_t clone() override {
                return data_t{new node{*this}};
            }

        private:
            array_t value;
        };
    }
}

#endif//INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG
