#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <set>

using namespace std;

// РћР±СЉСЏРІР»СЏРµРј Group<String> РґР»СЏ РїСЂРѕРёР·РІРѕР»СЊРЅРѕРіРѕ С‚РёРїР° String
// СЃРёРЅРѕРЅРёРјРѕРј vector<String>.
// Р‘Р»Р°РіРѕРґР°СЂСЏ СЌС‚РѕРјСѓ РІ РєР°С‡РµСЃС‚РІРµ РІРѕР·РІСЂР°С‰Р°РµРјРѕРіРѕ Р·РЅР°С‡РµРЅРёСЏ
// С„СѓРЅРєС†РёРё РјРѕР¶РЅРѕ СѓРєР°Р·Р°С‚СЊ РЅРµ РјР°Р»РѕРїРѕРЅСЏС‚РЅС‹Р№ РІРµРєС‚РѕСЂ РІРµРєС‚РѕСЂРѕРІ,
// Р° РІРµРєС‚РѕСЂ РіСЂСѓРїРї вЂ” vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Р•С‰С‘ РѕРґРёРЅ С€Р°Р±Р»РѕРЅРЅС‹Р№ СЃРёРЅРѕРЅРёРј С‚РёРїР°
// РїРѕР·РІРѕР»СЏРµС‚ РІРјРµСЃС‚Рѕ РіСЂРѕРјРѕР·РґРєРѕРіРѕ typename String::value_type
// РёСЃРїРѕР»СЊР·РѕРІР°С‚СЊ Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
    map<set<Char<String>>, vector<String>> groups;
    for (const auto& s : strings) {
        set<Char<String>> v = {s.begin(), s.end()};
        groups[v].push_back(move(s));
    }
    vector<Group<String>> result;
    for (const auto& g : groups) {
        result.push_back(move(g.second));
    }
    return result;
}


void TestGroupingABC() {
    vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    sort(begin(groups), end(groups));  // РџРѕСЂСЏРґРѕРє РіСЂСѓРїРї РЅРµ РёРјРµРµС‚ Р·РЅР°С‡РµРЅРёСЏ
    ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
    ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
    vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    sort(begin(groups), end(groups));  // РџРѕСЂСЏРґРѕРє РіСЂСѓРїРї РЅРµ РёРјРµРµС‚ Р·РЅР°С‡РµРЅРёСЏ
    ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
    ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
    ASSERT_EQUAL(groups[2], vector<string>({"port"}));
    ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    RUN_TEST(tr, TestGroupingReal);
    return 0;
}
