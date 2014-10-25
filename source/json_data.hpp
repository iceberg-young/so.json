#ifndef INCLUDE_SINGULARITY_JSON_DATA_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_DATA_ONCE_FLAG

#include <typeinfo>
#include "json.hpp"

namespace singularity {
    class json_data :
      public std::enable_shared_from_this<json_data>
    {
    public:
        static json_detail factory(json_type type);

    public:
        json_data(json_type type) :
          type(type) {
        }

        virtual ~json_data() {
        }

    public:
        virtual void be_boolean(bool value) {
            throw std::bad_cast{};
        }

        virtual void be_decimal(double value) {
            throw std::bad_cast{};
        }

        virtual void be_integer(int value) {
            throw std::bad_cast{};
        }

        virtual void be_string(const std::string &value) {
            throw std::bad_cast{};
        }

        virtual void be_array(const json_array &value) {
            throw std::bad_cast{};
        }

        virtual void be_object(const json_object &value) {
            throw std::bad_cast{};
        }

    public:
        virtual bool to_boolean() const {
            throw std::bad_cast{};
        }

        virtual double to_decimal() const {
            throw std::bad_cast{};
        }

        virtual int to_integer() const {
            throw std::bad_cast{};
        }

        virtual std::string to_string() const {
            throw std::bad_cast{};
        }

        virtual json_array to_array() const {
            throw std::bad_cast{};
        }

        virtual json_object to_object() const {
            throw std::bad_cast{};
        }

    public:
        virtual json_detail clone() = 0;

    public:
        const json_type type;
    };

    template<json_type T>
    class json_node :
      public json_data
    {
    public:
        json_node() :
          json_data(T) {
        }

    public:
        json_detail clone() override {
            return json_detail{new json_node{*this}};
        }
    };
}

#endif//INCLUDE_SINGULARITY_JSON_DATA_ONCE_FLAG
