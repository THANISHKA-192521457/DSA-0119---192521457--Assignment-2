#include <iostream>
#include <string>
using namespace std;

struct Parcel { double weightKg; bool express; bool insured; };

double charge(int grams, bool express = false, bool insured = false) {
    double cost = grams * 0.02;
    if (express) cost += 30;
    if (insured) cost += 20;
    cout << "[int grams overload] ";
    return cost;
}
double charge(double kg, bool express = false, bool insured = false) {
    double cost = kg * 50.0;
    if (express) cost += 30;
    if (insured) cost += 20;
    cout << "[double kg overload] ";
    return cost;
}
double charge(const Parcel& p) {
    double cost = p.weightKg * 50.0;
    if (p.express) cost += 30;
    if (p.insured) cost += 20;
    cout << "[Parcel overload] ";
    return cost;
}

int main() {
    Parcel p{2.5, true, true};
    cout << "charge(2) = "; cout << charge(2) << '\n';
    cout << "charge(2.0) = "; cout << charge(2.0) << '\n';
    cout << "charge(2.0f) = "; cout << charge(2.0f) << '\n';
    cout << "charge(500, true) = "; cout << charge(500, true) << '\n';
    cout << "charge(1.5, false, true) = "; cout << charge(1.5, false, true) << '\n';
    cout << "charge(Parcel) = "; cout << charge(p) << '\n';
}
