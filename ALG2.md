# c++ algorithm cheatsheet -- dynamic programming, more graph, geometry

## Binary Search in General
Danny Sleator's ***best*** binary search template:

Problems that can be solved with binary search need to have the following property:

- Usually the space of binary search is canonical (i.e. integers)
- We can find a property (function) $f$ and some integer $N$ such that $\forall n >= N$ this property is true and $\forall n < N$ this property is false.

Therefore, in implementation we maintain two invariants:

- $l$​ is the right most point we know such that this property is true. (if such $l$​ doesn't exist define it to be left boundary - 1)
- $r$ is the left most point we know such that this property is false. (if such $r$ doesn't exist define it to be right boundary + 1)

Then just copy this template and customize this property function:

```cpp
int l = lb - 1, r = rb + 1;
while (l + 1 < r) {
  int mid = l + (r - l) / 2;
  function<bool(int)> ok = [&](int mid) -> bool {
    // Implement me
  }
  if (ok(mid)) l = mid;
  else r = mid;
}
```

Example: given a sorted vector $v$ in non-decreasing order, find the greatest index $x$ such that $v[x] < K$ or state it does not exist.

```cpp
// Suppose have v as vector
int l = -1, r = (int)v.size();
while (l + 1 < r) {
  int mid = l + (r - l) / 2;
  auto ok = [&](int mid) {
    return v[mid] < K;
  };
  if (ok(mid)) l = mid;
  else r = mid;
}
if (l == -1) std::cout << "Do not exist" << std::endl;
else std::cout << l << std::endl;
```

Special case: what if the binary search space is float? Do not use while loop in this case. Use for loop instead.

Example: find $x$ such that $x$ is no more then $10^{-6}$ away from $\sqrt3$.

```cpp
double l = 0, r = 2;
int iteration = 40; // The bigger this number the more accurate answer is
for (int i = 0; i < iteration; i++) {
double mid = (l + r) / 2;
auto ok = [&](double mid) {
    return mid * mid < (double)3;
};
if (ok(mid)) l = mid;
else r = mid;
}
std::cout << setprecision(10) << fixed << r << ' ' << sqrt(3) << std::endl;
```
