
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class Solution {

    private record Sentence(StringBuilder sentence, int sentenceSize) {}
    private final Trie trie = new Trie();
    private final List<String> allPossibleSentences = new ArrayList<>();

    public List<String> wordBreak(String source, List<String> dictionary) {
        addAllWordsInDictionaryToTrie(dictionary);
        searchForAllPossibleSentences(source);
        return allPossibleSentences;
    }

    private void addAllWordsInDictionaryToTrie(List<String> dictionary) {
        for (int i = 0; i < dictionary.size(); ++i) {
            trie.addWord(dictionary.get(i));
        }
    }

    private void searchForAllPossibleSentences(String source) {
        Queue<Sentence> queue = new LinkedList<>();
        queue.add(new Sentence(new StringBuilder(), 0));

        while (!queue.isEmpty()) {

            int size = queue.size();
            while (size-- > 0) {
                Sentence current = queue.poll();
                if (current.sentenceSize == source.length()) {
                    allPossibleSentences.add(current.sentence.toString().substring(1));
                    continue;
                }

                List<String> next = trie.searchWords(source.substring(current.sentenceSize));
                for (String word : next) {
                    StringBuilder sentence = new StringBuilder();
                    sentence.append(current.sentence).append(" ").append(word);
                    int sentenceSize = current.sentenceSize + word.length();
                    queue.add(new Sentence(sentence, sentenceSize));
                }
            }
        }
    }
}

class TrieNode {

    private static final int ALPHABET_SIZE = 26;
    TrieNode[] branches = new TrieNode[ALPHABET_SIZE];
    boolean isEndOfWord;
}

class Trie {

    final TrieNode rootTrieNode = new TrieNode();

    void addWord(String word) {
        TrieNode current = rootTrieNode;

        for (int indexWord = 0; indexWord < word.length(); ++indexWord) {
            int indexBranches = word.charAt(indexWord) - 'a';
            if (current.branches[indexBranches] == null) {
                current.branches[indexBranches] = new TrieNode();
            }
            current = current.branches[indexBranches];
        }
        current.isEndOfWord = true;
    }

    List<String> searchWords(String word) {
        TrieNode current = rootTrieNode;

        List<String> nextWords = new ArrayList<>();
        for (int indexWord = 0; indexWord < word.length(); ++indexWord) {
            int indexBranches = word.charAt(indexWord) - 'a';
            if (current.branches[indexBranches] == null) {
                break;
            }
            current = current.branches[indexBranches];
            if (current.isEndOfWord) {
                nextWords.add(word.substring(0, indexWord + 1));
            }
        }
        return nextWords;
    }
}
