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

        using iterator_t = std::string::const_iterator;

    public:
        json_decode(iterator_t& i) :
          begin(i),
          iterator(i) {
        }

    public:
        json run() {
            --this->iterator;
            return this->cascade(this->next());
        }

    protected:
        // Cascade create node.
        json cascade(token t);

        // Create a node start from the iterator.
        json create(token t);

        // Create children for an array node.
        void fill_children(json::array_t& array);

        // Create children for an object node.
        void fill_children(json::object_t& object);

        // Move iterator over the expected literals.
        void pass_literals(const std::string& expected);

        double parse_number();

    protected:
        // Iterator information for debug.
        std::string dump();

        // Guess type of next node.
        token next();

        // Check value separator take post.
        bool separated(token t, bool& s);

    private:
        const iterator_t begin;

        iterator_t& iterator;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_LEXER_ONCE_FLAG
