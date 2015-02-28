#ifndef INCLUDE_SO_JSON_LEXER_ONCE_FLAG
#define INCLUDE_SO_JSON_LEXER_ONCE_FLAG

#include "json.hpp"

namespace so {
    class json_decode
    {
    public:
        static json run(json::literal_t& begin);

    protected:
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

    protected:
        json_decode(json::literal_t& begin) :
          begin(begin),
          iterator(begin) {
            // Counteract the first forward in next().
            --this->iterator;
        }

        ~json_decode() {
            // Move beyond the end.
            ++this->iterator;
        }

        // Iterator information for debug.
        std::string dump();

    protected:
        // Create cascade node.
        json::data_t cascade(token t);

        // Create a node start from the iterator.
        json::data_t factory(token t);

        // Create children for an array node.
        void fill_children(json::array_t& array);

        // Create children for an object node.
        void fill_children(json::object_t& object);

        char go_forward();

        // Guess type of next node.
        token next();

        // Skip value-separator.
        bool next(token end, bool& initial, token& child);

        // Move iterator over the expected literals.
        void pass_literals(const std::string& expected);

        double parse_number();

        std::string parse_string();

    private:
        const json::literal_t begin;

        json::literal_t& iterator;
    };
}

#endif//INCLUDE_SO_JSON_LEXER_ONCE_FLAG
