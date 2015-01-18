#include "json_object.hpp"

namespace singularity {
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
            this->data->be_object(value);
        }
        return *this;
    }

    json& json::be_object(object_t&& value) {
        if (this->data->type != content_type::object) {
            this->data = data_t{new json_object{std::move(value)}};
        }
        else {
            this->data->be_object(std::move(value));
        }
        return *this;
    }

    json::object_t json::to_object() const {
        return this->data->to_object();
    }

    json::object_t& json::as_object() {
        return this->data->to_object();
    }

    json& json::operator[](const std::string& key) {
        return this->data->to_object().at(key);
    }

    json& json::operator()(const std::string& key) {
        if (this->data->type == content_type::null) {
            this->be(content_type::object);
        }
        auto& object = this->data->to_object();
        try {
            return object.at(key);
        }
        catch (std::out_of_range) {
            return object.emplace(std::make_pair(key, nullptr)).first->second;
        }
    }

    void json_object::stringify(std::string& target) const {
        target += '{';
        if (!this->value.empty()) {
            auto e = --this->value.end();
            for (auto i = this->value.begin(); i != e; ++i) {
                append_pair(i->first, i->second, target);
                target += ',';
            }
            append_pair(e->first, e->second, target);
        }
        target += '}';
    }

    void json_object::append_pair(const std::string& name, const json& value, std::string& target) {
        target += '"';
        escape(name, target);
        target += "\":";
        value.data->stringify(target);
    }
}
