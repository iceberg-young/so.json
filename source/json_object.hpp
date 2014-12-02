#ifndef INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    class json_object :
      public json_data
    {
    public:
        json_object() :
          json_data(json::content_type::object) {
        }

        json_object(const json::object_t& value) :
          json_data(json::content_type::object),
          value(value) {
        }

        json_object(json::object_t&& value) :
          json_data(json::content_type::object),
          value(std::move(value)) {
        }

        json::data_t clone() override {
            return json::data_t{new json_object{*this}};
        }

    public:
        void be_object(const json::object_t& value) override {
            this->value = value;
        }

        void be_object(json::object_t&& value) override {
            this->value.swap(value);
        }

        json::object_t& to_object() override {
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
        void stringify(std::string& target) const override;

    protected:
        static void append_pair(const std::string& name, const json& value, std::string& target);

    private:
        json::object_t value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_OBJECT_ONCE_FLAG
