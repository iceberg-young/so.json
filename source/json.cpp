#include "json.hpp"
#include "json_data.hpp"

namespace singularity {
    json::json(const std::string &text) {
        // TODO
    }

    json::json(content_t type) noexcept :
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

    std::string json::stringify() const noexcept {
        return this->data->stringify();
    }

    content_t json::type() const noexcept {
        return this->data->type;
    }

    json &json::be(content_t type) {
        if (this->data->type != type) {
            this->data = json_data::factory(type);
        }
        return *this;
    }

    json &json::be_boolean(bool value) {
        this->be(content_t::boolean).data->be_boolean(value);
        return *this;
    }

    json &json::be_decimal(double value) {
        this->be(content_t::decimal).data->be_decimal(value);
        return *this;
    }

    json &json::be_integer(int value) {
        this->be(content_t::integer).data->be_integer(value);
        return *this;
    }

    json &json::be_string(const std::string &value) {
        this->be(content_t::string).data->be_string(value);
        return *this;
    }

    json &json::be_string(std::string &&value) {
        this->be(content_t::string).data->be_string(std::move(value));
        return *this;
    }

    json &json::be_array(const array_t &value) {
        this->be(content_t::array).data->be_array(value);
        return *this;
    }

    json &json::be_array(array_t &&value) {
        this->be(content_t::array).data->be_array(std::move(value));
        return *this;
    }

    json &json::be_object(const object_t &value) {
        this->be(content_t::object).data->be_object(value);
        return *this;
    }

    json &json::be_object(object_t &&value) {
        this->be(content_t::object).data->be_object(std::move(value));
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

    array_t json::to_array() const {
        return this->data->to_array();
    }

    object_t json::to_object() const {
        return this->data->to_object();
    }

    array_t &json::as_array() {
        return this->data->to_array();
    }

    object_t &json::as_object() {
        return this->data->to_object();
    }
}
