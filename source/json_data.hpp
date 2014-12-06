#ifndef INCLUDE_SINGULARITY_JSON_DATA_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_DATA_ONCE_FLAG

#include <typeinfo>
#include "../include/json.hpp"

namespace singularity {
    class json_data :
      public std::enable_shared_from_this<json_data>
    {
    public:
        using cursor = std::string::const_iterator;

    public:
        static json::pointer_t decode(cursor& c);

        static void escape(const std::string& source, std::string& target);

        static std::string un_escape(cursor& i);

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
        virtual bool to_boolean() const {
            throw std::bad_cast{};
        }

        virtual double to_number() const {
            throw std::bad_cast{};
        }

        virtual std::string to_string() const {
            throw std::bad_cast{};
        }

        virtual json::array_t& to_array() {
            throw std::bad_cast{};
        }

        virtual json::object_t& to_object() {
            throw std::bad_cast{};
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
