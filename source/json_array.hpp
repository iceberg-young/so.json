#ifndef INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG

#include <sstream>
#include "json_data.hpp"

namespace singularity {
    template<>
    class json_node<content_t::array> :
      public json_data
    {
    public:
        json_node() :
          json_data(content_t::array) {
        }

    public:
        void be_array(const array_t &value) override {
            this->value = value;
        }

        void be_array(array_t &&value) override {
            this->value.swap(value);
        }

    public:
        array_t &to_array() override {
            return this->value;
        }

    public:
        std::string to_string() const override {
            std::stringstream ss;
            for (auto &i : this->value) {
                ss << ',' << i.to_string();
            }
            return ss.str().substr(1);
        }

    public:
        detail_t clone() override {
            return detail_t{new json_node{*this}};
        }

    private:
        array_t value;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_ARRAY_ONCE_FLAG
