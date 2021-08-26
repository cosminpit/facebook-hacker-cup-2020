#include <string>
#include <fstream>
using namespace std;

int main() {
    ifstream f("in.txt");
    ofstream g("out.txt");
    int nTests; f >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n, diff = 0; f >> n;
        string s; f >> s;
        for (char c: s) diff += (c == 'A') ? +1 : -1;
        g << "Case #" << test << ": " << ((abs(diff) == 1) ? 'Y' : 'N') << "\n";
    }
    return 0;
}
