/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */
#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

namespace so {
    // Representation of RFC-7159 specified object.
    class json {
     public:
        enum class content_type {
            null,
            boolean,
            number,
            string,
            array,
            object,
        };

     public: // Type aliases.
        // Implementation type of content_type::object.
        using object_t = std::map<std::string, json>;

        // Implementation type of content_type::array.
        using array_t = std::vector<json>;

        // Implementation type of internal details.
        using data_t = std::shared_ptr<class json_data>;

     public: // Convert from/to JSON text.
        // Initialize from a JSON text, may throw json_parse_error.
        // Will move the iterator to pass the end.
        static json parse(std::string::const_iterator& iterator);

        static json parse(const std::string& text) {
            auto iterator = text.begin();
            return json::parse(iterator);
        }

        // Format a JSON text.
        // false: all in one line; true: indented multi-line
        std::string stringify(bool pretty = false) const;

     public: // Constructors.
        // Initialize an empty node.
        json(content_type type);

        // Clone from the other node.
        json(const json& other);

        // Steal from the other node.
        json(json&& other) noexcept :
          data(std::move(other.data)) {}

        // Steal the heart.
        json(data_t&& data) noexcept :
          data(std::move(data)) {}

     public: // Initialize by value.
        json(std::nullptr_t value = nullptr);

        json(bool value);

        json(double value);

        json(int value) :
          json(double(value)) {}

        json(const std::string& value);

        json(std::string&& value);

        json(const char* value) :
          json(std::string{value}) {}

        json(const array_t& value);

        json(array_t&& value);

        json(const object_t& value);

        json(object_t&& value);

        json(void*) = delete;

     public: // Get/set content type.
        json& be(content_type type);

        content_type type() const;

        std::string type_name() const;

     public: // Set content value. Return *this.
        json& be_null();

        json& be_boolean(bool value);

        json& be_number(double value);

        json& be_string(const std::string& value);

        json& be_string(std::string&& value);

        json& be_array(const array_t& value);

        json& be_array(array_t&& value);

        json& be_object(const object_t& value);

        json& be_object(object_t&& value);

     public: // Shortcuts of setting content value. Return *this.
        json& operator=(std::nullptr_t) {
            return this->be_null();
        }

        json& operator=(bool value) {
            return this->be_boolean(value);
        }

        json& operator=(double value) {
            return this->be_number(value);
        }

        json& operator=(int value) {
            return this->be_number(value);
        }

        json& operator=(const std::string& value) {
            return this->be_string(value);
        }

        json& operator=(std::string&& value) {
            return this->be_string(std::move(value));
        }

        json& operator=(const char* value) {
            return this->be_string(std::string(value));
        }

        json& operator=(const array_t& value) {
            return this->be_array(value);
        }

        json& operator=(array_t&& value) {
            return this->be_array(std::move(value));
        }

        json& operator=(const object_t& value) {
            return this->be_object(value);
        }

        json& operator=(object_t&& value) {
            return this->be_object(std::move(value));
        }

        json& operator=(const json& other);

        json& operator=(json&& other) {
            this->data.swap(other.data);
            return *this;
        }

     public: // Get content value.
        bool to_boolean() const;

        double to_number() const;

        std::string to_string() const;

        array_t to_array() const;

        object_t to_object() const;

        array_t& as_array();

        object_t& as_object();

     public: // Shortcuts of getting content value.
        operator bool() const {
            return this->to_boolean();
        }

        operator double() const {
            return this->to_number();
        }

        operator int() const {
            return static_cast<int>(this->to_number());
        }

        operator std::string() const {
            return this->to_string();
        }

        operator array_t() const {
            return this->to_array();
        }

        operator object_t() const {
            return this->to_object();
        }

        operator array_t&() {
            return this->as_array();
        }

        operator object_t&() {
            return this->as_object();
        }

     public: // Access child element. Throw std::out_of_range if not exist.
        json& operator[](size_t index);

        json& operator[](const std::string& key);

        json& operator[](const char* key) {
            return (*this)[std::string{key}];
        }

     public: // Access child element. Create if not exist.
        json& operator()(size_t index);

        json& operator()(const std::string& key);

        json& operator()(const char* key) {
            return (*this)(std::string{key});
        }

     public:
        bool operator==(const json& other) const;

     public:
        // The implementation details. Wrapped to minimise interface.
        data_t data;
    };

    class json_parse_error :
      public std::domain_error {
     public:
        explicit json_parse_error(const std::string& what) :
          domain_error(what) {}
    };

    namespace is {
        inline bool null(const json& v) {
            return v.type() == json::content_type::null;
        }

        inline bool boolean(const json& v) {
            return v.type() == json::content_type::boolean;
        }

        inline bool number(const json& v) {
            return v.type() == json::content_type::number;
        }

        inline bool string(const json& v) {
            return v.type() == json::content_type::string;
        }

        inline bool array(const json& v) {
            return v.type() == json::content_type::array;
        }

        inline bool object(const json& v) {
            return v.type() == json::content_type::object;
        }
    }
}
