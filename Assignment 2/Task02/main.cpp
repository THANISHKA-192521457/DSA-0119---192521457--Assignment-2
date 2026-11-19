#include <iostream>
using namespace std;

int& highestMark(int marks[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) if (marks[i] > marks[best]) best = i;
    return marks[best];
}
const int& highestMarkReadOnly(const int marks[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) if (marks[i] > marks[best]) best = i;
    return marks[best];
}
int highestMarkCopy(const int marks[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) if (marks[i] > marks[best]) best = i;
    return marks[best];
}
int highestMarkIndex(const int marks[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) if (marks[i] > marks[best]) best = i;
    return best;
}
// Never return a reference to a local variable: it is destroyed at function exit.
// int& unsafeLocal() { int x = 10; return x; } // intentionally kept out of build

int main() {
    int marks[] = {78, 91, 84, 88};
    int n = 4;
    cout << "Highest before moderation: " << highestMarkReadOnly(marks, n) << '\n';
    highestMark(marks, n) += 2;
    cout << "Highest after +2: " << highestMarkCopy(marks, n) << '\n';
    int idx = highestMarkIndex(marks, n);
    cout << "Index of highest: " << idx << '\n';
    cout << "Value using index: " << marks[idx] << '\n';
    int copied = highestMarkCopy(marks, n);
    copied = 0;
    cout << "Array unchanged after changing copy: " << marks[idx] << '\n';
}
