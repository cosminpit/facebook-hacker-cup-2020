#include <string>
#include <fstream>
using namespace std;

int main() {
    ifstream f("in.txt");
    ofstream g("out.txt");
    int nTests; f >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n; f >> n;
        string in, out; f >> in >> out;
        g << "Case #" << test << ":\n";
        for (int i = 0; i < n; i++) {
            string ans(n, 'N'); ans[i] = 'Y';
            for (int j = i + 1; j <  n && out[j-1] == 'Y' && in[j] == 'Y'; j++) ans[j] = 'Y';
            for (int j = i - 1; j >= 0 && out[j+1] == 'Y' && in[j] == 'Y'; j--) ans[j] = 'Y';
            g << ans << "\n";
        }
    }
    return 0;
}
