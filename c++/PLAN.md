# c++ from a programming language perspective λ



## basic types
### built-in types
```cpp
float x = 4.2f
double x = 4.2

sizeof(type) returns bytes of type
```
### algebraic types
example of use:
```cpp
// type aliasing
typedef int myInt;

// product type
struct Person {
    string name;
    int age;
};

// sum type
enum Color { Red, Green, Blue }; // by default, Red = 0, Green = 1, ...
Color c1 = Red;


// general product type / sum type
struct List {
    int val;
    List* next; 
}

struct Tree {
    int val;
    Tree* left;
    Tree* right;
}


```

## automatic type inference
```auto```  let compiler determine the type DEPEND ON THE CONTEXT.
What happen if compiler does not gain enough information? (Turns into Python??)


## syntax for commonly used statements
quick reference: https://github.com/mortennobel/cpp-cheatsheet
```cpp
x=y;                        // Every expression is a statement
int x;                      // Declarations are statements
;                           // Empty statement
{                           // A block is a single statement
    int x;                  // Scope of x is from declaration to end of block
}
if (x) a;                   // If x is true (not 0), evaluate a
else if (y) b;              // If not x and y (optional, may be repeated)
else c;                     // If not x and not y (optional)

while (x) a;                // Repeat 0 or more times while x is true

for (x; y; z) a;            // Equivalent to: x; while(y) {a; z;}

for (x : y) a;              // Range-based for loop e.g.
                            // for (auto& x in someList) x.y();

do a; while (x);            // Equivalent to: a; while(x) a;

switch (x) {                // x must be int
    case X1: a;             // If x == X1 (must be a const), jump here
    case X2: b;             // Else if x == X2, jump here
    default: c;             // Else jump here (optional)
}
break;                      // Jump out of while, do, or for loop, or switch
continue;                   // Jump to bottom of while, do, or for loop
return x;                   // Return x from function to caller
try { a; }
catch (T t) { b; }          // If a throws a T, then jump here
catch (...) { c; }          // If a throws something else, jump here
```


## OOP in c++, and more theory
visibility (theory behind, information flow in type system):

```cpp
private
public
protected // visiable for subclass, but not outside the class system
friend
```
example of basic usage:
```cpp
class MyClass{
// class set all fields and methods to be private by default, different from struct
// set field be public by default
private:
    int secret_;

public:
    int x, y;
    bool b;

    MyClass() {} // constructor 
    void MyMethod1() {}
    int MyInsecureMethod2() {
        return secret_; // ?
    }
    virtual void DynamicDispatch() {
        std::cout<< "MyClass" << endl;
    }
    ~MyClass() {} // desctructor 
};
```
example illustrating inheritance:
```cpp
class MySubClass : public MyClass {
private:
public:
    /* inherited: 
        int x, y;
        bool b;
    */
    float z;
    void DynamicDispatch() override {
        std::cout<< "MySubClass" << endl;
    }
    
}
int main() {
    MyClass* c = new MySubClass();
    c->DynamicDispatch(); // calls MySubClass::DynamicDispatch();
    delete c;
}
```
Comment:
- Idea of dynamic dispatch: at runtime determine the right version of method to call upon different classes. (theory behind this, class based or method based dynamic dispatch see PFPL chapter 26)
- Dynamic dispatch vs Static dispatch: by default (or use ```final```), C++ does static
dispatch, which determine which method to call statically based on type of the object. 
```virtual``` (with ```override``` as good oop style) enables dynamic dispatch, (see above, and more explanation added ???)

example of interface (signature)
```cpp
class Printable {
public:
    virtual std::string GetName() = 0;
}

class MySubClass : public MyClass, Printable {
public:
    std::string GetName() override {
        return "MySubClass";
    }
}

```

## Templates (Generics / Polymorphism / Parametric Types ??)
quick intro example, when you don't want to write same function for different types
```cpp
template<typename T>
void Print(T value) {
    std::cout << value << std::endl;
}
int main() {
    Print<int>(5);
    Print<std::string>("Example from Cherno's c++ tutorial video");
}
```
```template``` won't exist until we call it, i.e. they will be factored out as dead code by complier if nobody used the template. It behaves more
simply as linking.

TODO: More to fill here!!!

## lambda expression
###  intro
```cpp
[capture](parameters) -> return_type {
    // function body
}
```
[]: Does not capture anything in the local scope.
[&]: capture everything in the local scope by reference.
[=]: capture everything in the local scope by copy.
The lambda's local scope is the scope where it is defined, not the scope where it is used.

Common example of use -- define comparator for a sort 
```cpp
typedef edge pair<pair<int, int>, int>;
vector<pair<pair<int, int>, int> > weighted_graph(M);
sort(weighted_graph.begin(), weighted_graph.end(), 
    [](const edge& e1, const edge& e2) {
        return e1.second < e2.second;
    })
```

### mutating environment
```cpp
int main()
{
   int m = 0;
   int n = 0;
   [&, n] (int a) mutable { m = ++n + a; }(4);
   cout << m << endl << n << endl;
}
```
mutable keyword allows n, captured by reference, to be mutated in lambda expression body

### recursive lambda 
First, this doesn't work, since lambda function cannot directly refer itself in definition
```cpp
auto gcd = [](int a, int b) -> int { 
    return b == 0 ? a : gcd(b, a % b); 
};
```
a small but intelligent perturb to prevent self-reference, is wrap it into Y-combinator:
```cpp
y_combinator([](auto gcd, int a, int b) -> int {
		return b == 0 ? a : gcd(b, a % b);
	})(20, 30)
```
**the most convenient way** is to use 
std::function to have a lambda capture a reference to 
a not-yet constructed std::function:
```cpp
function<int(int, int)> gcd = [&](int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	};
```
a final solution is pass itself into itself
```cpp
auto gcd = [&](int a, int b, auto &&gcd) -> int {
		return b == 0 ? a : gcd(b, a % b, gcd);
	};
```

Here's an example writing DFS as recursive lambda: 
```cpp
void dfs(int root, vector<vector <int>>& edges) {
    vector<bool> visited(n, false);
    function<void(int)> l_dfs = [&](int u) {
        if (visited[u]) return;
        else {
            for (auto v : edges[u]) {
                if (!visited[v]) l_dfs(v);
            }
        }
        return;
    }
}
    
```
another example from leetcode 105.
```cpp
// we want to access idx of each value fast, and hashmap is doable here
        // sinc each value is unique
        int N = inorder.size();
        unordered_map<int, int> idxmap;
        for (int i = 0; i < N; i++) {
            idxmap[inorder[i]] = i;
        }
// a recursive function takes in node u, and slice of inorder through l, r
        function<TreeNode*(int, int, int)> build_helper = 
        [&](int u, int l, int r) -> TreeNode* {
            if (l == r) return nullptr;
            int ui = idxmap[preorder[u]];
            TreeNode* res1 = build_helper(u+1, l, ui);
            TreeNode* res2 = build_helper(u+1+ui-l, ui+1, r);
            return new TreeNode(preorder[u], res1, res2);
        };
```


# Advanced feature

## preprocess
### macros 
Caveat! macros may affect things (in larger systems) you don't realize

```cpp
#include <in one of include direactories>
#include "relative path to current file"
#pragma once // #include a header file only once

#define [#undef]

#if [#elif]* [#else] #endif

// example of use, equivalent to #pragma once, which now conditioning 
// on snip of code already been defined or not upon mulitpule #include
#ifndef _INSANE_CODE
#define _INSANE_CODE
( whatever code goes here)
#endif
```

### ```#include```
- ```#include``` literally copies the contents of a file into translation unit
    - this becomes problematic when in ```file1.cpp``` we ```#include "lib.hpp"``` and we ```#include "file1.cpp"``` and ```#include "lib.hpp"``` again in ```file2.cpp```
    - expedient solution: 
        - ```static``` restrict free-functions to its tranlation unit
        - ```inline```
        - ```#pragma once```
        - (better) remodulize 
    - standard solution (in C++20), similar to Rust, Python, OCaml...
        -  ```import module```

## linking


### static, the confusing keyword
Also see https://stackoverflow.com/questions/15235526/the-static-keyword-and-its-various-uses-in-c 
```static```  variables/functions exists for the lifetime translation unit that it is defined in, i.e. cannot be accessed from other namespaces (? in headers for const expr)
```cpp
file1.cpp       file2.cpp(#include "file1.cpp")
int x = 42;            int x = 43;          (linking err)
static int x = 42;     int x = 43;          (compile)
int x = 42;            extern int x = 43;   (compile)
static int x = 42;     extern int x = 43;   (linking err)

```

```static``` inside a Class/Struct 
- ```static``` vars: all instances of the Class share and mutate var
- ```static``` methods cannot access non-static fields (notice static methods are
syntax sugar for write the function outside the class, with static fields hanging 
above)