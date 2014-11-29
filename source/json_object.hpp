#ifndef INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    template<>
    class json_node<content_t::object> :
      public json_data
    {
    public:
        json_node() :
          json_data(content_t::object) {
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
        std::string stringify() const override {
            std::stringstream ss;
            for (auto &i : this->value) {
                ss << ",\"" << json_data::escape(i.first) << "\":" << i.second.stringify();
            }
            return '{' + ss.str().substr(1) + '}';
        }

    public:
        detail_t clone() override {
            return detail_t{new json_node{*this}};
        }

    private:
        object_t value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG
