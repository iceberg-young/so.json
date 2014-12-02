#ifndef INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG

#include "json.hpp"

namespace singularity {
    namespace json_uh {
        using sci_t = std::string::const_iterator;

        class cursor :
          public sci_t
        {
        public:
            cursor(sci_t &&begin, const sci_t &end) :
              sci_t(begin),
              begin(begin),
              end(end) {
            }

        public:
            cursor &operator++() {
                if (*this == this->end) {
                    throw std::out_of_range{"Already reached the end."};
                }
                sci_t::operator++();
                return *this;
            }

            cursor &operator=(const cursor &other) {
                *static_cast<sci_t *>(this) = other;
                return *this;
            }

        public:
            long position() const {
                return *static_cast<const sci_t *>(this) - this->begin;
            }

        private:
            const sci_t &begin;

            const sci_t &end;
        };

        enum class token :
          char
        {
            null = 'n',
            boolean_false = 'f',
            boolean_true = 't',
            number = '-',
            string = '"',
            array_begin = '[',
            array_end = ']',
            object_begin = '{',
            object_end = '}',
            name_separator = ':',
            value_separator = ',',
        };

        json::pointer_t decode(const cursor &c);
    };
}

#endif//INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG
