#include "json_number.hpp"

namespace so {
    json::json(double value) :
      data(new json_number{value}) {
    }

    json& json::be_number(double value) {
        if (this->data->type != content_type::number) {
            this->data = data_t{new json_number{value}};
        }
        else {
            json_number::set(this->data, value);
        }
        return *this;
    }

    double json::to_number() const {
        return this->data->to_number();
    }

    std::string json_number::to_string() const {
        std::string s;
        stringify(s);
        return s;
    }

    void json_number::stringify(std::string& target) const {
        char buffer[24];
        std::snprintf(buffer, sizeof(buffer), "%.17g", this->value);
        target += buffer;
    }
}
