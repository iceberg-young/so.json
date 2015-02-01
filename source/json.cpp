#include "json_data.hpp"
#include "json_decode.hpp"

namespace singularity {
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

    json json::parse(literal_t& iterator) {
        json_decode decoder(iterator);
        return decoder.run();
    }

    std::string json::stringify() const {
        std::string target;
        this->data->stringify(target);
        return target;
    }

    json::content_type json::type() const {
        return this->data->type;
    }
}
