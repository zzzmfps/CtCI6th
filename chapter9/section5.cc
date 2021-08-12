#include <bits/stdc++.h>

class Section5 {
public:
    static void insertBits(int n, int m, int i, int j) {
        int mask = ~(((1 << (j - i + 1)) - 1) << i);
        m <<= i;
        n = n & mask | m;
        std::cout << n << '\n';
    }

    static void binaryDouble(double val) {
        std::string bin = "0.";
        double x = 0.5;
        for (size_t i = 0; i < 32; ++i) {
            bin += x <= val ? "1" : "0";
            if (x <= val) val -= x;
            x /= 2.0;
        }
        std::cout << (0.0 == val ? bin : "ERROR") << '\n';
    }

    static void longestConsecutiveOnes(int x) {
        std::vector<int> counts = {x & 1};
        int mask = 1;
        while (x >>= 1) {
            if (x & 1) {
                counts.back() += 1;
            } else {
                counts.push_back(0);
            }
        }
        int max = 0;
        for (size_t i = 1; i < counts.size(); ++i) {
            max = std::max(max, counts[i - 1] + counts[i]);
        }
        std::cout << 1 + max << '\n';
    }

    static void nextNumber(int x) {
        int mask = 1;
        if (x & 1) {
            while (x & mask) mask <<= 1;
            x = (x | mask) & ~(mask >> 1);
        } else {
            while (!(x & mask)) mask <<= 1;
            x = (x & ~mask) | (mask >> 1);
        }
        std::cout << x << '\n';
    }

    static void convertSteps(int x, int y) {
        int z = x ^ y, count = 0;
        while (z) {
            count += (z & 1);
            z >>= 1;
        }
        std::cout << count << '\n';
    }

    static void swapOddAndEven(int x) {
        const int a = 0x55555555, b = 0xaaaaaaaa;
        x = ((a & x) << 1) | ((b & x) >> 1);
        std::cout << x << '\n';
    }

    static void drawLine(std::vector<char> &screen, int width, int x1, int x2, int y) {
        int height = (screen.size() << 6) / width;
        if (y >= height) return;
        int index = (width >> 3) * y + (x1 >> 3);
        screen[index++] |= 255 >> (x1 & 7);
        for (size_t i = (x2 >> 3) - (x1 >> 3); i > 1; --i) {
            screen[index++] = 255;
        }
        screen[index] |= 255 << (7 ^ (x2 & 7));
    }
};

int main(int argc, char const *argv[]) {
    return 0;
}
