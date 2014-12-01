#ifndef INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    namespace json_uh {
        template<>
        class node<content_t::object> :
          public data
        {
        public:
            node() :
              data(content_t::object) {
            }

        public:
            void be_object(const object_t &value) override {
                this->value = value;
            }

            void be_object(object_t &&value) override {
                this->value.swap(value);
            }

        public:
            object_t &to_object() override {
                return this->value;
            }

        public:
            bool to_boolean() const override {
                return !this->value.empty();
            }

            std::string to_string() const override {
                return "[object Object]";
            }

        public:
            void stringify(std::string &target) const override {
                target += '{';
                if (!this->value.empty()) {
                    auto e = --this->value.end();
                    for (auto i = this->value.begin(); i != e; ++i) {
                        append_pair(i->first, i->second, target);
                        target += ',';
                    }
                    append_pair(e->first, e->second, target);
                }
                target += '}';
            }

        public:
            data_t clone() override {
                return data_t{new node{*this}};
            }

        private:
            static void append_pair(const std::string &name, const json &value, std::string &target) {
                target += '"';
                escape(name, target);
                target += "\":";
                value.data->stringify(target);
            }

        private:
            object_t value;
        };
    }
}

#endif//INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG
