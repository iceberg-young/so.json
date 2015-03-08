#include "json_array.hpp"

namespace so {
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
            json_array::set(this->data, value);
        }
        return *this;
    }

    json& json::be_array(array_t&& value) {
        if (this->data->type != content_type::array) {
            this->data = data_t{new json_array{std::move(value)}};
        }
        else {
            json_array::set(this->data, std::move(value));
        }
        return *this;
    }

    json::array_t json::to_array() const {
        return this->data->to_array();
    }

    json::array_t& json::as_array() {
        return json_array::get(this->data);
    }

    json& json::operator[](size_t index) {
        return this->data->type == content_type::object
          ? (*this)[std::to_string(index)]
          : json_array::get(this->data).at(index);
    }

    json& json::operator()(size_t index) {
        switch (this->data->type) {
            case content_type::object: {
                return (*this)(std::to_string(index));
            }
            case content_type::null: {
                this->be_array(array_t(index + 1));
                // Continue with default.
            }
            default: {
                auto& array = json_array::get(this->data);
                if (index >= array.size()) {
                    array.resize(index + 1);
                }
                return array[index];
            }
        }
    }

    std::string json_array::to_string() const {
        std::string s;
        if (not this->value.empty()) {
            auto e = --this->value.end();
            for (auto i = this->value.begin(); i != e; ++i) {
                (s += i->data->to_string()) += ',';
            }
            s += e->data->to_string();
        }
        return s;
    }

    json::object_t json_array::to_object() {
        json::object_t o;
        int i = 0;
        for (auto& v : this->value) {
            o[std::to_string(i++)] = v;
        }
        return o;
    }

    void json_array::stringify(std::string& target) const {
        target += '[';
        if (not this->value.empty()) {
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
