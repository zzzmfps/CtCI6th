#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

class Section8 {
public:
    static void threeSteps(int n = 20) {
        using LL = long long;
        std::vector<LL> cache(1 + n);
        auto helper = [&](auto &&self, int i) -> LL {
            if (i < 0) return 0;
            if (0 == i) return 1;
            if (0 == cache[i]) cache[i] = self(self, i - 1) + self(self, i - 2) + self(self, i - 3);
            return cache[i];
        };
        LL res = helper(helper, n);
        std::cout << "Result: " << res << '\n';
    }

    static void robot(const std::vector<std::vector<bool>> &grid) {
        if (grid.empty() || grid[0].empty()) return;
        int row = grid.size(), col = grid[0].size();

        using Point = std::pair<int, int>;
        std::vector<std::vector<Point>> paths;

        std::vector<Point> cur;
        std::vector<std::vector<bool>> visited(row, std::vector<bool>(col));
        auto helper = [&](auto &&self, int x, int y) {
            if (!grid[x][y] || visited[x][y]) return;
            if (x == row - 1 && y == col - 1) {
                paths.push_back(cur);
                paths.back().emplace_back(row - 1, col - 1);
                return;
            }
            cur.emplace_back(x, y);
            visited[x][y] = true;
            if (x > 0) self(self, x - 1, y);
            if (y > 0) self(self, x, y - 1);
            if (x + 1 < row) self(self, x + 1, y);
            if (y + 1 < col) self(self, x, y + 1);
            visited[x][y] = false;
            cur.pop_back();
        };
        helper(helper, 0, 0);

        for (auto &&path : paths) {
            for (size_t i = 0; i < path.size(); ++i) {
                auto [x, y] = path[i];
                std::cout << (i ? " " : "") << "(" << x << ", " << y << ")";
            }
            std::cout << '\n';
        }
    }

    static void magicIndex(const std::vector<int> &array) {
        if (array.empty()) return;

        int magic = -1;
        bool isAscending = array.front() < array.back();
        auto helper = [&](auto &&self, int l, int r) -> bool {
            if (l >= r) return false;
            int mid = l + (r - l) / 2;
            if (mid == array[mid]) {
                magic = mid;
                return true;
            }
            bool flag = false;
            if (mid < array[mid]) {
                if (isAscending) flag |= self(self, l, mid);
                if (!flag) flag |= self(self, mid + 1, r);
            } else {
                flag |= self(self, l, mid);
                if (isAscending && !flag) flag |= self(self, mid + 1, r);
            }
            return flag;
        };
        helper(helper, 0, array.size());

        std::cout << magic << '\n';
    }

    template <typename T>
    static void subsets(std::set<T> set) {
        std::set<std::set<T>> sets({{}});

        auto helper = [&](auto &&self) -> void {
            if (set.empty()) return;
            sets.insert(set);
            if (1 == set.size()) return;
            std::set<T> tmp(set);
            for (auto it = tmp.begin(); it != tmp.end(); ++it) {
                set.erase(*it);
                self(self);
                set.insert(*it);
            }
        };
        helper(helper);

        for (auto &&s : sets) {
            for (auto &&val : s) std::cout << val << ' ';
            std::cout << '\n';
        }
    }

    static void multiply(size_t x, size_t y) {
        assert(x > 0 && y > 0);
        if (1 == x || 1 == y) {
            std::cout << (1 == x) ? y : x << '\n';
            return;
        }

        if (x < y) { // maybe not neccessary
            y = (x += y) - y;
            x -= y;
        }

        long long res = 0LL;
        while (y) {
            int leftShift = 0;
            while ((1 << (leftShift + 1)) <= y) ++leftShift;
            res += static_cast<long long>(x) << leftShift;
            y -= (1 << leftShift);
        }
        std::cout << res << '\n';
    }

    static void hanoiTower(int n) {
        // auto solve = [](auto &&self, int x) -> long long {
        //     if (1 == x) return 1LL;
        //     return 1LL + 2 * self(self, x - 1);
        // };
        // std::cout << solve(solve, n) << '\n';
        std::cout << static_cast<long long>(std::pow(2, n) - 1) << '\n';
    }

    static void combinationsNoRepeat(const std::string &str) {
        std::vector<std::string> res = {""};
        for (size_t i = 0; i < str.size(); ++i) {
            char ch = str[i];
            std::vector<std::string> tmp;
            for (auto &&r : res) {
                tmp.push_back(r);
                for (size_t j = 0; j <= r.size(); ++j) {
                    tmp.push_back(r);
                    tmp.back().insert(tmp.back().begin() + j, ch);
                }
            }
            res = std::move(tmp);
        }
        for (size_t i = 0; i < res.size(); ++i) std::cout << '\t' << i << ": " << res[i] << '\n';
    }

    static void combinationsWithRepeat(const std::string &str) {
        std::vector<std::string> res = {""};
        for (size_t i = 0; i < str.size(); ++i) {
            char ch = str[i];
            std::vector<std::string> tmp;
            for (auto &&r : res) {
                tmp.push_back(r);
                for (size_t j = 0; j <= r.size(); ++j) {
                    tmp.push_back(r);
                    tmp.back().insert(tmp.back().begin() + j, ch);
                }
            }
            res = std::move(tmp);
        }
        std::set<std::string> set(res.begin(), res.end());
        for (size_t i = 0; i < set.size(); ++i) std::cout << '\t' << i << ": " << *std::next(set.begin(), i) << '\n';
    }

    static void parentheses(int n) {
        if (n < 0) return;
        if (0 == n) {
            std::cout << "0\n";
            return;
        }
        std::set<std::string> res({"()"});
        while (--n) {
            std::set<std::string> tmp;
            for (auto &&par : res) {
                for (size_t i = 0; i < par.size(); ++i) {
                    if (i > 1 && '(' == par[i - 2] && ')' == par[i - 1]) continue;
                    std::string n = par.substr(0, i) + "()" + par.substr(i);
                    tmp.insert(n);
                }
            }
            res = std::move(tmp);
        }
        std::cout << res.size() << '\n';
        for (auto &&par : res) std::cout << par << ", ";
        std::cout << '\n';
    }

    static void fillColor(std::vector<std::vector<int>> &grid, int row, int col, int target) {
        if (grid.empty() || grid[0].empty()) return;
        int prev = grid[row][col];
        if (prev == target) return;

        grid[row][col] = target;
        std::queue<std::pair<int, int>> q({std::make_pair(row, col)});

        static int delta[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        auto helper = [&](int r, int c) -> void {
            if (r < 0 || c < 0 || r == grid.size() || c == grid[0].size()) return;
            if (prev != grid[r][c]) return;
            grid[r][c] = target;
            q.push(std::make_pair(r, c));
        };

        while (!q.empty()) {
            auto [r, c] = q.front();
            for (size_t i = 0; i < 4; ++i) helper(r + delta[i][0], c + delta[i][1]);
            q.pop();
        }
    }

    static int coins(std::vector<int> counts, int n) {
        static int coinValues[] = {1, 5, 10, 25};

        int res = 0;

        int min1 = std::min(counts[3], n / 25);
        for (size_t i = 0; i <= min1; ++i) {
            int min2 = std::min(counts[2], n / 10);
            for (size_t j = 0; j <= min2; ++j) {
                int min3 = std::min(counts[1], n / 5);
                for (size_t k = 0; k <= min3; ++k) {
                    res += (n <= counts[0]);
                    // if (n <= counts[0]) std::cout << i << ' ' << j << ' ' << k << ' ' << n << '\n';
                    n -= 5;
                }
                // n += 5 * (min3 + 1);
                // n -= 10;
                n += 5 * min3 - 5;
            }
            // n += 10 * (min2 + 1);
            // n -= 25;
            n += 10 * min2 - 15;
        }

        return res;
    }

    static void eightQueens() {
        short col = 0, luRb = 0, ruLb = 0;
        short grid[8] = {};
        short count = 0;

        auto printGrid = [&]() {
            std::cout << std::setw(2) << count << ": ";
            for (size_t r = 0; r < 8; ++r) {
                for (size_t c = 0; c < 8; ++c) {
                    if (grid[r] & (1 << c)) std::cout << '(' << r << ", " << c << ')';
                }
            }
            std::cout << '\n';
        };
        auto helper = [&](auto &&self, int r) {
            if (8 == r) {
                ++count, printGrid();
                return;
            }
            for (size_t c = 0; c < 8; ++c) {
                int ec = 1 << c;
                if (col & ec) continue;

                int ei = 1 << (7 + r - c), ej = 1 << (r + c);
                if ((luRb & ei) || (ruLb & ej)) continue;

                col |= ec, luRb |= ei, ruLb |= ej, grid[r] |= ec;
                self(self, r + 1);
                col ^= ec, luRb ^= ei, ruLb ^= ej, grid[r] ^= ec;
            }
        };

        helper(helper, 0);
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
