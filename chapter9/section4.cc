#include <bits/stdc++.h>

template <typename T>
class GraphNode {
private:
    T value;
    std::unordered_set<GraphNode *> connects;

public:
    GraphNode(const T &val) : value(val) {}

    const T &getValue() { return this->value; }

    void setValue(const T &val) { this->value = val; }

    void getConnects(GraphNode *node) { this->connects.insert(node); }

    const std::unordered_set<GraphNode *> &getConnects() { return this->connects; }

    bool isConnected(GraphNode *node) {
        if (this == node) {
            return true;
        }
        std::unordered_set<GraphNode *> visited({this});
        std::queue<GraphNode *> q({this});
        while (!q.empty()) {
            for (size_t i = q.size(); i > 0; --i) {
                GraphNode *cur = q.front();
                q.pop();
                for (auto &&n : cur->connects) {
                    if (!visited.contains(n)) {
                        visited.insert(n);
                        q.push(n);
                    }
                }
            }
            if (visited.contains(node)) return true;
        }
        return false;
    }
};

template <typename T>
class TreeNode {
private:
    T value;
    TreeNode *lchild = nullptr, *rchild = nullptr;

public:
    TreeNode(const T &val) : value(val) {}

    const T &getValue() { return this->value; }

    TreeNode *setLeftChild(const T &val) { return this->lchild = new TreeNode(val); }

    TreeNode *setRightChild(const T &val) { return this->rchild = new TreeNode(val); }

    void levelTraverse(auto &&p1, auto &&p2, int level = -1) {
        if (0 == level) return;
        std::queue<TreeNode *> q({this});
        while (!q.empty()) {
            for (size_t i = q.size(); i > 0; --i) {
                TreeNode *cur = q.front();
                q.pop();
                p1(cur);
                if (cur->lchild) q.push(cur->lchild);
                if (cur->rchild) q.push(cur->rchild);
            }
            if (0 == --level) break;
            p2();
        }
    }

    TreeNode *successor(TreeNode *node) {
        if (!node) return nullptr;
        static bool visited = false;

        TreeNode *ret;
        if (ret = TreeNode::successor(node->lchild)) return ret;
        if (visited) return node;
        if (node == this) visited = true;
        if (ret = TreeNode::successor(node->rchild)) return ret;
        return nullptr;
    }

    std::vector<std::vector<T>> getAllOriginInputSeqs() {
        auto randomMerge = [](auto &&self, std::vector<std::vector<T>> &mat, const std::vector<T> &v1,
                              const std::vector<T> &v2, size_t i, size_t j, std::vector<T> &cur) -> void {
            if (i == v1.size() && j == v2.size()) {
                mat.push_back(cur);
                return;
            }
            if (i < v1.size()) {
                cur.push_back(v1[i]);
                self(self, mat, v1, v2, i + 1, j, cur);
                cur.pop_back();
            }
            if (j < v2.size()) {
                cur.push_back(v2[j]);
                self(self, mat, v1, v2, i, j + 1, cur);
                cur.pop_back();
            }
        };
        auto helper = [&](auto &&self, TreeNode *node) -> std::vector<std::vector<T>> {
            std::vector<std::vector<T>> ret;
            if (node) {
                auto l = self(self, node->lchild);
                auto r = self(self, node->rchild);
                std::vector<T> tmp = {node->value};
                if (l.empty() && r.empty()) {
                    ret.push_back(tmp);
                } else if (l.empty() || r.empty()) {
                    auto &lr = l.empty() ? r : l;
                    for (auto &&seq : lr) {
                        ret.push_back(tmp);
                        for (auto &&v : seq) ret.back().push_back(v);
                    }
                } else {
                    for (size_t i = 0; i < l.size(); ++i)
                        for (size_t j = 0; j < r.size(); ++j) randomMerge(randomMerge, ret, l[i], r[j], 0, 0, tmp);
                }
            }
            return ret;
        };
        return helper(helper, this);
    }

    bool isSubtree(TreeNode *root) {
        if (!root) return false;

        auto sameWith = [](auto &&self, TreeNode *r1, TreeNode *r2) {
            if (r1 == r2) return true;
            if (!r1 || !r2 || r1->value != r2->value) return false;
            return self(self, r1->lchild, r2->lchild) && self(self, r1->rchild, r2->rchild);
        };
        auto leftHeight = [](TreeNode *root) {
            int lh = 0;
            while (root) ++lh, root = root->lchild;
            return lh;
        };
        int lh1 = leftHeight(this);

        std::queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *cur = q.front();
            q.pop();

            int lh2 = leftHeight(cur);
            if (cur->rchild) q.push(cur->rchild);
            for (size_t i = lh2 - lh1; i > 0; --i) {
                if (!(cur = cur->lchild)) break;
                if (cur->rchild) q.push(cur->rchild);
            }

            if (sameWith(sameWith, this, cur)) return true;
        }

        return false;
    }

    static TreeNode *buildBST(int array[], int l, int r) {
        if (l >= r) return nullptr;
        int mid = l + (r - l) / 2;
        TreeNode *node = new TreeNode(array[mid]);
        node->lchild = TreeNode::buildBST(array, l, mid);
        node->rchild = TreeNode::buildBST(array, mid + 1, r);
        return node;
    }

    static int getBalanceFactor(TreeNode *node) {
        if (!node || node->lchild == node->rchild) return 0;
        int l = node->lchild ? 1 + TreeNode::getBalanceFactor(node->lchild) : 0;
        int r = node->rchild ? 1 + TreeNode::getBalanceFactor(node->rchild) : 0;
        return std::abs(l - r);
    }

    static bool isBST(TreeNode *node) {
        if (!node) return true;
        T &value = node->value;
        if (node->lchild && node->lchild->value > value) return false;
        if (node->rchild && node->rchild->value <= value) return false;
        return TreeNode::isBST(node->lchild) && TreeNode::isBST(node->rchild);
    }

    static TreeNode *findFirstCommonAncestor(TreeNode *root, TreeNode *n1, TreeNode *n2) {
        if (!root) return nullptr;

        static int mask = 0;

        TreeNode *l = TreeNode::findFirstCommonAncestor(root->lchild, n1, n2);
        if (2 == mask) return l;
        TreeNode *r = TreeNode::findFirstCommonAncestor(root->rchild, n1, n2);
        if (2 == mask) return l ? root : r;

        if (root == n1 || root == n2) {
            ++mask;
            return root;
        }

        return (l ? l : r ? r : nullptr);
    }

    static std::vector<std::vector<int>> sumPath(TreeNode *root, int target) {
        std::vector<std::vector<int>> paths;

        std::vector<int> cur;
        auto helper = [&](auto &&self, TreeNode *node, int t) {
            if (!node) return;
            cur.push_back(node->value);
            if (node->value == t) paths.push_back(cur);
            self(self, node->lchild, t - node->value);
            self(self, node->rchild, t - node->value);
            cur.pop_back();
            self(self, node->lchild, t);
            self(self, node->rchild, t);
        };
        helper(helper, root, target);

        return paths;
    }
};

template <typename T>
class RandomBinaryTree {
private:
    std::default_random_engine engine;

    std::vector<T> tree = {0, 0};
    int size = 0;

public:
    T &getRandomNode() {
        if (0 == this->size) return this->tree[0];
        std::uniform_int_distribution<int> distribution(1, this->size);
        int index = distribution(this->engine);
        return this->tree[index];
    }

    void insertNode(const T &value) {
        if (this->size + 1 == this->tree.size()) this->tree.resize(this->tree.size() * 2);
        this->tree[++this->size] = value;
        this->swim(this->size);
    }

    int find(const T &value) {
        if (0 == this->size) return 0;
        if (value == this->tree[1]) return 1;

        std::stack<int> st({1});
        auto check = [&](int i) {
            if (i <= this->size) {
                if (value == this->tree[i]) return i;
                if (value < this->tree[i]) st.push(i);
            }
            return 0;
        };

        while (!st.empty()) {
            int i = st.top(), j;
            st.pop();
            if (j = check(i * 2)) return j;
            if (j = check(i * 2 + 1)) return j;
        }
        return 0;
    }

    bool deleteNode(const T &value) {
        int index = this->find(value);
        if (0 == index) return false;
        this->tree[index] = std::move(this->tree[this->size--]);
        this->sink(index);
        return true;
    }

private:
    void swim(int i) {
        T value = this->tree[i];
        while (i > 1) {
            int j = i / 2;
            if (this->tree[j] >= value) break;
            this->tree[i] = std::move(this->tree[j]);
            i = j;
        }
        this->tree[i] = std::move(value);
    }

    void sink(int i) {
        T value = this->tree[i];
        while (true) {
            int j = i * 2;
            if (j > this->size || value >= this->tree[j]) break;
            if (j + 1 <= this->size && value < this->tree[j + 1]) ++j;
            this->tree[i] = std::move(this->tree[j]);
            i = j;
        }
        this->tree[i] = std::move(value);
    }
};

class Section4 {
public:
    static void isConnected() {
        GraphNode<int> *n1 = new GraphNode<int>(1);
        GraphNode<int> *n2 = new GraphNode<int>(2);
        GraphNode<int> *n3 = new GraphNode<int>(3);
        n1->getConnects(n2);
        n2->getConnects(n3);
        GraphNode<int> *n4 = new GraphNode<int>(4);
        std::cout << n1->isConnected(n3) << '\n'; // true
        std::cout << n1->isConnected(n4) << '\n'; // false
    }

    static void minHeightBST() {
        int array[] = {1, 2, 3, 4, 6, 7, 8, 9};
        auto *root = TreeNode<int>::buildBST(array, 0, 8);
        root->levelTraverse([](auto &&node) { std::cout << node->getValue() << ' '; }, []() { std::cout << '\n'; });
    }

    static void listOfCertainHeight() {
        int array[] = {1, 2, 3, 4, 6, 7, 8, 9}, level = 2;
        auto *root = TreeNode<int>::buildBST(array, 0, 8);
        std::vector<std::list<TreeNode<int> *>> lists({std::list<TreeNode<int> *>()});
        root->levelTraverse([&](auto &&node) { lists.back().push_back(node); },
                            [&]() { lists.push_back(std::list<TreeNode<int> *>()); }, level);
        std::cout << lists.size() << '\n';
        for (auto &&list : lists) {
            for (auto &&elem : list) std::cout << elem->getValue() << ' ';
            std::cout << '\n';
        }
    }

    static void isBalanced() {
        TreeNode<int> *root = new TreeNode(1);
        TreeNode<int> *n2 = root->setLeftChild(2);
        TreeNode<int> *n3 = root->setRightChild(3);
        TreeNode<int> *n4 = n2->setLeftChild(4);
        int factor = TreeNode<int>::getBalanceFactor(root);
        std::cout << factor << '\n';

        TreeNode<int> *n5 = n4->setRightChild(5);
        factor = TreeNode<int>::getBalanceFactor(root);
        std::cout << factor << '\n';
    }

    static void isBST() {
        TreeNode<int> *root = new TreeNode(2);
        TreeNode<int> *n2 = root->setLeftChild(1);
        TreeNode<int> *n3 = root->setRightChild(3);
        std::cout << TreeNode<int>::isBST(root) << '\n'; // true
        TreeNode<int> *n4 = n2->setLeftChild(4);
        std::cout << TreeNode<int>::isBST(root) << '\n'; // false
    }

    static void successor() {
        TreeNode<int> *root = new TreeNode(3);
        TreeNode<int> *n2 = root->setLeftChild(2);
        TreeNode<int> *n3 = root->setRightChild(4);
        TreeNode<int> *n4 = n2->setLeftChild(0);
        TreeNode<int> *n5 = n4->setRightChild(1);
        std::cout << n4->successor(root)->getValue() << '\n';
        // without inorder recursion:
        // 1. node->rchild->lchild->...
        // 2. node->rchild if (nullptr == node->rchild->lchild)
        // 3. if (nullptr == node->rchild), check node's fathers
        //   1. node->father if (node == node->father->lchild)
        //   2. node->father->father... until if (...->father == ...father->father->lchild)
        //   3. no successor if node is at right-bottom (contains largest value)
    }

    static void compileOrder() {
        std::string projects[] = {"a", "b", "c", "d", "e", "f"};
        std::pair<std::string, std::string> dep[] = {{"a", "d"}, {"f", "b"}, {"b", "d"}, {"f", "a"}, {"d", "c"}};

        std::unordered_map<std::string, GraphNode<int> *> pros;
        for (size_t i = 0; i < 6; ++i) pros[projects[i]] = new GraphNode(0);
        for (size_t i = 0; i < 5; ++i) {
            auto &px = pros[dep[i].first], &py = pros[dep[i].second];
            px->getConnects(py);
            py->setValue(1 + py->getValue());
        }

        while (!pros.empty()) {
            std::vector<std::string> tmp;
            for (auto &&p : pros) {
                if (0 == p.second->getValue()) {
                    std::cout << p.first << '\n';
                    for (auto &&p2 : p.second->getConnects()) {
                        p2->setValue(p2->getValue() - 1);
                    }
                    tmp.push_back(p.first);
                }
            }
            for (auto &&name : tmp) pros.erase(name);
        }
    }

    static void findFirstCommonAncestor() {
        TreeNode<int> *root = new TreeNode(1);
        TreeNode<int> *n2 = root->setLeftChild(2);
        TreeNode<int> *n3 = root->setRightChild(3);
        TreeNode<int> *n4 = n2->setLeftChild(4);
        TreeNode<int> *n5 = n4->setRightChild(5);
        std::cout << TreeNode<int>::findFirstCommonAncestor(root, n2, n5)->getValue() << '\n'; // 2
        // std::cout << TreeNode<int>::findFirstCommonAncestor(root, n3, n5)->getValue() << '\n'; // 1
    }

    static void bstSequence() {
        int array[] = {1, 2, 3, 4};
        auto *root = TreeNode<int>::buildBST(array, 0, 4);
        auto seqs = root->getAllOriginInputSeqs();
        std::cout << seqs.size() << '\n';
        for (auto &&seq : seqs) { // [3 4 2 1], [3 2 4 1], [3 2 1 4]
            for (auto &&v : seq) std::cout << v << ' ';
            std::cout << '\n';
        }
    }

    static void checkSubtree() {
        int array1[] = {7, 8, 9};
        auto *root1 = TreeNode<int>::buildBST(array1, 0, 3);
        int array2[] = {1, 2, 3, 4, 6, 7, 8, 9};
        auto *root2 = TreeNode<int>::buildBST(array2, 0, 8);
        std::cout << root1->isSubtree(root2) << '\n'; // true
    }

    static void randomNode() {
        RandomBinaryTree<int> rbt;
        rbt.insertNode(1);
        rbt.insertNode(2);
        std::cout << rbt.find(2) << '\n';
        std::cout << rbt.find(3) << '\n';
        rbt.insertNode(3);
        rbt.insertNode(4);
        rbt.deleteNode(3);
        rbt.insertNode(5);
        rbt.insertNode(6);
        for (size_t i = 0; i < 10; ++i) std::cout << rbt.getRandomNode() << (9 == i ? "\n" : " ");
    }

    static void sumPath() {
        int array[] = {1, 2, 3, 4, 6, 7, 8, 9};
        auto *root = TreeNode<int>::buildBST(array, 0, 8);
        auto res = TreeNode<int>::sumPath(root, 6);
        std::cout << res.size() << '\n';
        for (auto &&path : res) {
            for (auto &&v : path) std::cout << v << ' ';
            std::cout << '\n';
        }
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
