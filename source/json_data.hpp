/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include "json.hpp"

namespace so {
    class json_data {
     public:
        static const std::string esc_label;
        static const std::string esc_value;

        static void escape(const std::string& source, std::string& target);

        static json::data_t factory(json::content_type type);

     public:
        json_data(json::content_type type) :
          type(type) {}

        virtual ~json_data() {}

        virtual json::data_t clone() const = 0;

     public:
        virtual bool to_boolean() const = 0;

        virtual std::string to_string() const = 0;

        virtual double to_number() const = 0;

        virtual json::array_t to_array() const = 0;

        virtual json::object_t to_object() const = 0;

     public:
        virtual void stringify(std::string& target, const std::string& indent) const {
            target += this->to_string();
        }

     public:
        const json::content_type type;
    };

    template<typename sub_t, typename value_t, json::content_type type_t>
    class json_copy :
      public json_data {
     public:
        json_copy() :
          json_data(type_t) {}

        json_copy(const value_t& value) :
          json_data(type_t),
          value(value) {}

        json_copy(value_t&& value) noexcept :
          json_data(type_t),
          value(std::move(value)) {}

        virtual json::data_t clone() const final override {
            return std::make_shared<sub_t>(*dynamic_cast<const sub_t* const>(this));
        }

     public: // Downcast helper.
        static value_t& get(const json::data_t& data) {
            return dynamic_cast<sub_t&>(*data).value;
        }

        static void set(const json::data_t& data, const value_t& value) {
            get(data) = value;
        }

        static void set(const json::data_t& data, value_t&& value) {
            std::swap(get(data), value);
        }

     protected:
        value_t value;
    };

    template<typename sub_t, json::content_type type_t>
    class json_solo :
      public json_data {
     public:
        json_solo() :
          json_data(type_t) {}

        virtual json::data_t clone() const final override {
            return sub_t::solo;
        }
    };
}
