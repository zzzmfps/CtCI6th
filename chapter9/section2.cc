#include <bits/stdc++.h>

template <typename T>
struct Node {
    T value;
    Node *next = nullptr;

    Node(T val) : value(val) {}
    Node(const std::initializer_list<T> &ilist) {
        this->value = *ilist.begin();
        Node *tmp = this;
        for (auto i = std::next(ilist.begin()); i != ilist.end(); ++i) {
            tmp->next = new Node(*i);
            tmp = tmp->next;
        }
    }
};

class Section2 {
public:
    template <typename T>
    static void unique(Node<T> *head) {
        if (!head) return;
        std::unordered_set<T> set = {head->value};
        for (auto i = head; i->next;) {
            auto j = std::next(i);
            if (set.contains(i->next->value)) {
                i->next = i->next->next;
            } else {
                set.insert(i->next->value);
                i = i->next;
            }
        }
    }

    template <typename T>
    static Node<T> *getLastKthElement(Node<T> *head, int k) {
        if (k <= 0) return nullptr;
        auto i = head, j = head;
        while (j && k--) j = j->next;
        if (k > 0) return nullptr;
        while (j) i = i->next, j = j->next;
        return i;
    }

    template <typename T>
    static void deleteNode(Node<T> *node) {
        Node<T> *last = nullptr;
        while (node->next) {
            node->value = node->next->value;
            last = node;
            node = node->next;
        }
        last->next = nullptr;
    }

    template <typename T>
    static void partition(Node<T> *head, T pivot) {
        auto i = head;
        while (i->next && i->next->value < pivot) i = i->next;
        auto j = i->next;
        while (j->next) {
            while (j->next && j->next->value >= pivot) j = j->next;
            auto moving = j->next;
            j->next = moving->next;
            moving->next = i->next;
            i->next = moving;
        }
    }

    static Node<int> *sumOfTwoLists(Node<int> *head1, Node<int> *head2) {
        Node<int> *res = new Node(0), *cur = res;
        bool carry = false;
        for (; head1 && head2; head1 = head1->next, head2 = head2->next) {
            int sum = head1->value + head2->value + carry;
            Section2::checkSumAndCarry(sum, carry);
            cur->next = new Node(sum);
            cur = cur->next;
        }
        auto remains = (head1 ? head1 : head2);
        for (; remains; remains = remains->next) {
            int sum = remains->value + carry;
            Section2::checkSumAndCarry(sum, carry);
            cur->next = new Node(sum);
            cur = cur->next;
        }
        if (carry) cur->next = new Node(1);
        return res->next;
    }

    static Node<int> *sumOfTwoReversedLists(Node<int> *head1, Node<int> *head2) {
        std::stack<Node<int> *> st1, st2;
        auto pushToStack = [](std::stack<Node<int> *> &st, Node<int> *node) {
            while (node) {
                st.push(node);
                node = node->next;
            }
        };
        pushToStack(st1, head1), pushToStack(st2, head2);

        Node<int> *sentinel = new Node(0);
        bool carry = false;
        while (!st1.empty() && !st2.empty()) {
            auto n1 = st1.top(), n2 = st2.top();
            st1.pop(), st2.pop();
            int sum = n1->value + n2->value + carry;
            Section2::checkSumAndCarry(sum, carry);
            Section2::addNodeAfter(sentinel, sum);
        }

        auto &st = st1.empty() ? st2 : st1;
        while (!st.empty()) {
            auto n1 = st.top();
            st.pop();
            int sum = n1->value + carry;
            Section2::checkSumAndCarry(sum, carry);
            Section2::addNodeAfter(sentinel, sum);
        }
        if (carry) Section2::addNodeAfter(sentinel, 1);

        return sentinel->next;
    }

    template <typename T>
    static bool isPalindrome(Node<T> *head) {
        int length = Section2::length(head);
        std::stack<Node<T> *> st;
        for (size_t i = 0; i < length / 2; ++i) {
            st.push(head);
            head = head->next;
        }
        if (length & 1) head = head->next;
        while (!st.empty()) {
            auto &n = st.top();
            if (n->value != head->value) return false;
            st.pop();
            head = head->next;
        }
        return true;
    }

    template <typename T>
    static bool isIntersected(Node<T> *head1, Node<T> *head2) {
        int len1 = Section2::length(head1);
        int len2 = Section2::length(head2);
        auto &longer = len1 < len2 ? head2 : head1;
        for (size_t i = std::abs(len1 - len2); i > 0; --i) longer = longer->next;

        while (head1) {
            if (head1 == head2) return true;
            head1 = head1->next;
            head2 = head2->next;
        }
        return false;
    }

    template <typename T>
    static Node<T> *getHeadOfLoop(Node<T> *head) {
        std::unordered_set<Node<T> *> set;
        while (true) {
            if (set.contains(head)) break;
            set.insert(head);
            head = head->next;
        }
        return head;
    }

private:
    static void checkSumAndCarry(int &sum, bool &carry) {
        if (sum > 9) {
            sum -= 10;
            carry = true;
        } else {
            carry = false;
        }
    }

    template <typename T>
    static void addNodeAfter(Node<T> *prev, T value) {
        Node<T> *node = new Node(value);
        node->next = prev->next;
        prev->next = node;
    }

    template <typename T>
    static size_t length(Node<T> *head) {
        if (!head) return 0;
        size_t length = 1;
        while ((head = head->next)) ++length;
        return length;
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
