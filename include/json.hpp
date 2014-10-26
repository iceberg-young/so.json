#ifndef INCLUDE_SINGULARITY_JSON_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_ONCE_FLAG

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace singularity {
    // Possible content types.
    enum class json_type
    {
        null,
        boolean,
        decimal,
        integer,
        string,
        array,
        object,
    };

    // Implementation type of json_type::array.
    using json_array = std::vector<class json>;

    // Implementation type of json_type::object.
    using json_object = std::map<std::string, class json>;

    // Implementation type of internal details.
    using json_detail = std::shared_ptr<class json_data>;

    // Extended implementation of ECMA-404.
    class json
    {
    public:
        // Initialize from a JSON string.
        json(const std::string &text);

        // Initialize an empty node.
        json(json_type type = json_type::null);

        // Clone from the other node.
        json(const json &other);

        // Steal from the other node.
        json(json &&other);

    public:
        json &operator=(const json &other);

        json &operator=(json &&other);

    public:
        // Get corresponding JSON string representation.
        std::string stringify();

        // Get node type.
        json_type type();

    public: // Change node type (by value). Return *this.
        json &be(json_type type);

        json &be_boolean(bool value);

        json &be_decimal(double value);

        json &be_integer(int value);

        json &be_string(const std::string &value);

        json &be_array(const json_array &value);

        json &be_object(const json_object &value);

    public: // Shortcuts for changing node type. Return *this.
        json &operator=(std::nullptr_t) {
            return this->be(json_type::null);
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

        json &operator=(const json_array &value) {
            return this->be_array(value);
        }

        json &operator=(const json_object &value) {
            return this->be_object(value);
        }

    public: // Get content value, may throw std::bad_cast if type mismatch.
        bool to_boolean() const;

        double to_decimal() const;

        int to_integer() const;

        std::string to_string() const;

        json_array to_array() const;

        json_object to_object() const;

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

        operator json_array() const {
            return this->to_array();
        }

        operator json_object() const {
            return this->to_object();
        }

    public: // *Get* an element from array|object.
        json get(size_t index);

        json get(const std::string &key);

    public: // *Set* an element to array|object. Return *this.
        json &set(size_t index, const json &value);

        json &set(size_t index, json &&value);

        json &set(const std::string &key, const json &value);

        json &set(const std::string &key, json &&value);

    private:
        // The implementation details. Wrapped to minimise interface.
        json_detail data;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_ONCE_FLAG
