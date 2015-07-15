#include "json_number.hpp"
#include <cmath>

namespace so {
    json::json(double value) :
      data(std::make_shared<json_number>(value)) {}

    json& json::be_number(double value) {
        if (this->data->type != content_type::number) {
            this->data = std::make_shared<json_number>(value);
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
        const char* ptr = nullptr;
        if (std::isnan(this->value)) {
            ptr = R"("NaN")";
        }
        else if (std::isinf(this->value)) {
            ptr = this->value > 0 ? R"("Infinity")" : R"("-Infinity")";
        }
        else {
            char buffer[sizeof("-0.1234567890123456e+308")];
            snprintf(buffer, sizeof(buffer), "%.16g", this->value);
            ptr = buffer;
        }
        return std::string{ptr};
    }
}
