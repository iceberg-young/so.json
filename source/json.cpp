#include "json.hpp"
#include "json_data.hpp"

using namespace std;

namespace singularity {
    json::json(const std::string &text) {
        // TODO
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

    std::string json::stringify() {
        return "TODO";
    }

    json_type json::type() {
        return this->data->type;
    }

    json &json::be(json_type type) {
        if (this->data->type != type) {
            this->data = json_data::factory(type);
        }
        return *this;
    }

    json &json::be_boolean(bool value) {
        this->be(json_type::boolean).data->be_boolean(value);
        return *this;
    }

    json &json::be_decimal(double value) {
        this->be(json_type::decimal).data->be_decimal(value);
        return *this;
    }

    json &json::be_integer(int value) {
        this->be(json_type::integer).data->be_integer(value);
        return *this;
    }

    json &json::be_string(const std::string &value) {
        this->be(json_type::string).data->be_string(value);
        return *this;
    }

    json &json::be_array(const json_array &value) {
        this->be(json_type::array).data->be_array(value);
        return *this;
    }

    json &json::be_object(const json_object &value) {
        this->be(json_type::object).data->be_object(value);
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

    json json::get(size_t index) {
        return this->data->to_array().at(index);
    }

    json json::get(const std::string &key) {
        return this->data->to_object().at(key);
    }

    json &json::set(size_t index, const json &value) {
        auto &array = this->data->to_array();
        if (array.size() > index) {
            array[index] = value;
        }
        else {
            array.reserve(index + 1);
            array.resize(index);
            array.emplace_back(value);
        }
        return *this;
    }

    json &json::set(size_t index, json &&value) {
        auto &array = this->data->to_array();
        if (array.size() > index) {
            array[index] = std::move(value);
        }
        else {
            array.reserve(index + 1);
            array.resize(index);
            array.emplace_back(std::move(value));
        }
        return *this;
    }

    json &json::set(const std::string &key, const json &value) {
        this->data->to_object()[key] = value;
        return *this;
    }

    json &json::set(const std::string &key, json &&value) {
        this->data->to_object()[key] = std::move(value);
        return *this;
    }
}
