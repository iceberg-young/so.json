#ifndef INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG

#include <functional>
#include <string>
#include "cursor.hpp"

namespace singularity {
    class lexer
    {
    public:
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
            done = '.',
        };

    public:
        using callback_t = std::function<void(token, sci_t, sci_t)>;

    public:
        lexer(callback_t callback) :
          callback(callback),
          parser(&lexer::parse_value) {
        }

    public:
        void parse(const std::string &text);

    protected:
        void parse_value(cursor &cursor);

        void parse_literal(cursor &cursor, const std::string &expected);

        void parse_number(cursor &cursor);

        void parse_string(cursor &cursor);

    private:
        callback_t callback;

        void (lexer::*parser)(cursor &);
    };
}

#endif//INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG
