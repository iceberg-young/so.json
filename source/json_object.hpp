#ifndef INCLUDE_SO_JSON_OBJECT_ONCE_FLAG
#define INCLUDE_SO_JSON_OBJECT_ONCE_FLAG

#include "json_data.hpp"

namespace so {
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

        json_object(json::object_t&& value) noexcept :
          json_data(json::content_type::object),
          value(std::move(value)) {
        }

        json::data_t clone() override {
            return json::data_t{new json_object{*this}};
        }

    public:
        static json::object_t& get(const json::data_t& data) {
            return dynamic_cast<json_object&>(*data).value;
        }

        static void set(const json::data_t& data, const json::object_t& value) {
            get(data) = value;
        }

        static void set(const json::data_t& data, json::object_t&& value) {
            get(data).swap(value);
        }

    public:
        json::object_t to_object() override {
            return this->value;
        }

    public:
        bool to_boolean() const override {
            return !this->value.empty();
        }

        std::string to_string() const override {
            return "[object Object]";
        }

        json::array_t to_array() override;

    public:
        void stringify(std::string& target) const override;

    protected:
        static void append_pair(const std::string& name, const json& value, std::string& target);

    private:
        json::object_t value;
    };
}

#endif//INCLUDE_SO_JSON_OBJECT_ONCE_FLAG
