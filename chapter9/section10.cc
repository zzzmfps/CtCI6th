#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

class BitSet {
private:
    uint8_t *bytes = nullptr;

public:
    BitSet(size_t length) {
        this->bytes = new uint8_t[ceil(length / 8)]{};
    }
    ~BitSet() {
        delete[] this->bytes;
    }
    bool add(size_t n) {
        uint8_t byte = n >> 3, offset = 2 << (n & 7);
        bool origin = this->bytes[byte] & offset;
        this->bytes[byte] |= offset;
        return origin;
    }
};

struct Node {
    int key;
    int count = 1;
    Node *lchild = nullptr, *rchild = nullptr;
    Node(int k) : key(k) {}
};

class NumberStream {
private:
    Node *root = nullptr;

public:
    ~NumberStream() {
        if (!this->root) return;
        std::queue<Node *> q;
        q.push(this->root);
        while (!q.empty()) {
            Node *cur = q.front();
            if (cur->lchild) q.push(cur->lchild);
            if (cur->rchild) q.push(cur->rchild);
            delete cur;
            q.pop();
        }
    }

    void track(int x) {
        this->insert(this->root, x);
    }

    int getRankOfNumber(int x) {
        if (!this->root) return 0;

        Node *node = this->root;
        while (node->lchild && x < node->key) node = node->lchild;
        if (!node->lchild && x < node->key) return 0;

        return node->count - this->getCount(node, x);
    }

private:
    void insert(Node *&node, int value) {
        if (!node) {
            node = new Node(value);
            return;
        }
        if (value == node->key) {
            ++node->count;
            return;
        }
        ++node->count;
        this->insert(value < node->key ? node->lchild : node->rchild, value);
    }

    // get total counts of nodes that larger than value
    // if value exists in the BST, plus 1 (exclude itself once)
    int getCount(Node *node, int value) {
        if (!node) return 0;
        if (value > node->key) return this->getCount(node->rchild, value);
        if (value == node->key) return 1 + (node->rchild ? node->rchild->count : 0);
        if (!node->lchild) return node->count;
        return node->count - (node->lchild->count - this->getCount(node->lchild, value));
    }
};

class Section10 {
public:
    template <typename T>
    static void merge(T a[], size_t len1, size_t len2, T b[], size_t len3) {
        if (len2 < len1 + len3) return;
        for (size_t i = len1 - 1, j = len2 - 1; i < len1;) a[j--] = a[i--];

        int i = 0, j = len2 - len1, k = 0;
        while (k < len3) {
            if (a[j] < b[k]) {
                a[i++] = a[j++];
            } else {
                a[i++] = b[k++];
            }
        }
    }

    static void anagramSort(std::vector<std::string> &words) {
        auto count = [](const std::string &word) -> int * {
            int *counts = new int[26]{};
            for (auto &&ch : word) ++counts[ch - 97];
            return counts;
        };
        auto cmp = [&](int *pCounts, size_t length, const std::string &word) -> int {
            if (length != word.size()) return (length < word.size()) ? 1 : -1;
            int *counts = count(word);
            for (size_t i = 0; i < 26; ++i) {
                if (pCounts[i] == counts[i]) continue;
                return pCounts[i] < counts[i] ? -1 : 1;
            }
            delete[] counts;
            return 0;
        };
        auto partition = [&](int begin, int end) -> std::pair<int, int> {
            int *pCounts = count(words[begin]);
            size_t length = words[begin].size();

            int b = begin, l = begin + 1, r = end - 1, e = end;
            while (l < r) {
                while (l < e) { // l
                    int res = cmp(pCounts, length, words[l]);
                    if (res > 0) break;
                    if (0 == res) std::swap(words[++b], words[l]);
                    ++l;
                }
                while (b < r) { // r
                    int res = cmp(pCounts, length, words[r]);
                    if (res < 0) break;
                    if (0 == res) std::swap(words[--e], words[r]);
                    --r;
                }
                if (l < r) std::swap(words[l++], words[r--]);
            }
            if (l == r) {
                switch (cmp(pCounts, length, words[l])) {
                    case 0: std::swap(words[++b], words[l++]); break;
                    case -1: ++l; break;
                    case 1: --r; break;
                }
            }
            while (begin <= b) std::swap(words[b--], words[--l]);
            while (end > e) std::swap(words[e++], words[++r]);
            delete[] pCounts;
            return std::make_pair(l, r); // range of anagrams
        };
        auto sort = [&](auto &&self, int begin, int end) -> void {
            if (begin + 2 >= end) return;
            auto [l, r] = partition(begin, end);
            self(self, begin, l);
            self(self, r + 1, end);
        };

        // optimize: only count each word once
        sort(sort, 0, words.size());
    }

    static int findRotatedArray(const std::vector<int> &array, int target) {
        // assuming no repeat elems
        if (array.empty()) return -1;
        if (1 == array.size()) return target == array[0] ? 0 : -1;

        if (array.front() > array[1]) { // 5 1 2 3 4
            return target == array.front() ? 0 : binarySearch(array, target, 1, array.size());
        }
        if (array.back() > array[0]) { // 1 2 3 4 5
            return binarySearch(array, target, 0, array.size());
        }
        // if max-value is not at the edge of array
        int l = 1, r = array.size() - 1, mid;
        while (l < r) { // find min-value
            mid = l + (r - l) / 2;
            if (array[mid - 1] > array[mid] && array[mid] < array[mid + 1]) break;
            if (array[mid - 1] < array[mid]) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return array.front() <= target ? binarySearch(array, target, 0, mid)
                                       : binarySearch(array, target, mid, array.size());
    }

    static int findInSparseArray(const std::vector<std::string> &strs, const std::string &target) {
        std::stack<std::pair<int, int>> st;
        st.emplace(0, static_cast<int>(strs.size()));
        int hintL = 0, hintR = strs.size(); // hints that target is in [hintL, hintR)

        while (!st.empty()) {
            auto [l, r] = st.top();
            st.pop();
            if (l >= r || l >= hintR || r <= hintL) continue;

            int mid = l + (r - l) / 2;
            if (target == strs[mid]) return mid;
            if (strs[mid].empty()) {
                st.emplace(l, mid);
                st.emplace(mid + 1, r);
            } else if (target < strs[mid]) {
                st.emplace(l, mid);
                hintR = mid;
            } else {
                st.emplace(mid + 1, r);
                hintL = mid + 1;
            }
        }

        return -1;
    }

    static void findRepeatElements(const std::vector<int> &numbers, int n) {
        BitSet bs(n);
        for (auto &&num : numbers)
            if (bs.add(num)) std::cout << num << ' ';
        std::cout << '\n';
    }

    static std::pair<int, int> findInSortedMatrix(const std::vector<std::vector<int>> &matrix, int target) {
        auto ret = std::make_pair(-1, -1);
        if (matrix.empty() || matrix[0].empty()) return ret;
        if (target > matrix.back().back()) return ret;

        for (size_t r = 0; r < matrix.size(); ++r) {
            if (target < matrix[r].front()) break;
            if (target > matrix[r].back()) continue;
            int index = Section10::binarySearch(matrix[r], target, 0, matrix[r].size());
            if (-1 != index) {
                ret.first = r, ret.second = index;
                return ret;
            }
        }
        return ret;
    }

    static void getRankOfNumber() {
        int value;
        NumberStream ns;
        while (std::cin >> value) ns.track(value);
        std::cin.clear();
        while (std::cin >> value) std::cout << ns.getRankOfNumber(value) << '\n';
    }

    static void peakAndEbb(std::vector<int> &array) {
        std::sort(array.begin(), array.end());

        size_t i = 0;
        std::vector<int> tmp(array.size());
        for (size_t j = 0; j < array.size(); j += 2) tmp[j] = array[i++];
        for (size_t j = 1; j < array.size(); j += 2) tmp[j] = array[i++];
        array.swap(tmp);
    }

private:
    static int binarySearch(const std::vector<int> &array, int target, int l, int r) {
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (target == array[mid]) return mid;
            if (target < array[mid]) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
