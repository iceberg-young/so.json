/**
 * @copyright 2015 Iceberg YOUNG
 * @license GNU Lesser General Public License version 3
 */

#include "json_null.hpp"
#include "json_boolean.hpp"
#include "json_number.hpp"
#include "json_string.hpp"
#include "json_array.hpp"
#include "json_object.hpp"
#include "utf.hpp"

namespace so {
    json& json::be(content_type type) {
        if (type == this->data->type) return *this;

        switch (type) {
            case content_type::null: {
                return this->be_null();
            }
            case content_type::boolean: {
                return this->be_boolean(this->data->to_boolean());
            }
            case content_type::number: {
                return this->be_number(this->data->to_number());
            }
            case content_type::string: {
                return this->be_string(this->data->to_string());
            }
            case content_type::array: {
                return this->be_array(this->data->to_array());
            }
            case content_type::object: {
                return this->be_object(this->data->to_object());
            }
        }
        throw type;
    }

    bool json::operator==(const json& other) const {
        auto type = this->data->type;
        if (type != other.data->type) return false;

        switch (type) {
            case content_type::null: {
                return true;
            }
            case content_type::boolean: {
                return this->data->to_boolean() == other.data->to_boolean();
            }
            case content_type::number: {
                return this->data->to_number() == other.data->to_number();
            }
            case content_type::string: {
                return json_string::get(this->data) == json_string::get(other.data);
            }
            case content_type::array: {
                return json_array::get(this->data) == json_array::get(other.data);
            }
            case content_type::object: {
                return json_object::get(this->data) == json_object::get(other.data);
            }
        }
        throw type;
    }

    const std::string json_data::esc_label{"bfnrt"};
    const std::string json_data::esc_value{"\b\f\n\r\t"};

    void json_data::escape(const std::string& source, std::string& target) {
        for (char c : source) {
            if (c >= 0 and c < 0x20) {
                auto pos = esc_value.find(c);
                if (pos != std::string::npos) {
                    target += '\\';
                    target += esc_label[pos];
                }
                else {
                    target += utf::escape(std::u16string{char16_t(c)});
                }
            }
            else {
                if (c == '"' or c == '\\') {
                    target += '\\';
                }
                target += c;
            }
        }
    }

    json::data_t json_data::factory(json::content_type type) {
        switch (type) {
            case json::content_type::null: {
                return json_null::solo;
            }
            case json::content_type::boolean: {
                return json_false::solo;
            }
            case json::content_type::number: {
                return std::make_shared<json_number>();
            }
            case json::content_type::string: {
                return std::make_shared<json_string>();
            }
            case json::content_type::array: {
                return std::make_shared<json_array>();
            }
            case json::content_type::object: {
                return std::make_shared<json_object>();
            }
        }
        throw type;
    }
}
