#ifndef INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG

#include "json.hpp"

namespace singularity {
    class json_decode
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
        };

    public:
        json_decode(json::literal_t& begin) :
          begin(begin),
          iterator(begin) {
        }

    public:
        json run();

    protected:
        // Cascade create node.
        json::data_t cascade(token t);

        // Create a node start from the iterator.
        json::data_t factory(token t);

        // Create children for an array node.
        void fill_children(json::array_t& array);

        // Create children for an object node.
        void fill_children(json::object_t& object);

    protected:
        // Move iterator over the expected literals.
        void pass_literals(const std::string& expected);

        double parse_number();

        std::string parse_string();

    protected:
        // Iterator information for debug.
        std::string dump();

        // Guess type of next node.
        token next();

        // Check value separator take post.
        bool separator(token t, bool& s);

    private:
        const json::literal_t begin;

        json::literal_t& iterator;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG
