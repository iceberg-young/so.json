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

    json& json::be(content_type type) {
        if (type == this->data->type) return *this;

        switch (type) {
            case content_type::null:
                return this->be_null();

            case content_type::boolean:
                return this->be_boolean(this->data->to_boolean());

            case content_type::number:
                return this->be_number(this->data->to_number());

            case content_type::string:
                return this->be_string(this->data->to_string());

            case content_type::array:
                return this->be_array(this->data->to_array());

            case content_type::object:
                return this->be_object(this->data->to_object());
        }
    }
}
