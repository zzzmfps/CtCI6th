#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

class Section1 {
private:
    static constexpr int ALPHA = 26;
    static constexpr int ASCII = 128;

public:
    static bool isAllCharsUnique(const std::string &str) {
        int counts[Section1::ASCII] = {};
        for (auto &&ch : str)
            if (++counts[ch] > 1) return false;
        return true;
    }

    static bool isRearrangedStrings(const std::string &str1, const std::string &str2) {
        if (str1.length() != str2.length()) {
            return false;
        }
        int counts[Section1::ASCII] = {};
        for (size_t i = 0; i < str1.length(); ++i) {
            ++counts[str1[i]];
            --counts[str2[i]];
        }
        return std::all_of(counts, counts + Section1::ASCII, [](int cnt) { return 0 == cnt; });
    }

    static void toUrlStyle(std::string &str, int length) {
        int spaces = std::count(str.begin(), str.begin() + length, ' ');
        int i = length, j = length + 2 * spaces - 1;
        while (--i > -1) {
            if (' ' != str[i]) {
                str[j--] = str[i];
                continue;
            }
            str[j--] = '0';
            str[j--] = '2';
            str[j--] = '%';
        }
    }

    static bool isPermutationOfPalindrome(const std::string &str) {
        int counts[Section1::ALPHA] = {};
        for (auto &&ch : str)
            if (isalpha(ch)) ++counts[(ch | 32) - 97];
        return std::count_if(counts, counts + Section1::ALPHA, [](int cnt) { return cnt & 1; }) < 2;
    }

    static bool isConvertableWithinOneStep(const std::string &str1, const std::string &str2) {
        int size1 = str1.length(), size2 = str2.length();
        if (abs(size1 - size2) > 1) return false;

        bool edited = false;
        size_t i = 0, j = 0;
        while (i < size1 && j < size2) {
            if (str1[i] == str2[j]) {
                ++i, ++j;
                continue;
            }
            if (edited) return false;
            edited = true;
            if (str1.length() == str2.length()) {
                ++i, ++j;
            } else {
                ++(str1.length() > str2.length() ? i : j);
            }
        }
        return true;
    }

    static std::string compressString(const std::string &str) {
        std::string res = "";
        int count = 0;
        char last = str[0];
        for (auto &&ch : str) {
            if (ch == last) {
                ++count;
                continue;
            }
            res.append({last, char(count + 48)});
            count = 1, last = ch;
        }
        res.append({last, char(count + 48)});
        return (res.length() < str.length()) ? res : str;
    }

    static void rotateMatrixClockwise(std::vector<std::vector<int>> &matrix) {
        int n = matrix.size();
        for (size_t i = 0; i < n / 2; ++i) {
            for (size_t j = i + 1; j < n - i; ++j) {
                int tmp = matrix[i][j];
                matrix[i][j] = matrix[n - 1 - j][i];
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
                matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
                matrix[j][n - 1 - i] = tmp;
            }
        }
    }

    static void zeroMatrix(std::vector<std::vector<int>> &matrix) {
        std::unordered_set<int> row, col;
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[0].size(); ++j) {
                if (0 == matrix[i][j]) {
                    row.insert(i);
                    col.insert(j);
                }
            }
        }
        for (auto &&r : row) {
            for (size_t j = 0; j < matrix[0].size(); ++j) {
                matrix[r][j] = 0;
            }
        }
        for (auto &&c : col) {
            for (size_t i = 0; i < matrix.size(); ++i) {
                matrix[i][c] = 0;
            }
        }
    }

    static bool isSubstring(const std::string &str1, const std::string &str2) {
        size_t index = 0;
        while (std::string::npos != (index = str1.find(str2.front(), index))) {
            if (str1.length() - index < str2.length()) break;
            bool flag = true;
            for (size_t i = 0; i < str2.length(); ++i) {
                if (str2[i] != str1[i + index]) {
                    flag = false;
                    break;
                }
            }
            if (flag) return true;
            ++index;
        }
        return false;
    }

    static bool isRotated(const std::string &str1, const std::string &str2) {
        std::string tmp = str1 + str1; // .substr(0, str1.size() - 1);
        return Section1::isSubstring(tmp, str2);
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
