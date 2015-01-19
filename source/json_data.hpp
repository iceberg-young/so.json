#ifndef INCLUDE_SINGULARITY_JSON_DATA_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_DATA_ONCE_FLAG

#include <limits>
#include <typeinfo>
#include "json.hpp"

namespace singularity {
    class json_data :
      public std::enable_shared_from_this<json_data>
    {
    public:
        static void escape(const std::string& source, std::string& target);

        static json::data_t factory(json::content_type type);

    public:
        json_data(json::content_type type) :
          type(type) {
        }

        virtual ~json_data() {
        }

        virtual json::data_t clone() {
            return this->shared_from_this();
        }

    public:
        virtual void be_number(double value) {
            throw std::bad_cast{};
        }

        virtual void be_string(const std::string& value) {
            throw std::bad_cast{};
        }

        virtual void be_string(std::string&& value) {
            throw std::bad_cast{};
        }

        virtual void be_array(const json::array_t& value) {
            throw std::bad_cast{};
        }

        virtual void be_array(json::array_t&& value) {
            throw std::bad_cast{};
        }

        virtual void be_object(const json::object_t& value) {
            throw std::bad_cast{};
        }

        virtual void be_object(json::object_t&& value) {
            throw std::bad_cast{};
        }

    public:
        virtual bool to_boolean() const = 0;

        virtual std::string to_string() const = 0;

        virtual double to_number() const {
            return std::numeric_limits<double>::quiet_NaN();
        }

        virtual json::array_t to_array() {
            return json::array_t{json{this->clone()}};
        }

        virtual json::object_t to_object() {
            return json::object_t{std::make_pair(this->to_string(), json{this->clone()})};
        }

    public:
        virtual void stringify(std::string& target) const {
            target += this->to_string();
        }

    public:
        const json::content_type type;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_DATA_ONCE_FLAG
