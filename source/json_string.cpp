#include "json_string.hpp"

namespace so {
    json::json(const std::string& value) :
      data(new json_string{value}) {
    }

    json::json(std::string&& value) :
      data(new json_string{std::move(value)}) {
    }

    json& json::be_string(const std::string& value) {
        if (this->data->type != content_type::string) {
            this->data = data_t{new json_string{value}};
        }
        else {
            json_string::set(this->data, value);
        }
        return *this;
    }

    json& json::be_string(std::string&& value) {
        if (this->data->type != content_type::string) {
            this->data = data_t{new json_string{std::move(value)}};
        }
        else {
            json_string::set(this->data, std::move(value));
        }
        return *this;
    }

    std::string json::to_string() const {
        return this->data->to_string();
    }

    void json_string::stringify(std::string& target) const {
        target += '"';
        escape(this->value, target);
        target += '"';
    }
}
