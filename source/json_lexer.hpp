#ifndef INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG

#include "cursor.hpp"

namespace singularity {
    class json_lexer
    {
    public:
        enum class token :
          char
        {
            space = 0,
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

    public:
        /// @param in[out] first
        /// @param out last
        token static parse(cursor &first, cursor &last);

    protected:
        token static parse_value(cursor &cursor);

        token static parse_literal(cursor &cursor, const std::string &expected);

        token static parse_number(cursor &cursor);

        token static parse_string(cursor &cursor);
    };
}

#endif//INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG
