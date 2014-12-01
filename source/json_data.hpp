#ifndef INCLUDE_SINGULARITY_JSON_DATA_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_DATA_ONCE_FLAG

#include <typeinfo>
#include "json.hpp"

namespace singularity {
    namespace json_uh {
        using data_t = json::data_t;
        using array_t = json::array_t;
        using object_t = json::object_t;
        using content_t = json::content_type;

        class data :
          public std::enable_shared_from_this<data>
        {
        public:
            static data_t factory(content_t type);

        public:
            static void escape(const std::string &source, std::string &target);

        public:
            data(content_t type) :
              type(type) {
            }

            virtual ~data() {
            }

        public:
            virtual void be_boolean(bool value) {
                throw std::bad_cast{};
            }

            virtual void be_number(double value) {
                throw std::bad_cast{};
            }

            virtual void be_string(const std::string &value) {
                throw std::bad_cast{};
            }

            virtual void be_string(std::string &&value) {
                throw std::bad_cast{};
            }

            virtual void be_array(const array_t &value) {
                throw std::bad_cast{};
            }

            virtual void be_array(array_t &&value) {
                throw std::bad_cast{};
            }

            virtual void be_object(const object_t &value) {
                throw std::bad_cast{};
            }

            virtual void be_object(object_t &&value) {
                throw std::bad_cast{};
            }

        public:
            virtual bool to_boolean() const {
                throw std::bad_cast{};
            }

            virtual double to_number() const {
                throw std::bad_cast{};
            }

            virtual std::string to_string() const {
                throw std::bad_cast{};
            }

            virtual array_t &to_array() {
                throw std::bad_cast{};
            }

            virtual object_t &to_object() {
                throw std::bad_cast{};
            }

        public:
            virtual void stringify(std::string &target) const {
                target += this->to_string();
            }

        public:
            virtual data_t clone() = 0;

        public:
            const content_t type;
        };

        template<content_t>
        class node :
          public data
        {
            // Not used
        };
    }
}

#endif//INCLUDE_SINGULARITY_JSON_DATA_ONCE_FLAG
