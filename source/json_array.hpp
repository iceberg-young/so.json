#ifndef INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG

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
                std::string s;
                if (!this->value.empty()) {
                    auto e = --this->value.end();
                    for (auto i = this->value.begin(); i != e; ++i) {
                        (s += i->to_string()) += ',';
                    }
                    s += e->to_string();
                }
                return s;
            }

        public:
            void stringify(std::string &target) const override {
                target += '[';
                if (!this->value.empty()) {
                    auto e = --this->value.end();
                    for (auto i = this->value.begin(); i != e; ++i) {
                        i->data->stringify(target);
                        target += ',';
                    }
                    e->data->stringify(target);
                }
                target += ']';
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
