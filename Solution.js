
/**
 * @param {string} source
 * @param {string[]} dictionary
 * @return {string[]}
 */
var wordBreak = function (source, dictionary) {
    this.trie = new Trie();
    this.allPossibleSentences = [];
    addAllWordsInDictionaryToTrie(dictionary);
    searchForAllPossibleSentences(source);
    return this.allPossibleSentences;
};

/**
 * @param {string[]} dictionary
 * @return {void}
 */
function addAllWordsInDictionaryToTrie(dictionary) {
    for (let word of dictionary) {
        this.trie.addWord(word);
    }
}

/**
 * @param {string} source
 * @return {void}
 */
function searchForAllPossibleSentences(source) {
    const queue = new Queue();//Queue<Sentence>
    queue.enqueue(new Sentence("", 0));

    while (!queue.isEmpty()) {

        let size = queue.size();
        while (size-- > 0) {
            const current = queue.dequeue();
            if (current.sentenceSize === source.length) {
                this.allPossibleSentences.push(current.sentence.substring(1));
                continue;
            }

            const next = this.trie.searchWords(source.substring(current.sentenceSize));
            for (let word of next) {
                let sentence = current.sentence.concat(" ").concat(word);
                let sentenceSize = current.sentenceSize + word.length;
                queue.enqueue(new Sentence(sentence, sentenceSize));
            }
        }
    }
}

/**
 * @param {string} sentence
 * @param {number} sentenceSize
 */
function Sentence(sentence, sentenceSize) {
    this.sentence = sentence;
    this.sentenceSize = sentenceSize;
}

class TrieNode {

    static ALPHABET_SIZE = 26;
    branches = new Array(TrieNode.ALPHABET_SIZE).fill(null);
    isEndOfWord = false;
}

class Trie {

    rootTrieNode = new TrieNode();
    static ascii_small_case_a = 97;

    /**
     * @param {string} word
     * @return {void}
     */
    addWord(word) {
        let current = this.rootTrieNode;

        for (let indexWord = 0; indexWord < word.length; ++indexWord) {
            let indexBranches = word.codePointAt(indexWord) - Trie.ascii_small_case_a;
            if (current.branches[indexBranches] === null) {
                current.branches[indexBranches] = new TrieNode();
            }
            current = current.branches[indexBranches];
        }
        current.isEndOfWord = true;
    }

    /**
     * @param {string} word
     * @return {string[]}
     */
    searchWords(word) {
        let current = this.rootTrieNode;

        const nextWords = [];
        for (let indexWord = 0; indexWord < word.length; ++indexWord) {
            let indexBranches = word.codePointAt(indexWord) - Trie.ascii_small_case_a;
            if (current.branches[indexBranches] === null) {
                break;
            }
            current = current.branches[indexBranches];
            if (current.isEndOfWord) {
                nextWords.push(word.substring(0, indexWord + 1));
            }
        }
        return nextWords;
    }
}
