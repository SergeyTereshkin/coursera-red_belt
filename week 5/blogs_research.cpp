#include <algorithm>
#include <cstdint>
#include <vector>
#include <future>
#include <map>
#include <sstream>
#include "test_runner.h"

using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for (const auto& o : other.word_frequences) {
            auto itr = word_frequences.find(o.first);
            if (itr != end(word_frequences)) {
                word_frequences[o.first] += o.second;
            }
            else {
                word_frequences[o.first] = o.second;
            }
        }
    }
};

Stats ExploreKeyWordSingle(const set<string>& key_words, istream& input) {
    Stats stats;

    string word;
    while (input >> word) {
        auto itr = key_words.find(word);
        if (itr != key_words.end()) {
            if (stats.word_frequences.count(word) == 0) {
                stats.word_frequences[word] = 0;
            }
            stats.word_frequences[word]++;
        }
    }

    return stats;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    // Implement this function
    vector<future<Stats>> futures;
    Stats res;
    int num_streams = 4;
    vector<stringstream> streams(num_streams);
    string word;
    futures.reserve(num_streams);

    int i = 0;
    while (input >> word) {
        streams[i%num_streams] << word + " ";
        i++;
    }
    for (auto& stream : streams) {
        futures.push_back(async(ExploreKeyWordSingle, ref(key_words), ref(stream)));
    }

    for (auto& f : futures) {
        res += f.get();
    }

    return res;
}
