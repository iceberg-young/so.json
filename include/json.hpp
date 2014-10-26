#ifndef INCLUDE_SINGULARITY_JSON_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_ONCE_FLAG

#include <map>
#include <tuple>
#include <memory>
#include <string>
#include <vector>
#include <functional>

namespace singularity {
    // Extended implementation of ECMA-404.
    class json
    {
    public:
        enum class content_type
        {
            null,
            boolean,
            decimal,
            integer,
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
        // Initialize from a JSON string.
        json(const std::string &text);

        // Initialize an empty node.
        json(content_type type = content_type::null) noexcept;

        // Clone from the other node.
        json(const json &other);

        // Steal from the other node.
        json(json &&other);

    public:
        json &operator=(const json &other);

        json &operator=(json &&other);

    public:
        // Get corresponding JSON string representation.
        std::string stringify() const noexcept;

        // Get node type.
        content_type type() const noexcept;

    public: // Change node type (by value). Return *this.
        json &be(content_type type);

        json &be_boolean(bool value);

        json &be_decimal(double value);

        json &be_integer(int value);

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
            return this->be_decimal(value);
        }

        json &operator=(int value) {
            return this->be_integer(value);
        }

        json &operator=(const std::string &value) {
            return this->be_string(value);
        }

        json &operator=(std::string &&value) {
            return this->be_string(std::move(value));
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

        double to_decimal() const;

        int to_integer() const;

        std::string to_string() const;

        array_t to_array() const;

        object_t to_object() const;

    public: // Shortcuts for getting content value.
        operator bool() const {
            return this->to_boolean();
        }

        operator double() const {
            return this->to_decimal();
        }

        operator int() const {
            return this->to_integer();
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

    public: // *Get* an element from array|object.
        json get(size_t index) const;

        json get(const std::string &key) const;

    public: // *Set* an element to array|object. Return *this.
        json &set(size_t index, const json &value);

        json &set(size_t index, json &&value);

        json &set(const std::string &key, const json &value);

        json &set(const std::string &key, json &&value);

    public:
        // Iterating over json of array|object.
        class iterator
        {
        public:
            using element_t = std::tuple<size_t, json *, std::string>;
            using forward_t = std::function<void(element_t &)>;

        public:
            iterator(forward_t forward);

        public:
            iterator &operator++() {
                this->forward(this->current);
                return *this;
            }

        public:
            element_t &operator*() {
                return this->current;
            }

        public:
            bool operator!=(const iterator &other) const {
                return this->current != other.current;
            }

        private:
            forward_t forward;

        private:
            element_t current;
        };

    public:
        iterator begin();

        iterator end();

    private:
        // The implementation details. Wrapped to minimise interface.
        detail_t data;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_ONCE_FLAG
