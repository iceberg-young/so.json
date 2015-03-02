#ifndef INCLUDE_SO_JSON_ARRAY_ONCE_FLAG
#define INCLUDE_SO_JSON_ARRAY_ONCE_FLAG

#include "json_data.hpp"

namespace so {
    class json_array :
      public json_data
    {
    public:
        json_array() :
          json_data(json::content_type::array) {
        }

        json_array(const json::array_t& value) :
          json_data(json::content_type::array),
          value(value) {
        }

        json_array(json::array_t&& value) noexcept :
          json_data(json::content_type::array),
          value(std::move(value)) {
        }

        json::data_t clone() override {
            return json::data_t{new json_array{*this}};
        }

    public:
        static json::array_t& get(const json::data_t& data) {
            return dynamic_cast<json_array&>(*data).value;
        }

        static void set(const json::data_t& data, const json::array_t& value) {
            get(data) = value;
        }

        static void set(const json::data_t& data, json::array_t&& value) {
            get(data).swap(value);
        }

    public:
        json::array_t to_array() override {
            return this->value;
        }

    public:
        bool to_boolean() const override {
            return not this->value.empty();
        }

        std::string to_string() const override;

        json::object_t to_object() override;

    public:
        void stringify(std::string& target) const override;

    private:
        json::array_t value;
    };
}

#endif//INCLUDE_SO_JSON_ARRAY_ONCE_FLAG
