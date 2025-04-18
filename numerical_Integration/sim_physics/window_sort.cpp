/*

Input: s = "barfoothefoobarman", words = ["foo","bar"]

Output: [0,9]

Explanation:

The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.
*/
#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
    std::vector<int> findSubstring(const std::string& s, const std::vector<std::string>& words) {
        if (s.empty() || words.empty()) return {};

        int word_len = words[0].size();
        int number_words = words.size();
        int window_size = word_len * number_words;
        std::unordered_map<std::string, int> word_counter;

        for (const auto& word : words) {
            ++word_counter[word];
        }

        std::vector<int> result;

        for (int i = 0; i <= s.size() - window_size; ++i) {
            std::unordered_map<std::string, int> seen;
            for (int j = 0; j < number_words; ++j) {
                int start = i + j * word_len;
                std::string word = s.substr(start, word_len);
                if (word_counter.find(word) != word_counter.end()) {
                    ++seen[word];
                    if (seen[word] > word_counter[word]) {
                        break;
                    }
                } else {
                    break;
                }
            }

            if (seen == word_counter) {
                result.push_back(i);
            }
        }

        return result;
    }
};