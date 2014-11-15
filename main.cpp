#include <iostream>
#include "include/json.hpp"

using namespace std;
using namespace singularity;

int main() {
//    cout << json::parse("").stringify() << endl;
    cout << json::parse("null").stringify() << endl;
    cout << json::parse("false").stringify() << endl;
    cout << json::parse("true").stringify() << endl;
    cout << json::parse("1.234e2").stringify() << endl;
    cout << json::parse("\"hello\\\"world\"").stringify() << endl;

    cout << json::parse("[1,\"2\", [ 3, \"x4x\",[5]]]").stringify() << endl;
    cout << json::parse("{\"x\":\"a\",\"y\" : [\"a\"] , \"z\": [ \"x\" ,{ \"y\" : [1, \"2\" ,3.4e2]}]}").stringify() << endl;

    return 0;
}
