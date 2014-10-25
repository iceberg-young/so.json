#include "json.hpp"
#include "json_data.hpp"

using namespace std;

namespace singularity {
    json::json(const std::string &text) {
    }

    json::json(json_type type) :
      data(json_data::factory(type)) {
    }

    json::json(const json &other) :
      data(other.data->clone()) {
    }

    json::json(json &&other) {
        this->data.swap(other.data);
    }

    json &json::operator=(const json &other) {
        this->data = other.data->clone();
        return *this;
    }

    json &json::operator=(json &&other) {
        this->data.swap(other.data);
        return *this;
    }

    json &json::be(json_type type) {
        if (this->data->type != type) {
            this->data = json_data::factory(type);
        }
        return *this;
    }

    json &json::be_boolean(bool value) {
        this->be(json_type::boolean);
        this->data->be_boolean(value);
        return *this;
    }

    json &json::be_decimal(double value) {
        this->be(json_type::decimal);
        this->data->be_decimal(value);
        return *this;
    }

    json &json::be_integer(int value) {
        this->be(json_type::integer);
        this->data->be_integer(value);
        return *this;
    }

    json &json::be_string(const std::string &value) {
        this->be(json_type::string);
        this->data->be_string(value);
        return *this;
    }

    json &json::be_array(const json_array &value) {
        this->be(json_type::array);
        this->data->be_array(value);
        return *this;
    }

    json &json::be_object(const json_object &value) {
        this->be(json_type::object);
        this->data->be_object(value);
        return *this;
    }

    bool json::to_boolean() const {
        return this->data->to_boolean();
    }

    double json::to_decimal() const {
        return this->data->to_decimal();
    }

    int json::to_integer() const {
        return this->data->to_integer();
    }

    std::string json::to_string() const {
        return this->data->to_string();
    }

    json_array json::to_array() const {
        return this->data->to_array();
    }

    json_object json::to_object() const {
        return this->data->to_object();
    }

    json_type json::type() {
        return this->data->type;
    }

    std::string json::stringify() {
        return "";
    }
}
