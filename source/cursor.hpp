#ifndef INCLUDE_SINGULARITY_JSON_CURSOR_ONCE_FLAG
#define INCLUDE_SINGULARITY_JSON_CURSOR_ONCE_FLAG

#include <string>
#include <stdexcept>

namespace singularity {
    using sci_t = std::string::const_iterator;

    class cursor :
      public sci_t
    {
    public:
        cursor(sci_t &&begin, const sci_t &end) :
          sci_t(begin),
          end(end) {
        }

    public:
        cursor &operator++() {
            if (*this == this->end) {
                throw std::range_error{"Already reached the end."};
            }
            return ++*this;
        }

        cursor &operator=(const cursor &other) {
            *static_cast<sci_t *>(this) = other;
            return *this;
        }

    private:
        const sci_t &end;
    };
}

#endif//INCLUDE_SINGULARITY_JSON_CURSOR_ONCE_FLAG
