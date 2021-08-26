#include <deque>
#include <vector>
#include <cstdint>
#include <fstream>
using namespace std;

int main() {
    ifstream f("in.txt");
    ofstream g("out.txt");
    int nTests; f >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n, m; f >> n >> m;
        vector<int64_t> c(n);
        deque<int> q; q.push_back(0);

        for (int i = 0; i < n; i++) f >> c[i];
        c[0] = c[n - 1] = 0;

        int64_t ans = (n == 1) ? 0LL : -1LL;
        for (int i = 1; i < n; i++) {
            while (!q.empty() && q.front() + m < i) q.pop_front();
            if (q.empty()) break;

            c[i] += c[q.front()];
            if (i == n - 1) ans = c[q.front()];
            if (c[i] == c[q.front()]) continue;

            while (!q.empty() && c[i] <= c[q.back()]) q.pop_back();
            q.push_back(i);
        }
        g << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}
