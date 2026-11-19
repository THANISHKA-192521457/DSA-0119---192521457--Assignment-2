#include <iostream>
#include <array>
#include <chrono>
using namespace std;
using namespace std::chrono;

class ShiftHistory {
    array<int, 10> data{};
    int count = 0;
public:
    void add(int x) {
        if (count < 10) data[count++] = x;
        else {
            for (int i = 1; i < 10; ++i) data[i-1] = data[i];
            data[9] = x;
        }
    }
    int newest() const { return data[9]; }
};
class CircularHistory {
    array<int, 10> data{};
    int count = 0, next = 0;
public:
    void add(int x) {
        data[next] = x;
        next = (next + 1) % 10;
        if (count < 10) ++count;
    }
    int newest() const { return data[(next + 9) % 10]; }
};
template<class History>
long long test(const char* label) {
    History h;
    auto start = steady_clock::now();
    for (int i = 0; i < 2000000; ++i) h.add(i);
    auto stop = steady_clock::now();
    cout << label << " newest=" << h.newest() << '\n';
    return duration_cast<microseconds>(stop-start).count();
}
int main() {
    auto shiftTime = test<ShiftHistory>("Shift array");
    auto circularTime = test<CircularHistory>("Circular buffer");
    cout << "Shift insertion test time (us): " << shiftTime << '\n';
    cout << "Circular insertion test time (us): " << circularTime << '\n';
    cout << "Both retain the latest 10 values; timings vary by machine/compiler.\n";
}
