#include <ctime>
#include <iostream>
#include <random>
#include <string>

class Section6 {
public:
    static void heavierBottle() {
        std::string desc = R"(较重的药丸
        前提1：天平能显示两边托盘的具体重量差值
        前提2：各个药瓶内含的药丸能够取出且数量足够
        将 20 瓶药丸分成 A,B 两堆，并分别编号为 A1,A2,...,A10,B1,B2,...,B10 (Ai,Bi)
        根据各自的编号大小，从药瓶中取出相应 i 颗药丸放在对应的托盘上
        根据天平测量结果，较重的那瓶药丸位于重量较大的一侧，且重量差为 0.k 克，k 为其编号)";
        std::cout << desc << '\n';
    }

    static void basketball() {
        std::string desc = R"(篮球问题
        玩法1 获胜概率 f1 = p
        玩法2 获胜概率 f2 = 1 - (1-p)^3 - C(1,3)*p*(1-p)^2 = 3p^2 - 2p^3
        令 f1 > f2, 即 p > 3p^2 - 2p^3, 可得 p < 0.5
        因此，当 p < 0.5 时选择玩法1；p > 0.5 时选择玩法2；p = 0.5 时二者等价)";
        std::cout << desc << '\n';
    }

    static void domino() {
        std::string desc = R"(多米诺骨牌
        将棋盘每个格子涂上黑色或白色，保证不存在相邻格子的颜色相同
        此时，由于对角线的两个格子不存在，不同颜色格子数量关系为 黑色+2 = 白色（或相反）
        显然，一个多米诺骨牌必然覆盖一个黑色格子和一个白色格子
        由于黑白格子数量不一，因此不可能盖住整个棋盘)";
        std::cout << desc << '\n';
    }

    static void antsOnEdges() {
        std::string desc = R"(三角形上的蚂蚁
        每只蚂蚁可选择的方向仅有两个，且相同：顺时针/逆时针
        当且仅当所有蚂蚁均选择顺时针（或逆时针）时，不发生碰撞，可能性为 2 种，与蚂蚁数量无关
        可知，当有 n 只蚂蚁时，碰撞概率为 1-2/(2^n)。因此当 n=3 时，概率为 1-2/(2^3) = 3/4)";
        std::cout << desc << '\n';
    }

    static void pots() {
        std::string desc = R"(水壶问题
        令 A 为 3 夸脱水壶，B 为 5 夸脱水壶，则
        1 夸脱：装满 A，将 A 中的水全部倒入 B；再次装满 A，将 A 中的水倒入 B 直至 B 装满。此时 A 有 1 夸脱水
        2 夸脱：装满 B，将 B 中的水倒入 A 直至 A 装满。此时 B 有 2 夸脱水
        3/5 夸脱：装满 A 或 B
        4 夸脱：先获得 1 夸脱的水（位于 A）并倒空 B；将 A 中的水全部倒入 B；装满 A 并再次全部倒入 B。此时 B 有 4 夸脱水)";
        std::cout << desc << '\n';
    }

    static void blueEye() {
        std::string desc = R"(蓝眸岛
        前提：岛上的每个有蓝眼睛的人都能正确地推理当前的情况
        令岛上一共有 n 个人有蓝眼睛，n>=1
        当 n = 1 时，需要 1 天。因为唯一有蓝眼睛的人会发现别人都没有蓝眼睛，因此会意识到自己有蓝眼睛，于是当天离岛
        当 n = 2 时，需要 2 天。有蓝眼睛的两人会等待对方离岛；当第二天发现对方没有离岛时，会知道对方的想法与自己相同，
                              即对方看到了自己的蓝眼睛，在等待自己离开，于是他们将在第二天离岛
        当 n = 3 时，需要 3 天。因为有蓝眼睛的人会等待另外两人两天，直到第三天才意识到自己也有蓝眼睛
        以此类推，对于 n 个有蓝眼睛的人，离岛时间为 n 天，且所有的 n 个人均在第 n 天离岛)";
        std::cout << desc << '\n';
    }

    static void genderRatio() {
        std::string desc = R"(大灾难
        令最终每个家庭生了 n 个孩子，则
        当 n = 1 时，概率 p=0.5, 男孩 0 个，女孩 1 个
        当 n = 2 时，概率 p=0.25，男孩 1 个，女孩 1 个
        当 n = 3 时，概率 p=0.125，男孩 2 个，女孩 1 个
        ...
        当 n = k 时，概率 p=0.5^k，男孩 k-1 个，女孩 1 个
        因此，在该政策下，每个家庭生出后代的数量期望分别为：
        男孩 = 0.5*0 + 0.25*1 + 0.125*2 + 0.0625*3 + ... + 0.5^k*(k-1) = 1.0 - 0.5^(k-1)
        女孩 = 0.5*1 + 0.25*1 + 0.125*1 + ... + 0.5^k*1 = 1.0 - 0.5^(k-1)
        所以，最终男女比为 1:1。且当 k -> +inf 时，男孩和女孩的期望均趋于 1)";
        std::cout << desc << '\n';
    }

    static void genderRatioSimulation(int family = 10000) {
        std::default_random_engine engine(std::time(0));
        std::bernoulli_distribution dist(0.5);

        int m = 0, f = 0;
        for (size_t i = 0; i < family; ++i) {
            while (dist(engine)) ++m;
            ++f;
        }
        std::cout << "Family: " << family << " boys: " << m << " girls: " << f << " ratio: " << double(m) / f << '\n';
    }

    static void throwEggs() {
        std::string desc = R"(扔鸡蛋问题
        当第 1 个鸡蛋破碎时，第 2 个鸡蛋只能在可能区间内逐楼层尝试，不能跳过任一楼层
        因此需要令第 2 个鸡蛋面临的区间足够小
        又因为第 1 个鸡蛋在每次跳过若干楼层尝试时也计入扔鸡蛋次数，因为可能区间应当随第 1 个鸡蛋的尝试次数的增加而减少
        于是，令第 1 个鸡蛋的尝试楼层数为 [14 27 39 50 60 69 77 84 90 95]
        极端情况如下：
        N= 13，尝试次数为 1+13=14
        N= 27，尝试次数为 2+12=14
        ...
        N= 94，尝试次数为 10+4=14
        N=100，尝试次数为 10+1+2=13 (第 1 个鸡蛋没有摔碎，可以先检查 98 层分割区间)
        综上所述，最差情况下扔鸡蛋的次数最少为 14 次)";
        std::cout << desc << '\n';
    }

    static void cabinets() {
        std::string desc = R"(100 个储物柜
        从关闭状态开始，第 k 轮会影响能被 k 整除的所有柜子
        因此，对于任意编号为 n 的柜子，有 m 个数能将其整除，则
        当 m 是偶数时，n 号柜子最终状态为 关闭
        当 m 是奇数时，n 号柜子最终状态为 打开
        同时注意到对于整数 n 而言，若状态为打开，意味着除去 1,n 之外，有奇数个数能整除 n；
        对于任意 1<a<n 而言，一定存在一个 b，满足 1<b<n 且 a*b=n；
        则在奇数情况下，显然多出一个数 a'，此时，与之对应的 b' 是其本身；
        因此，该问题的结果是 不大于储物柜个数 k 的全部平方数)";
        std::cout << desc << '\n';
    }

    static void cabinetsSimulation(int k = 100) {
        std::vector<int> nums(k + 1, 1);
        for (size_t i = 2; i <= k; ++i) {
            for (size_t j = i; j <= k; j += i) {
                nums[j] ^= 1;
            }
        }
        for (size_t i = 1; i <= k; ++i)
            if (nums[i]) std::cout << i << ' ';
        std::cout << '\n';
    }

    static void cabinetsDirect(int k = 100) {
        for (size_t i = 1; i * i <= k; ++i) std::cout << i * i << ' ';
        std::cout << '\n';
    }

    static void toxicSoda() {
        std::string desc = R"(有毒的苏打水
        描述1：每天只能进行一次测试：测试的最小时间单位是天，不能继续分割到小时
        描述2：用时 7 天才可得到测试结果：等待的 6 天中还可以继续往试纸上滴苏打水（有什么用？）
        注意到 1000 < 2^10，其中 1000 为苏打水的瓶数，10 为试纸的条数

        将苏打水编号为 i = 0,1,2,...,998,999，将试纸编号为 j = 0,1,2,...,8,9
        对于试纸 j，第 1 天倒入编号满足 1 == i & (1<<j) 的苏打水（编号二进制表示的第 j 位为 1）

        从第 1 天开始测试，第 8 天有试纸变黄
        设第 8 天变黄试纸的编号为 j'=n1,n2,...,nk，则
        有毒苏打水的编号的二进制表示的第 n1,n2,...,nk 位为 1，其余位为 0
        故最少用时为 8 天，且不存在最好/最坏情况（所有情况用时相同）)";
        std::cout << desc << '\n';
    }

    static void toxicSodaSimulation() {
        int index = std::rand() % 1000;

        struct Soda {
            int index;
            bool toxic;
            Soda(int i, bool t) : index(i), toxic(t) {}
        };

        std::vector<std::vector<Soda>> trial(10);
        for (size_t j = 0; j < 10; ++j) { // day 1
            int mask = 1 << j;
            for (size_t i = 0; i < 1000; ++i)
                if (i & mask) trial[j].push_back(Soda(i, (i == index)));
        }
        // wait until day 8
        std::vector<int> nk;
        for (size_t j = 0; j < 10; ++j) {
            for (auto &&s : trial[j]) {
                if (s.toxic) {
                    nk.push_back(j);
                    break;
                }
            }
        }

        int res = 0;
        for (auto &&bit : nk) res |= (1 << bit);

        std::cout << "index: " << index << "\tresult: " << res << '\n';
    }
};

int main(int argc, char const *argv[]) {
    Section6::heavierBottle();
    Section6::basketball();
    Section6::domino();
    Section6::antsOnEdges();
    Section6::pots();
    Section6::blueEye();
    Section6::genderRatio();
    // Section6::genderRatioSimulation();
    Section6::throwEggs();
    Section6::cabinets();
    // Section6::cabinetsSimulation();
    // Section6::cabinetsDirect();
    Section6::toxicSoda();
    // Section6::toxicSodaSimulation();
    return 0;
}
