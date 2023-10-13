#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <map>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    using Id = int;

    
    Id Add(T object) {
        ids[counter] = make_pair(move(object), 0);
        priorities[0].insert(counter);
        counter += 1;
        return counter - 1;
    }


    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {

        for (int i = 0; i < distance(range_begin, range_end); i++) {
            *ids_begin = Add(move(*next(range_begin, i)));
            ids_begin++;
        }
    }
    
    bool IsValid(Id id) const {
        return ids.count(id) != 0;
    }
    
    const T& Get(Id id) const {
        return ids.at(id).first;
    }
    
    void Promote(Id id) {
        int priority = ids[id].second;
        priorities[priority].erase(id);
        if (priorities[priority].empty()) {
            priorities.erase(priority);
        }
        priorities[priority + 1].insert(id);
        ids[id].second = priority + 1;
    }
    
    pair<const T&, int> GetMax() const {
        auto max_itr = prev(end(priorities));
        int priority = max_itr->first;
        set<Id> max_ids = max_itr->second;
        Id id = *prev(end(max_ids));
        return {ids.at(id).first, priority};
    }
    
    pair<T, int> PopMax() {
        auto max_itr = prev(end(priorities));
        int priority = max_itr->first;
        set<Id> max_ids = max_itr->second;
        Id id = *prev(end(max_ids));
        pair<T, int> res = make_pair(move(ids[id].first), priority);
        ids.erase(id);
        prev(end(priorities))->second.erase(id);

        if (max_itr->second.empty()) {
            priorities.erase(max_itr->first);
        }
        return res;
    }

private:

    map<Id, pair<T, int>> ids;
    map<int, set<Id>> priorities;
    Id counter = 0;
};
