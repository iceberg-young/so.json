#ifndef INCLUDE_SINGULARITY_JSON_BUILDER_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_BUILDER_ONCE_FLAG

#include "json.hpp"
#include "cursor.hpp"
#include "json_lexer.hpp"

namespace singularity {
    class json_builder
    {
    public:
        json static build(const cursor &text);

    protected:
        json static cascade(json_lexer::token token, cursor &first, cursor &last);

        json static create(json_lexer::token token, const cursor &first, const cursor &last);

        std::string static unescape(const cursor &first, const cursor &last);

        void static fill_array(json &array, cursor &first, cursor &last);

        void static fill_object(json &object, cursor &first, cursor &last);

        bool static pass_comma(json_lexer::token token, bool &separated);

        void static assert(json_lexer::token expected, json_lexer::token real);
    };
}

#endif//INCLUDE_SINGULARITY_JSON_BUILDER_ONCE_FLAG
