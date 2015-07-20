#include "json_object.hpp"
#include <limits>

namespace so {
    namespace {
        void append_pair(
          const std::string& name,
          const json& value,
          std::string& target,
          const std::string& pad
        ) {
            target += '"';
            json_data::escape(name, target);
            target += "\":";
            if (not pad.empty()) {
                target += ' ';
            }
            value.data->stringify(target, pad);
        }
    }

    json::json(const object_t& value) :
      data(std::make_shared<json_object>(value)) {}

    json::json(object_t&& value) :
      data(std::make_shared<json_object>(std::move(value))) {}

    json& json::be_object(const object_t& value) {
        if (this->data->type != content_type::object) {
            this->data = std::make_shared<json_object>(value);
        }
        else {
            json_object::set(this->data, value);
        }
        return *this;
    }

    json& json::be_object(object_t&& value) {
        if (this->data->type != content_type::object) {
            this->data = std::make_shared<json_object>(std::move(value));
        }
        else {
            json_object::set(this->data, std::move(value));
        }
        return *this;
    }

    json::object_t json::to_object() const {
        return this->data->to_object();
    }

    json::object_t& json::as_object() {
        return json_object::get(this->data);
    }

    json& json::operator[](const std::string& key) {
        return this->data->type == content_type::array
          ? (*this)[std::stoul(key)]
          : json_object::get(this->data).at(key);
    }

    json& json::operator()(const std::string& key) {
        switch (this->data->type) {
            case content_type::array: {
                return (*this)(std::stoul(key));
            }
            case content_type::null: {
                this->be_object(object_t{});
                // Continue with default.
            }
            default: {
                return json_object::get(this->data)[key];
            }
        }
    }

    double json_object::to_number() const {
        return this->value.empty()
          ? std::numeric_limits<double>::quiet_NaN()
          : (double) this->value.begin()->second;
    };

    std::string json_object::to_string() const {
        std::string s;
        for (auto& v : this->value) {
            s += '[' + v.second.type_name() + ' ' + v.first + "]\n";
            s += v.second.to_string() + '\n';
        }
        return s;
    }

    json::array_t json_object::to_array() const {
        json::array_t a;
        a.reserve(this->value.size());
        for (auto& v : this->value) {
            a.push_back(v.second);
        }
        return a;
    }

    void json_object::stringify(std::string& target, const std::string& indent) const {
        target += '{';
        if (not this->value.empty()) {
            auto e = --this->value.end();
            auto pad = indent.empty() ? indent : indent + '\t';
            for (auto i = this->value.begin(); i != e; ++i) {
                target += pad;
                append_pair(i->first, i->second, target, pad);
                target += ',';
            }
            target += pad;
            append_pair(e->first, e->second, target, pad);
            target += indent;
        }
        target += '}';
    }
}
