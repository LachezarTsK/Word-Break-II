
#include <array>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct TrieNode {
    inline static const int ALPHABET_SIZE = 26;
    array<shared_ptr<TrieNode>, ALPHABET_SIZE > branches{};
    bool isEndOfWord{};
};

class Trie {
    
    const shared_ptr<TrieNode> rootTrieNode = make_shared<TrieNode>();

public:
    //C++20: ...(string_view word ...) ...
    void addWord(const string& word) const {
        shared_ptr<TrieNode> current = rootTrieNode;
        
        for (const auto& letter : word) {
            int indexBranches = letter - 'a';
            if (current->branches[indexBranches] == nullptr) {
                current->branches[indexBranches] = make_shared<TrieNode>();
            }
            current = current->branches[indexBranches];
        }
        current->isEndOfWord = true;
    }

    //C++20: ...(string_view word ...) ...
    vector<string> searchWords(const string& word) const {
        shared_ptr<TrieNode> current = rootTrieNode;
        
        vector<string> nextWords;
        for (int indexWord = 0; indexWord < word.length(); ++indexWord) {
            int indexBranches = word[indexWord] - 'a';
            if (current->branches[indexBranches] == nullptr) {
                break;
            }
            current = current->branches[indexBranches];
            if (current->isEndOfWord) {
                nextWords.push_back(word.substr(0, indexWord + 1));
            }
        }
        return nextWords;
    }
};

class Solution {

    struct Sentence {
        string sentence;
        size_t sentenceSize{};
        Sentence(string sentence, size_t sentenceSize) : sentence{move(sentence)}, sentenceSize{sentenceSize}{}
    };
    const Trie trie{};
    vector<string> allPossibleSentences;

public:
    vector<string> wordBreak(const string& source, const vector<string>& dictionary) {
        addAllWordsInDictionaryToTrie(dictionary);
        searchForAllPossibleSentences(source);
        return allPossibleSentences;
    }

private:
    void addAllWordsInDictionaryToTrie(const vector<string>& dictionary) const {
        for (const auto& word : dictionary) {
            trie.addWord(word);
        }
    }

    //C++20: ...(string_view word ...) ...
    void searchForAllPossibleSentences(const string& source) {
        queue<Sentence> queue;
        queue.emplace(string(""), 0);

        while (!queue.empty()) {

            size_t size = queue.size();
            while (size-- > 0) {
                Sentence current = queue.front();
                queue.pop();
                if (current.sentenceSize == source.length()) {
                    allPossibleSentences.push_back(current.sentence.substr(1));
                    continue;
                }

                vector<string> next = trie.searchWords(source.substr(current.sentenceSize));
                for (const auto& word : next) {
                    string sentence;
                    sentence.append(current.sentence).append(" ").append(word);
                    size_t sentenceSize = current.sentenceSize + word.length();
                    queue.emplace(sentence, sentenceSize);
                }
            }
        }
    }
};
