#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }
    vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));
    vector<typename RandomIt::value_type> temp;
    auto size = (end(elements) - begin(elements));
    auto fthird = begin(elements) + size/3;
    auto sthird = fthird + size/3;
    MergeSort(begin(elements), fthird);
    MergeSort(fthird, sthird);
    MergeSort(sthird, end(elements));
    merge(make_move_iterator(begin(elements)), make_move_iterator(fthird),
          make_move_iterator(fthird), make_move_iterator(sthird), back_inserter(temp));
    merge(make_move_iterator(begin(temp)), make_move_iterator(end(temp)), make_move_iterator(sthird), make_move_iterator(end(elements)), range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
