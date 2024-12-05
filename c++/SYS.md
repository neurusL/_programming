# System level language features in C++ 

## Memory Model used by C++
### Stack
C++ allocates memory for objects on stack based on the stack pointer ```%rsp```,
and it's fast since C++ simply decrease ```%rsp``` fitting the new object.
When objects go out of scope, ```%rsp``` restore based on bookkeeping ```%rbp```,
and all those objects vanish.
```cpp
int s_value = 5;
```

### Heap
C++ **dynamically** allocates memory for objects on heap, through ```new```, 
similar to ```malloc/free```, a expensive overhead at runtime
(recall the malloc lab CSAPP, where you implemented free list and several other 
mechanisms gluing fragmented heap spaces)
```cpp
int* h_value = new int;
*h_value = 5;
delete h_value;
```

## Pointer vs Reference 
reference(`int&`) can only REFER to ALREADY EXISTING object, but pointer(`int*`) 
can be created without depending on any existing object.
### basics of pointers
```cpp
int var = 42;
void* ptr = &var; // subtyping, int* <: void*
ptr = (int*)ptr;
*ptr = 10;
```
Heap memory allocation and deallocation:
- comment: Rust follows the same design, expect for additional information on
// ownership which keep track of (constructor, destructor) pair
- comment: avoid mixing with ```malloc/free```
```cpp
// for a single object
int* ptr = new int;
*ptr = 42;
delete ptr; 

// for an array of object
char* buffer = new char[8];
memset(buffer, 0, 8);
delete[] buffer;

// for objects of custom types (class)
class MyClass{
    private: // put constructor here if not want client create any instance of the class
    public:
    MyClass() {} // default constructor, namely doing nothing
    MyClass() {} // constructor
    MyClass(args) {} // constructor
    ~MyClass() {} // desctructor
};
int main() {
    MyClass *obj = new MyClass(); // calls constructor
    delete obj; // calls destructor
    ...
}
```
### basics of reference
```cpp
void dirty_incr1(int* a) { (*a)++; }
void dirty_incr2(int& a) { a++; } // syntactic sugar for pointer
int main() {
    int a1 = 5; std::cout<<dirty_incr1(&a1) << std::endl; // 6
    int a2 = 5; std::cout<<dirty_incr2(a2) << std::endl; // 6

    int& ref; // not compile
    int& ref = 1; // reference must be immediately initialize
    ref = 5;  // not compile, reference cannot be reassigned
}
```

## Function Pointers


## Smart Pointers, Pointers interact with Scope
### Unique Pointer
When stack allocated object goes out of scope, C++ automatically deallocate it 
(recursive if the object contains pointers pointing to heap); but when heap 
allocated object goes out of scope, developers are responsible for explicitly 
```delete``` it.
```cpp
class Entity {
public:
    Entity() { std::cout << "create entity" << endl; }
    ~Entity() { std::cout << "create entity" << endl; } // <-2-
}
class ScopePtr {
private:
    Entity* m_Ptr;
public:
    ScopePtr(Entity* ptr) : m_Ptr(ptr) {}
    ~ScopePtr() { delete m_Ptr; } 
    // <-1- stack allocated, thus calls ~ScopePtr() when out of scope
    //      which call delete on m_Ptr (<-2-)
}
int main() {
    {
        Entity* e1 = new Entity(); // object not automatically deleted
        ScopePtr e2 = new Entity(); // implicit conversion, and object automatically deleted
    }
}
```
Above is partial implementation for ```unique_ptr``` (copy trait for unique pointer is not shown, but they 
are implemented as ```delete```). 
Notice unique pointer has **unique ownership**, meaning no two owners can at the 
same time own the pointer, otherwise, when one owner goes out of scope and the object
consequently got deallocated, the other owner immediately lose the object's access.
```cpp
#include <memory>
int main() {
    {
        std::unique_ptr<Entity> e1(new Entity()); 
        // or use the convention:
        std::unique_ptr<Entity> e2 = std::make_unique<Entity>();
        std::unique_ptr<Entity> e2 = e3 // compiler error, 
        e2->some_methods(some_args);
    }
}
```

### Shared Pointer (implemented through reference counting), and Weak Pointer
Shared Pointer: deallocate the object when all the references to the object are gone (i.e. reference
count = 0).
```cpp
#include <memory>
int main() {
    {
        std::shared_ptr<Entity> e0;
        {
            std::shared_ptr<Entity> shared_e = std::make_shared<Entity>();
            std::unique_ptr<Entity> e0 = shared_e; // cnt = 1
            std::unique_ptr<Entity> e1 = shared_e; // cnt = 2
        } // cnt = 1
    } // cnt = 0, thus destroy object
}
```

Weak Pointer: not influence the reference counting, rather it ask a shared pointer
whether it is still valid

## move
### left values and right values 
```
type lvalue = rvalue
```


