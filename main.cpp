#include <iostream>
#include "include/json.hpp"

using namespace std;
using namespace singularity;

int main() {
    json a{json::content_type::array}, b = true, c{b}, d;
    json::array_t &x = a;
    x.push_back(b);
    c = false;
    x.push_back(c);
    d = "abc\"def\\ghi\tjkl\n\tmno";
    x.push_back(d);
    json::object_t y;
    y["abno"] = a;
    y["c\"\tm"] = b;
    y["del\n"] = c;
    y["f\\jk"] = d;
    cout << json{y}.stringify();
    return 0;
}
