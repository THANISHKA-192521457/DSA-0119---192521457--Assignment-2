# Assignment 2 Report – CO2

**Name:** S. THANISHKA  
**Register Number:** 192521457  
**Department:** B.Tech Information Technology  
**Compiler used in this build:** g++ (Debian 14.2.0-19) 14.2.0  
**Standard:** C++17  
**GitHub repository:** https://github.com/THANISHKA-192521457/DSA-0119---192521457--Assignment-2

> Important evidence rule: write your prediction before running each program in your own submission copy. The observed outputs in this package were captured by executing these source files. Replace timing values with measurements from your own computer if required by your instructor.

## Q1 – Call by Value, Reference and Pointer (6 marks)

### Predicted output for the given `change/bigger/show` program
```text
1 12 13
100 100
16 13 6
```
Reason: `a` is passed by value and remains 1 after `change`; `b` is passed by reference and becomes 12; `c` is passed by pointer and becomes 13. `bigger(a,c)` returns a reference to the larger value, `c`, so assigning 100 changes `c`. `show(1)` uses y=5,z=10; `show(1,2)` uses z=10; `show(1,2,3)` uses all explicit values.

### Complete-the-code result
The reference implementation subtracts `fee * percent / 100` from the referenced caller variable. Expected values: value call leaves 45000; reference call changes it to 40500.

### Inquiry and design decision
A value parameter is a separate local copy. A reference parameter aliases the caller's object. A pointer parameter stores an address and dereferences it to update the caller; check for null before dereferencing. Use `const T&` for large read-only objects to avoid copying while preventing modification through that parameter. For multiple concessions, returning a new fee makes the calculation explicit and easy to test; in-place reference mutation can be convenient when the function's purpose is specifically to update an existing record. All three operations take O(1) time for a single fee. A `long long` copy is constant-sized; copying a large Student object copies all its fields, while reference/const-reference pass an address-sized alias.

## Q2 – Return by Reference and Its Dangers (4 marks)

`highestMark()` returns a reference to an actual array element, so `highestMark(marks,n) += 2` updates the array. `highestMarkReadOnly()` returns a const reference, which can be read but not assigned through. `highestMarkCopy()` returns an independent integer copy. `unsafe_reference_demo.cpp` deliberately contains a function returning a reference to a local variable; compile it only to inspect the warning and do not run it. The local object is destroyed when the function exits, so the reference dangles and using it is undefined behaviour.

If the storage changes to a growing `std::vector`, an insertion that reallocates storage invalidates references, pointers and iterators to its elements. An index can be used to look up the element again after growth, provided the logical element ordering has not changed. Finding the maximum is O(n) time and O(1) extra space for reference, pointer or index approaches. Index is generally easier to revalidate after vector growth; a pointer/reference can become invalid after reallocation.

## Q3 – Default Arguments and Function Overloading (6 marks)

The original three declarations conflict because calls with one argument can match more than one candidate after defaults are applied. Keep one `double` overload with default flags and distinct overloads for `int` grams and `Parcel`. In this implementation:
- `charge(2)` selects the `int` overload (exact match).
- `charge(2.0)` selects the `double` overload (exact match).
- `charge(2.0f)` selects the `double` overload by floating-point promotion.
- `charge(500, true)` selects the `int` overload.
- `charge(1.5, false, true)` selects the `double` overload.
- `charge(p)` selects the `Parcel` overload.

Overload resolution prefers exact matches over promotions, and promotions over standard conversions. Default arguments must be supplied from the right because trailing parameters are the ones that can be omitted. Overload selection happens at compile time and adds no run-time dispatch cost. A single Parcel structure can make future optional fields easier to add, while overloads make common input types explicit.

## Q4 – Class with an Array Inside It (6 marks)

The `SavingsAccount` class stores account number, balance, ten transactions, count and next circular index privately. `deposit()`, `withdraw()` and `miniStatement()` are public. Some functions are defined inside the class and others outside using `SavingsAccount::`.

Private storage protects the account's invariants: callers cannot directly corrupt the balance, count or transaction positions. When full, shifting a fixed array discards the oldest entry but moves up to nine entries (O(k), here k=10). A circular buffer overwrites the oldest slot and advances an index in O(1) insertion time. Increasing capacity from 10 to 50 changes the array capacity and related logic; a circular buffer keeps the same insertion approach. A `deque` can also push at the back and pop at the front, normally O(1) at the ends, but uses dynamic storage. Fixed array space is O(k) embedded in each account; deque storage is O(k) dynamic storage.

## Q5 – Static Members and Arrays of Objects (7 marks)

The expected Token prediction is:
```text
101 103 104 4
```
The static `next` begins at 100. Three array objects and one extra object call the constructor, incrementing it four times. The IDs are 101, 102, 103 and 104; `issued()` returns 104-100 = 4.

The BusTicket design makes `issued` static because it represents seats issued across all tickets, not one ticket. Its out-of-class definition allocates/initializes the static data member. `count()` is static and therefore has no `this` pointer; it cannot directly access an individual object's non-static `seat` or `name`. Four tickets are created for capacity three, so the fourth is waiting. Creating objects in a function still increments the same class-level counter; calling that function twice continues from the previous count unless the design explicitly resets or separates bus state. A TicketOffice object would allow two buses to maintain independent counts; a single static counter is simpler for one shared capacity.

## Q6 – Friend Functions and Inline Functions (8 marks)

Expected output for the supplied Complete-the-Code program:
```text
205 false
```
9:45 is 585 minutes after midnight and 13:10 is 790 minutes; the difference is 205. `arrival` is not earlier than `departure`, so the result is false. The additional tests cover a pair on opposite sides of noon and equal times.

A friend function is not a member, is called like a normal function, and can access private members because the class explicitly grants friendship. It suits a symmetric operation involving two objects. A member function would be called through one object (for example `a.minutesTo(b)`); getters would preserve private storage but expose read accessors. Making fields public weakens encapsulation. `inline` permits a definition in a header and suggests that the compiler may substitute the function body, but the compiler decides whether to inline. Both comparison methods are O(1). The benchmark source measures 10,000,000 calls at `-O0` and `-O2`; see `Task06/benchmark_results.txt`. Timing is machine-, compiler- and optimisation-dependent, so repeat on the submission computer and report those values.

## Q7 – Diagnose, Redesign and Validate (13 marks)

### A. Diagnose the limitation
The original shift-array strategy in `ShiftHistory::add()` moves nine elements whenever the fixed array is full. The work per insertion is O(k), where k is the retained history size. As the required history grows from 10 to 50, the number of moved elements per full insertion also grows.

### B. Measurable objective
For a full history, retain the newest ten values while reducing each insertion to a constant number of assignments independent of the capacity.

### C. Revised design
Use a circular buffer containing an array, a count and a `next` index. Each insertion writes to `data[next]`, advances `next` modulo capacity, and increments count until full. No elements are shifted. Extra state is one index and a count; storage remains O(k). Pseudocode:
```text
add(value):
    data[next] = value
    next = (next + 1) mod capacity
    if count < capacity:
        count = count + 1
```
Trade-off: reading values in chronological order requires computing the oldest position from the index.

### D. Prediction before implementation
Both versions should retain the same latest ten values. The circular buffer should perform fewer assignments per insertion once full, and its insertion complexity should be O(1) instead of O(k).

### E. Implement and validate
`Task07/main.cpp` runs both designs with the same two million insertions. The output reports the newest value and measured elapsed microseconds. The same test is used for both. Use the captured output as a sample, then repeat on your own machine for your final evidence.

### F. Final evaluation
The circular buffer meets the constant-time insertion objective and avoids shifting. The shift version can be easier to understand and is acceptable for very small histories or infrequent updates. The circular design is preferable when updates are frequent, but chronological traversal is slightly more complex. Both use O(k) storage.

## Final evidence checklist
- See `ASSIGNMENT_REQUIREMENTS_CHECKLIST.md`.
- Include your own before-run predictions in your report.
- Keep at least one progressive Git commit for each task.
- Ensure the repository is named exactly `DSA01-192521457-Assignment2` if following the prescribed naming pattern.
- Put the working GitHub URL on the report cover page and share access with faculty.
