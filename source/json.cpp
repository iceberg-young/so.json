#include "json_data.hpp"

namespace singularity {
    json::json(content_type type) :
      data(json_data::factory(type)) {
    }

    json::json(const json& other) :
      data(other.data->clone()) {
    }

    json::json(json&& other) {
        this->data.swap(other.data);
    }

    json& json::operator=(const json& other) {
        this->data = other.data->clone();
        return *this;
    }

    json& json::operator=(json&& other) {
        this->data.swap(other.data);
        return *this;
    }

    json::pointer_t json::parse(const std::string& text) {
        auto iterator = text.cbegin();
        return json_data::decode(iterator);
    }

    json::pointer_t json::parse(json_data::cursor& iterator) {
        return json_data::decode(iterator);
    }

    std::string json::stringify() const {
        std::string target;
        this->data->stringify(target);
        return target;
    }

    json::content_type json::type() const {
        return this->data->type;
    }

    json& json::be(content_type type) {
        if (this->data->type != type) {
            this->data = json_data::factory(type);
        }
        return *this;
    }
}
