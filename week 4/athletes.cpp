#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

int main() {
    int sportsman_count;
    cin >> sportsman_count;
    list<int> sportsmen_queue;
    for (int i = 0; i < sportsman_count; i++) {
        int first, second;
        cin >> first >> second;
        auto itr = find(begin(sportsmen_queue), end(sportsmen_queue), second);
        if (itr != end(sportsmen_queue)) {
            sportsmen_queue.insert(itr, first);
        }
        else if (second == 0 or itr == end(sportsmen_queue)) {
            sportsmen_queue.push_back(first);
        }


    }

    for (auto l : sportsmen_queue) {
        cout << l << '\n';
    }
    return 0;
}
