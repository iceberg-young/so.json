#ifndef INCLUDE_SO_JSON_DATA_ONCE_FLAG
#define INCLUDE_SO_JSON_DATA_ONCE_FLAG

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

        virtual json::data_t clone() = 0;

     public:
        virtual bool to_boolean() const = 0;

        virtual std::string to_string() const = 0;

        virtual double to_number() const;

        virtual json::array_t to_array() {
            return json::array_t{json{this->clone()}};
        }

        virtual json::object_t to_object() {
            return json::object_t{
              std::make_pair(this->to_string(), json{this->clone()})
            };
        }

     public:
        virtual void stringify(std::string& target, const std::string& indent) const {
            target += this->to_string();
        }

     public:
        const json::content_type type;
    };

    template<typename T_sub, typename T_value, json::content_type T_type>
    class json_copy :
      public json_data {
     public:
        json_copy() :
          json_data(T_type) {}

        json_copy(const T_value& value) :
          json_data(T_type),
          value(value) {}

        json_copy(T_value&& value) noexcept :
          json_data(T_type),
          value(std::move(value)) {}

        virtual json::data_t clone() final override {
            return std::make_shared<T_sub>(*dynamic_cast<T_sub* const>(this));
        }

     public: // Downcast helper.
        static T_value& get(const json::data_t& data) {
            return dynamic_cast<T_sub&>(*data).value;
        }

        static void set(const json::data_t& data, const T_value& value) {
            get(data) = value;
        }

        static void set(const json::data_t& data, T_value&& value) {
            std::swap(get(data), value);
        }

     protected:
        T_value value;
    };

    template<json::content_type T_type>
    class json_solo :
      public json_data,
      public std::enable_shared_from_this<json_data> {
     public:
        json_solo() :
          json_data(T_type) {}

        virtual json::data_t clone() final override {
            return this->shared_from_this();
        }
    };
}

#endif//INCLUDE_SO_JSON_DATA_ONCE_FLAG
