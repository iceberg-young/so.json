#include "json_array.hpp"
#include <limits>
#include <iomanip>
#include <sstream>

namespace so {
    json::json(const array_t& value) :
      data(std::make_shared<json_array>(value)) {}

    json::json(array_t&& value) :
      data(std::make_shared<json_array>(std::move(value))) {}

    json& json::be_array(const array_t& value) {
        if (this->data->type != content_type::array) {
            this->data = std::make_shared<json_array>(value);
        }
        else {
            json_array::set(this->data, value);
        }
        return *this;
    }

    json& json::be_array(array_t&& value) {
        if (this->data->type != content_type::array) {
            this->data = std::make_shared<json_array>(std::move(value));
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

    double json_array::to_number() const {
        return this->value.empty()
          ? std::numeric_limits<double>::quiet_NaN()
          : (double) *this->value.begin();
    }

    std::string json_array::to_string() const {
        std::string s;
        for (auto& v : this->value) {
            (s += v.data->to_string()) += ',';
        }
        if (not s.empty()) s.pop_back();
        return s;
    }

    json::object_t json_array::to_object() const {
        json::object_t o;
        auto width = std::to_string(this->value.size() - 1).size();
        int i = 0;
        for (auto& v : this->value) {
            std::ostringstream k;
            k << std::setw(width) << std::setfill('0') << i++;
            o[k.str()] = v;
        }
        return o;
    }

    void json_array::stringify(std::string& target, const std::string& indent) const {
        target += '[';
        if (not this->value.empty()) {
            auto pad = indent.empty() ? indent : indent + '\t';
            for (auto& v : this->value) {
                target += pad;
                v.data->stringify(target, pad);
                target += ',';
            }
            target.pop_back();
            target += indent;
        }
        target += ']';
    }
}
