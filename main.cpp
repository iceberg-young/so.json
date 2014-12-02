#include <list>
#include <fstream>
#include <iostream>
#include "include/json.hpp"

using namespace std;
using namespace singularity;

int main() {
//    fstream f("sample.json");
//    string text;
//    f >> text;
//    list<string> pool;
//    const int LOOP = 200;
//    for (int i = 0; i < LOOP; ++i) {
//        pool.emplace_back(json::parse(text)->stringify());
//        cout << i << ' ';
//    }
//    cout << json::parse(text)->stringify().length();

//    cout << json::parse("").stringify() << endl;

    cout << json::parse("null")->stringify() << endl;
    cout << json::parse("false")->stringify() << endl;
    cout << json::parse("true")->stringify() << endl;
    cout << json::parse("1.2345678901234567890123456789e300")->stringify() << endl;
    cout << json::parse("\"\"")->stringify() << endl;
    cout << json::parse("\"hello\t\x01\\t\\\"world\"")->stringify() << endl;
    cout << json::parse("[1,\"2\", [ 3, \"x4x\",[5]]]")->stringify() << endl;
    cout << json::parse("{\"x\":\"a\",\"y\" : [\"a\"] , \"z\": [ \"x\" ,{ \"y\" : [1, \"2\" ,3.4e2]}]}")->stringify() << endl;

    return 0;
}
