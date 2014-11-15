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
        json static create(json_lexer::token token, const cursor &first, const cursor &last);

        std::string static unescape(const cursor &first, const cursor &last);

        void static fill_array(json &array, const cursor &first, const cursor &last);

        void static fill_object(json &object, const cursor &first, const cursor &last);
    };
}

#endif//INCLUDE_SINGULARITY_JSON_BUILDER_ONCE_FLAG
