#include <iostream>
#include <queue>
#include <stack>
#include <string>

template <typename T>
class MinStack {
private:
    std::stack<std::pair<T, T>> st;

public:
    void push(T value) {
        T min = this->st.empty() ? value : std::min(value, this->st.top().second);
        this->st.emplace(value, min);
    }

    T min() {
        return this->st.top().second;
    }

    void pop() {
        if (this->st.empty()) return;
        this->st.pop();
    }
};

template <typename T, int MAX>
class SetOfStacks {
private:
    static constexpr int MAX_SIZE = MAX;

    std::vector<std::stack<T>> sts = {std::stack<T>()};

public:
    void push(T value) {
        if (SetOfStacks::MAX_SIZE == this->sts.back().size()) this->sts.push_back(std::stack<T>());
        this->sts.back().push(value);
    }

    T top() {
        this->shrink();
        return this->sts.back().top();
    }

    void pop() {
        this->shrink();
        this->sts.back().pop();
    }

    void popAt(int index) {
        if (index >= this->sts.size()) return;
        this->sts[index].pop();
    }

private:
    void shrink() {
        while (this->sts.size() > 0 && this->sts.back().empty()) {
            this->sts.pop_back();
        }
    }
};

template <typename T>
class QueueUsingTwoStacks {
private:
    std::stack<T> st1, st2;

public:
    void push(T value) {
        this->st2.push(value);
    }

    T front() {
        if (this->st1.empty()) {
            while (!this->st2.empty()) {
                this->st1.push(this->st2.top());
                this->st2.pop();
            }
        }
        return this->st1.top();
    }

    void pop() {
        this->front();
        this->st1.pop();
    }
};

class AnimalAdopt {
private:
    size_t counter = 0;
    std::queue<std::pair<size_t, std::string>> cats, dogs;

public:
    void enqueue(std::string name, bool isCat) {
        (isCat ? this->cats : this->dogs).emplace(this->counter++, name);
    }

    std::string dequeueAny() {
        if (this->cats.empty() && this->dogs.empty()) return "";
        bool cat;
        if (this->cats.empty() || this->dogs.empty()) {
            cat = this->dogs.empty();
        } else {
            cat = this->cats.front().first < this->dogs.front().first;
        }
        return this->dequeue(cat ? this->cats : this->dogs);
    }

    std::string dequeueCat() {
        if (this->cats.empty()) return "";
        return this->dequeue(this->cats);
    }

    std::string dequeueDog() {
        if (this->dogs.empty()) return "";
        return this->dequeue(this->dogs);
    }

private:
    std::string dequeue(std::queue<std::pair<size_t, std::string>> &q) {
        std::string name = q.front().second;
        q.pop();
        return name;
    }
};

class Section3 {
public:
    static void minStack() {
        MinStack<int> ms;
        ms.push(5);
        ms.push(2);
        ms.push(3);
        ms.push(1);
        std::cout << ms.min() << '\n';
        ms.pop();
        std::cout << ms.min() << '\n';
    }

    static void setofStacks() {
        SetOfStacks<int, 2> ss;
        ss.push(1);
        ss.push(2);
        ss.push(3);
        ss.popAt(0);
        ss.pop();
        std::cout << ss.top() << '\n';
    }

    static void queueUsingTwoStacks() {
        QueueUsingTwoStacks<int> q;
        q.push(3);
        q.push(2);
        q.pop();
        q.push(1);
        std::cout << q.front() << '\n';
    }

    template <typename T>
    static void stackSort(std::stack<T> &st) {
        std::stack<T> tmp;
        T min = st.top();
        while (!st.empty()) {
            min = std::min(min, st.top());
            tmp.push(st.top());
            st.pop();
        }
        bool skip = true;
        while (!tmp.empty()) {
            if (tmp.top() == min && skip) {
                skip = false;
            } else {
                st.push(tmp.top());
            }
            tmp.pop();
        }
        st.push(min);
    }

    static void animalAdopt() {
        AnimalAdopt aa;
        aa.enqueue("cat1", true);
        aa.enqueue("dog1", false);
        aa.enqueue("dog2", false);
        std::cout << aa.dequeueAny() << '\n';
        std::cout << aa.dequeueCat() << '\n';
        std::cout << aa.dequeueDog() << '\n';
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
