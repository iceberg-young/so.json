#ifndef INCLUDE_SO_JSON_PARSER_ONCE_FLAG
#define INCLUDE_SO_JSON_PARSER_ONCE_FLAG

#include "json.hpp"

namespace so {
    enum class json_token :
      char;

    class json_parser {
     public:
        using literal_t = std::string::const_iterator;

        static json run(literal_t& begin);

     protected:
        json_parser(literal_t& begin) :
          begin(begin),
          iterator(begin) {}

        // Iterator information for debug.
        std::string location();

     protected:
        // Create cascade node.
        json::data_t cascade(json_token t);

        // Create a node start from the iterator.
        json::data_t factory(json_token t);

        // Create children for an array node.
        void fill_children(json::array_t& array);

        // Create children for an object node.
        void fill_children(json::object_t& object);

        // Guess type of next node.
        json_token next();

        // Skip value-separator.
        json_token next_peer(json_token end);

        // Move iterator over the expected literals.
        void pass_literals(const std::string& expected);

        double parse_number();

        std::string parse_string();

        char pick(char& c);

     private:
        const literal_t begin;

        literal_t& iterator;
    };
}

#endif//INCLUDE_SO_JSON_PARSER_ONCE_FLAG
