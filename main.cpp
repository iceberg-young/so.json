#include <iostream>
#include "include/json.hpp"

using namespace std;
using namespace singularity;

int main() {
    json a{json::content_type::array}, b{json::content_type::boolean}, c{b}, e;
    json::array_t &aa = a;
    b = true;
    aa.push_back(b);
    c = false;
    aa.push_back(c);
    e = std::string{"abc\"def\\ghi\tjkl\n\tm,no"};
    aa.push_back(e);
    json::object_t oa;
    oa["abc\"def\\ghi\tjkl\n\tm,no"] = a;
    json d;
    d = oa;
    cout << d.stringify();
    return 0;
}
