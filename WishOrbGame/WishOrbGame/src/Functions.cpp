#include "../include/Functions.h"
#include <fstream>
#include <sstream>
using namespace std;

vector<string> split(const string& _string, char razdel) {
    vector<string> parts;
    stringstream ss(_string);
    string part;
    while (getline(ss, part, razdel)) {
        parts.push_back(part);
    }
    return parts;
}