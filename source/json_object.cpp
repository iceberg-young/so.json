#include "json_object.hpp"

namespace so {
    json::json(const object_t& value) :
      data(new json_object{value}) {
    }

    json::json(object_t&& value) :
      data(new json_object{std::move(value)}) {
    }

    json& json::be_object(const object_t& value) {
        if (this->data->type != content_type::object) {
            this->data = data_t{new json_object{value}};
        }
        else {
            json_object::set(this->data, value);
        }
        return *this;
    }

    json& json::be_object(object_t&& value) {
        if (this->data->type != content_type::object) {
            this->data = data_t{new json_object{std::move(value)}};
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
            }
            default: {
                return json_object::get(this->data)[key];
            }
        }
    }

    void json_object::stringify(std::string& target) const {
        target += '{';
        if (not this->value.empty()) {
            auto e = --this->value.end();
            for (auto i = this->value.begin(); i != e; ++i) {
                append_pair(i->first, i->second, target);
                target += ',';
            }
            append_pair(e->first, e->second, target);
        }
        target += '}';
    }

    json::array_t json_object::to_array() {
        json::array_t a;
        a.reserve(this->value.size());
        for (auto& v : this->value) {
            a.push_back(v.second);
        }
        return a;
    }

    void json_object::append_pair(const std::string& name, const json& value, std::string& target) {
        target += '"';
        escape(name, target);
        target += "\":";
        value.data->stringify(target);
    }
}
