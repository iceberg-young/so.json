#include "json_array.hpp"

namespace singularity {
    json::json(const array_t& value) :
      data(new json_array{value}) {
    }

    json::json(array_t&& value) :
      data(new json_array{std::move(value)}) {
    }

    json& json::be_array(const array_t& value) {
        if (this->data->type != content_type::array) {
            this->data = data_t{new json_array{value}};
        }
        else {
            this->data->be_array(value);
        }
        return *this;
    }

    json& json::be_array(array_t&& value) {
        if (this->data->type != content_type::array) {
            this->data = data_t{new json_array{std::move(value)}};
        }
        else {
            this->data->be_array(std::move(value));
        }
        return *this;
    }

    json::array_t json::to_array() const {
        return this->data->to_array();
    }

    json::array_t& json::as_array() {
        return this->data->to_array();
    }

    json& json::operator[](size_t index) {
        return this->data->type == content_type::object
          ? (*this)[std::to_string(index)]
          : this->data->to_array().at(index);
    }

    json& json::operator()(size_t index) {
        switch (this->data->type) {
            case content_type::object:
                return (*this)(std::to_string(index));

            case content_type::null:
                this->be_array(array_t(index + 1));

            default:
                auto& array = this->data->to_array();
                if (index >= array.size()) {
                    array.resize(index + 1);
                }
                return array[index];
        }
    }

    std::string json_array::to_string() const {
        std::string s;
        if (!this->value.empty()) {
            auto e = --this->value.end();
            for (auto i = this->value.begin(); i != e; ++i) {
                (s += i->data->to_string()) += ',';
            }
            s += e->data->to_string();
        }
        return s;
    }

    void json_array::stringify(std::string& target) const {
        target += '[';
        if (!this->value.empty()) {
            auto e = --this->value.end();
            for (auto i = this->value.begin(); i != e; ++i) {
                i->data->stringify(target);
                target += ',';
            }
            e->data->stringify(target);
        }
        target += ']';
    }
}
