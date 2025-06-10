# Intro to Rust 

Resources: 
- official rust book: https://doc.rust-lang.org/book/ 
- rust exercises: https://github.com/rust-lang/rustlings

## Basics
### basic types
Scalar Types 
 integer:
 - signed: i8, i16, i32, i64, i128, isize
 - unsigned: u8, u16, u32, u64, u128, usize
 floating-point: f32, f64
 boolean: bool
 character: char (4 bytes, Unicode Scalar Value)
```rust
    let int8: i8 = 127;
    let int16: i16 = 32767;
    let quotient = 56.7 / 32.2;
    let truncated = -5 / 3; // -1
    let remainder = -5 % 3; // -2
    let c = 'z'; // char uses single quotes while string uses double quotes
    let z = 'ℤ';
    let heart_eyed_cat = '😻';
    // tuple usage
    let tup: (i32, f64, u8) = (500, 6.4, 1); // tuple elements can have different types
    let (x, y, z) = tup; 
    let five_hundred = tup.0;
    let six_point_four = tup.1;
    let one = tup.2;
    // array usage 
    let A = [1, 2, 3, 4, 5]; // array elements must have the same type
    let first = A[0];
    let B: [i32; 5] = [1, 2, 3, 4, 5]; // array with type and length
    let C = [3; 5]; // initialize array with 5 elements of 3
```
Structs and Enums
```rust
struct structName {
    field1: type1,
    ...
}
impl structName {
    fn new(value1: type1, ...) -> Self {
        Self {...}
    }
    fn method1(&self, ...) { ... }
}

fn main() {
    let instance = structName{field1: value, ... };
    let _ = instance.field1;
}
```
```rust 
enum enumName {
    Option1,
    Option2{ field1: type1, ...},
    Option3(type1, ...),
    ...
}
fn main() {
    ...
    match enumValue {
        enumName::Option1 => { <stmts> },
        enumName::Option2{field1, ...} => { ... },
        enumName::Option3(value1, ...) => { ... }
    }
}
```

### declaration 
Rust requires developer explicitly declare mutable variables with keyword ```mut```
```rust
let mut x = 5; 
    println!("Declare mutable x is: {}", x);
    x = x + 1;
    println!("Increase x by one, now x is: {}", x);
    {
        let x = 7;
        println!("Shadowing x inside block: {}", x);
    }
    println!("Shadowing x outside block: {}", x);
```
```mut``` only allows to change value, but not type of a variable. Shadowing allows change of type:
```rust
    let number = "T-H-R-E-E"; 
    println!("Spell a number: {}", number);
    let number = 3;
    println!("Number plus two is: {}", number + 2);
```
```const``` is immutable and must be explicitly typed, 
```rust
const NUMBER: i32 = 3;
```

### function
Basic syntax: 
```rust
fn add1(x: i32) -> i32 {
    x + 1 // expression 
}
fn add2(x: i32) -> i32 {
    return x + 2; // statement 
}

```
```rust 
let x = 5;
print_addition_result(add1(x), add2(x));
let y = {
    let x = 3;
    x + 1 // expression, so no semicolon added
}; // the whole scope is an expression
println!("The results of y is: {}", y);

```

### basic control flow 
Basic syntax (these are not inference rules), just example of uses:
```rust
    if <cond>: bool { <then_branch>: tau } else { <else_branch>: tau} :tau
```
```rust
    'label: loop { <stmts>; break <expr>: tau; } : tau 
    'label: loop { <stmts>; break; } : unit
```
```rust
    while <cond>: bool { <stmts> }
```
```rust
    for element in iteratables { <stmts> }
```

```rust
fn print_nums(mode: i32) {
    if mode == 1 {
        for number in 0..5 {
            println!("{}!", number);
        }
    } else if mode == 2 {
        let A = [0,1,2,3,4];
        for element in A {
            println!("{}!", element);
        }

    } else if mode == 3 {
        let mut counter = 0;
        while counter != 5 {
            println!("{}!", counter);
            counter += 1;
        }
        // notice while is less general than loop,
        // while has fixed return type to be unit,
        // but loop can return any type by "break return_value;"
    } else {
        let mut counter = 0;
        'outer: loop { // annotated loop
            println!("{}!", counter);
            counter += 1;
            if counter == 5 {
                break; // break without return value
                // break 'outer; // explicit break the labeled loop
            }
        }
        let result = loop {
            counter += 1;
            if counter == 10 {
                break (counter * 2) // break with 
                return value
            }
        };
    }
}
``` 

### basics of ```move``` semantics
Essentially, in any scope, only one ownership for one object.
Notice for stack object, they are implicitly copied, while for heap object ...
```rust
let s1 = String::from("hello");
let s2 = s1;
```
Both of below won't work, as ```s2``` is not borrowed as ```mut```
```rust
let s1 = String::from("hello");
let s2 = s1;
s2.push_str("world");

let mut s1 = String::from("hello");
let s2 = s1;
s2.push_str("world");
```
Now ```s2``` is fixed to be mutable. It's allowed to *downcasting* from unmutable to mutable (i.e. ```let mut <unmut_ident> = <unmut_ident>``` holds trivially), **but not vice versa**. Therefore, it's okay to omit first ```mut``` in declaration of ```s1```. 
Remark: when you write ```fn ident(mut x) { ... }```, it's a syntactic sugar for ```let mut x = args``` in function body, thus also follow the downcasting rule
```rust
let mut s1 = String::from("hello");
let mut s2 = s1;
s2.push_str("world");
```
...it won't be possible to ```println!("{s1} and {s2}");``` as ```s1``` already been ```move``` to ```s2```. To get around this without ```clone```ing ```s1```, let's motivate the concept of reference:

```rust
let v = vec!(1); // immutable
let x1 = &v;
let x2 = &v; 
println!("{:?} and {:?}",x1, x2);
```

```rust
let v = vec!(1); // immutable
let x1 = &v;
let x2 = x1; 
println!("{:?} and {:?}",x1, x2);
```
Now we want to mutate ```v```, by adding ```mut```:
```rust
let mut v = vec!(1);
let x1 = &v;
let x2 = &v; 
println!("{:?} and {:?}",x1, x2);
// -- ok

let mut v = vec!(1);
let x1 = &v;
let x2 = x1; // ok since &Vec<i32> implements copy trait
println!("{:?} and {:?}",x1, x2);

let mut v = vec!(1);
let x1 = &mut v;
let x2 = x1; // not ok since &mut Vec<i32> implements copy trait
println!("{:?} and {:?}",x1, x2);

let mut v = vec!(1);
let x1 = &mut v;
let x2 = &v; 
println!("{:?} and {:?}",x1, x2);
// -- not ok, unique &mut in arbitrary scope

let mut v = vec!(1);
let x1 = &mut v;
x1.push(2);
println!("{:?}",x1); // -- ok, printing [1, 2], and x1 is consumed 
let x2 = &mut v;
x2.push(3);
println!("{:?}",x2); // -- ok, printing [1, 2, 3], and x2 is consumed 

```
It's worth mentioning that, ```move``` is implemented at program level as a checker maintaining each object is uniquely owned in a scope, whereas *reference* is implemented at type level that 
```rust
let mut s1: String = String::from("hello");
let s2: String = String::from("hello");
let mut v = vec!([1]);
let x1: &mut Vec<i32> = &mut v;
let x2: &Vec<i32> = &v;
```

some exercise:
```rust
// Shouldn't take ownership
fn get_char(data: &String) -> char {
    data.chars().last().unwrap()
}

fn print_first(data: &String) {
    println!("{:?}", data.chars().nth(0).unwrap());
}

fn string_uppercase1(data: String) {
    let data = data.to_uppercase();
    println!("{data}");
}

fn string_uppercase2(data: &mut String) {
    *data = data.to_uppercase();
    println!("{data}");
}

fn main() {
    let data = "Rust is great!".to_string();
    get_char(&data);
    print_first(&data);
    string_uppercase1(data);
    // string_uppercase2(&mut data);
}
```