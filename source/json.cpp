#include "json_data.hpp"
#include "json_parser.hpp"

namespace so {
    json::json(content_type type) :
      data(json_data::factory(type)) {
    }

    json::json(const json& other) :
      data(other.data->clone()) {
    }

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
}
