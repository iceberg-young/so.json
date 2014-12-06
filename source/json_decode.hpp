#ifndef INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG

#include "json.hpp"

namespace singularity {
    namespace json_uh {
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

        using cursor = json_data::cursor;

        json::pointer_t cascade(token t, cursor& i);

        token next(cursor& i);
    };
}

#endif//INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG
