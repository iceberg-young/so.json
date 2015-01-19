#ifndef INCLUDE_SINGULARITY_JSON_STRING_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_STRING_ONCE_FLAG

#include "json_data.hpp"

namespace singularity {
    class json_string :
      public json_data
    {
    public:
        json_string() :
          json_data(json::content_type::string) {
        }

        json_string(const std::string& value) :
          json_data(json::content_type::string),
          value(value) {
        }

        json_string(std::string&& value) noexcept :
          json_data(json::content_type::string),
          value(std::move(value)) {
        }

        json::data_t clone() override {
            return json::data_t{new json_string{*this}};
        }

    public:
        static std::string& get(const json::data_t& data) {
            return dynamic_cast<json_string&>(*data).value;
        }

        static void set(const json::data_t& data, const std::string& value) {
            get(data) = value;
        }

        static void set(const json::data_t& data, std::string&& value) {
            get(data).swap(value);
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
        void stringify(std::string& target) const override;

    private:
        std::string value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_STRING_ONCE_FLAG
