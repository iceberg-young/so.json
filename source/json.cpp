#include "json.hpp"
#include "json_data.hpp"

namespace singularity {
    json::json(content_t type) noexcept :
      data(json_data::factory(type)) {
    }

    json::json(const json &other) :
      data(other.data->clone()) {
    }

    json::json(json &&other) {
        this->data.swap(other.data);
    }

    json::json(bool value) :
      data(json_data::factory(content_t::boolean)) {
        this->data->be_boolean(value);
    }

    json::json(int value) :
      data(json_data::factory(content_t::number)) {
        this->data->be_number(value);
    }

    json::json(double value) :
      data(json_data::factory(content_t::number)) {
        this->data->be_number(value);
    }

    json::json(const std::string &value) :
      data(json_data::factory(content_t::string)) {
        this->data->be_string(value);
    }

    json::json(std::string &&value) :
      data(json_data::factory(content_t::string)) {
        this->data->be_string(std::move(value));
    }

    json::json(const array_t &value) :
      data(json_data::factory(content_t::array)) {
        this->data->be_array(value);
    }

    json::json(array_t &&value) :
      data(json_data::factory(content_t::array)) {
        this->data->be_array(std::move(value));
    }

    json::json(const object_t &value) :
      data(json_data::factory(content_t::object)) {
        this->data->be_object(value);
    }

    json::json(object_t &&value) :
      data(json_data::factory(content_t::object)) {
        this->data->be_object(std::move(value));
    }

    json &json::operator=(const json &other) {
        this->data = other.data->clone();
        return *this;
    }

    json &json::operator=(json &&other) {
        this->data.swap(other.data);
        return *this;
    }

    json json::parse(const std::string &text) {
        // TODO
        return json{};
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

    json &json::be_number(double value) {
        this->be(content_t::number).data->be_number(value);
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

    double json::to_number() const {
        return this->data->to_number();
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
