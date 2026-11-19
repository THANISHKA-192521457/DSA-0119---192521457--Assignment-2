#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

volatile long long sinkValue = 0;
class ClockTime {
    int h, m;
public:
    ClockTime(int hh, int mm) : h(hh), m(mm) {}
    friend inline int inlineMinutes(const ClockTime&, const ClockTime&);
    friend __attribute__((noinline)) int normalMinutes(const ClockTime&, const ClockTime&);
};
inline int inlineMinutes(const ClockTime& a, const ClockTime& b) {
    return (a.h * 60 + a.m) - (b.h * 60 + b.m);
}
__attribute__((noinline)) int normalMinutes(const ClockTime& a, const ClockTime& b) {
    return (a.h * 60 + a.m) - (b.h * 60 + b.m);
}
template<class F> void measure(const char* label, F fn, const ClockTime& a, const ClockTime& b) {
    auto start = steady_clock::now();
    long long sum = 0;
    for (int i = 0; i < 10000000; ++i) sum += fn(a, b);
    auto stop = steady_clock::now();
    sinkValue = sum;
    cout << label << ": " << duration_cast<microseconds>(stop-start).count()
         << " microseconds; checksum=" << sinkValue << '\n';
}
int main() {
    ClockTime a(9,45), b(13,10);
    measure("inline", inlineMinutes, a, b);
    measure("non-inline", normalMinutes, a, b);
}
