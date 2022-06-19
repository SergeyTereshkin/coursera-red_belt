#include "stats.h"

#include <map>
#include <string_view>
using namespace std;

vector<string_view>
SplitIntoWords(string_view strv)
{
    vector<string_view> output;
    size_t first = 0;

    while (first < strv.size())
    {
        const auto second = strv.find_first_of(" ", first);

        if (first != second)
            output.emplace_back(strv.substr(first, second-first));

        if (second == string_view::npos)
            break;

        first = second + 1;
    }

    return output;
}


HttpRequest ParseRequest(string_view line) {
    vector<string_view> result = SplitIntoWords(line);
    string_view method = result[0];
    string_view uri = result[1];
    string_view protocol = result[2];

    HttpRequest req = {method, uri, protocol};
    return req;
}

Stats::Stats() {
    uris = {
            {"unknown", 0},
            {"/", 0},
            {"/order", 0},
            {"/product", 0},
            {"/basket", 0},
            {"/help", 0}
    };

    methods = {
            {"GET", 0},
            {"POST", 0},
            {"DELETE", 0},
            {"PUT", 0},
            {"UNKNOWN", 0}
    };
}


void Stats::AddUri(string_view uri) {
    if (uris.count(uri) == 0) {
        uris["unknown"] += 1;
    }
    else uris[uri] += 1;
}


void Stats::AddMethod(string_view method) {
    if (methods.count(method) == 0) {
        methods["UNKNOWN"] += 1;
    }
    else methods[method] += 1;
}


const map<string_view, int>& Stats::GetMethodStats() const {
    return methods;
}

const map<string_view, int>& Stats::GetUriStats() const {
    return uris;
}

