#ifndef INCLUDE_SINGULARITY_JSON_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_ONCE_FLAG

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace singularity {
    enum class json_type
    {
        undefined,
        null,
        boolean,
        decimal,
        integer,
        string,
        array,
        object,
    };

    using json_array = std::vector<class json>;
    using json_object = std::map<std::string, class json>;
    using json_detail = std::shared_ptr<class json_data>;

    class json
    {
    public:
        json(const std::string &text);

        json(json_type type = json_type::undefined);

        json(const json &other);

        json(json &&other);

        ~json() {
        }

    public:
        json &operator=(const json &other);

        json &operator=(json &&other);

    public:
        json &be(json_type type);

        json &be_boolean(bool value);

        json &be_decimal(double value);

        json &be_integer(int value);

        json &be_string(const std::string &value);

        json &be_array(const json_array &value);

        json &be_object(const json_object &value);

    public:
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

        json &operator=(const char *value) {
            return this->be_string(value);
        }

        json &operator=(const json_array &value) {
            return this->be_array(value);
        }

        json &operator=(const json_object &value) {
            return this->be_object(value);
        }

    public:
        bool to_boolean() const;

        double to_decimal() const;

        int to_integer() const;

        std::string to_string() const;

        json_array to_array() const;

        json_object to_object() const;

    public:
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

    public:
        json_type type();

        std::string stringify();

    private:
        json_detail data;
    };

    json json_decode(const std::string &text);

    std::string json_encode(const json &node);
}

#endif//INCLUDE_SINGULARITY_JSON_ONCE_FLAG
