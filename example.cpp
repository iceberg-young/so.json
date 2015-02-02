#include <fstream>
#include <iostream>
#include "include/json.hpp"

using namespace std;
using namespace so;

int main(int ac, char* av[]) {
    string text;
    cin >> text;
    cout << json::parse(text).stringify();
    return 0;
}
