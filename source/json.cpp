#include "json_data.hpp"
#include "json_parser.hpp"

namespace so {
    json::json(content_type type) :
      data(json_data::factory(type)) {}

    json::json(const json& other) :
      data(other.data->clone()) {}

    json& json::operator=(const json& other) {
        this->data = other.data->clone();
        return *this;
    }

    json json::parse(json_parser::literal_t& iterator) {
        return json_parser::run(iterator);
    }

    std::string json::stringify(bool pretty) const {
        std::string target;
        this->data->stringify(target, pretty ? "\n" : "");
        return target;
    }

    json::content_type json::type() const {
        return this->data->type;
    }

    std::string json::type_name() const {
        switch (this->data->type) {
            case content_type::null: {
                return "null";
            }
            case content_type::boolean: {
                return "boolean";
            }
            case content_type::number: {
                return "number";
            }
            case content_type::string: {
                return "string";
            }
            case content_type::array: {
                return "array";
            }
            case content_type::object: {
                return "object";
            }
        }
        throw this->data->type;
    }
}
