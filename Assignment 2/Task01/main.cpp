#include <iostream>
using namespace std;

void concessionByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
    cout << "Inside value function: " << fee << '\n';
}
void concessionByReference(long long& fee, int percent) {
    fee -= fee * percent / 100;
}
void concessionByPointer(long long* fee, int percent) {
    if (fee != nullptr) *fee -= *fee * percent / 100;
}
long long returnedFee(long long fee, int percent) {
    return fee - fee * percent / 100;
}
int& bigger(int& p, int& q) { return p > q ? p : q; }
void show(int x, int y = 5, int z = 10) { cout << x + y + z << ' '; }

int main() {
    long long fee = 45000;
    cout << "Initial fee: " << fee << '\n';
    concessionByValue(fee, 10);
    cout << "After value: " << fee << '\n';
    concessionByReference(fee, 10);
    cout << "After reference: " << fee << '\n';
    concessionByPointer(&fee, 10);
    cout << "After pointer: " << fee << '\n';
    cout << "Returned fee (25% from current): " << returnedFee(fee, 25) << '\n';

    int a = 1, b = 2, c = 3;
    a += 0; b += 10; c += 10;
    cout << "Reference/pointer illustration: " << a << ' ' << b << ' ' << c << '\n';
    bigger(a, c) = 100;
    cout << "After bigger(a,c)=100: " << a << ' ' << c << '\n';
    cout << "Default arguments: ";
    show(1); show(1, 2); show(1, 2, 3); cout << '\n';
}
