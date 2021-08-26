#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_map>
using namespace std;

struct Tree {
    int x, h;
};

int main() {
    ifstream f("in.txt");
    ofstream g("out.txt");
    int nTests; f >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n; f >> n;
        vector<Tree> trees(n);
        unordered_map<int, int> best;

        for (auto &t: trees) f >> t.x >> t.h;
        sort(trees.begin(), trees.end(), [&](const Tree &a, const Tree &b) {
             return a.x < b.x;
        });

        int ans = 0;
        for (const auto &t: trees) {
            best[t.x + t.h] = max(best[t.x + t.h], best[t.x] + t.h);
            best[t.x] = max(best[t.x], best[t.x - t.h] + t.h);
            ans = max({ans, best[t.x], best[t.x + t.h]});
        }
        g << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}
