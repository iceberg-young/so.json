#ifndef INCLUDE_SINGULARITY_JSON_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_ONCE_FLAG

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace singularity {
    // Representation of RFC-7159 specified object.
    class json
    {
    public:
        enum class content_type
        {
            null,
            boolean,
            number,
            string,
            array,
            object,
        };

    public:
        // Implementation type of content_type::array.
        using array_t = std::vector<json>;

        // Implementation type of content_type::object.
        using object_t = std::map<std::string, json>;

        // Implementation type of internal details.
        using detail_t = std::shared_ptr<class json_data>;

    public:
        // Initialize an empty node.
        json(content_type type = content_type::null) noexcept;

        // Clone from the other node.
        json(const json &other);

        // Steal from the other node.
        json(json &&other);

    public: // Initialize by value.
        json(bool value);

        json(int value);

        json(double value);

        json(const std::string &value);

        json(std::string &&value);

        json(const char *value) :
          json(std::string{value}) {
        }

        json(const array_t &value);

        json(array_t &&value);

        json(const object_t &value);

        json(object_t &&value);

    public:
        json &operator=(const json &other);

        json &operator=(json &&other);

    public:
        // Initialize from a JSON text.
        json static parse(const std::string &text);

        // Get corresponding JSON text.
        std::string stringify() const noexcept;

        // Get node type.
        content_type type() const noexcept;

    public: // Change node type (by value). Return *this.
        json &be(content_type type);

        json &be_boolean(bool value);

        json &be_number(double value);

        json &be_string(const std::string &value);

        json &be_string(std::string &&value);

        json &be_array(const array_t &value);

        json &be_array(array_t &&value);

        json &be_object(const object_t &value);

        json &be_object(object_t &&value);

    public: // Shortcuts for changing node type. Return *this.
        json &operator=(std::nullptr_t) {
            return this->be(content_type::null);
        }

        json &operator=(bool value) {
            return this->be_boolean(value);
        }

        json &operator=(double value) {
            return this->be_number(value);
        }

        json &operator=(int value) {
            return this->be_number(value);
        }

        json &operator=(const std::string &value) {
            return this->be_string(value);
        }

        json &operator=(std::string &&value) {
            return this->be_string(std::move(value));
        }

        json &operator=(const char *value) {
            return this->be_string(std::string(value));
        }

        json &operator=(const array_t &value) {
            return this->be_array(value);
        }

        json &operator=(array_t &&value) {
            return this->be_array(std::move(value));
        }

        json &operator=(const object_t &value) {
            return this->be_object(value);
        }

        json &operator=(object_t &&value) {
            return this->be_object(std::move(value));
        }

    public: // Get content value, may throw std::bad_cast if type mismatch.
        bool to_boolean() const;

        double to_number() const;

        std::string to_string() const;

        array_t to_array() const;

        object_t to_object() const;

    public:
        array_t &as_array();

        object_t &as_object();

    public: // Shortcuts for getting content value.
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

    public:
        operator array_t &() {
            return this->as_array();
        }

        operator object_t &() {
            return this->as_object();
        }

    private:
        // The implementation details. Wrapped to minimise interface.
        detail_t data;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_ONCE_FLAG
