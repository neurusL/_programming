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

## Pointers interact with Scope
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