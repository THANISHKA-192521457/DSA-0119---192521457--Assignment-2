// Compile only to inspect the diagnostic. Do not run this program.
// Returning a reference to local variable x creates a dangling reference.
int& unsafeLocal() {
    int x = 10;
    return x;
}
int main() { return unsafeLocal(); }
