
### quick sort
```ocaml
let rec qsort l =
    match l with
    [] -> []
    x::xs -> (
        let ys, zs = partition x xs in
        (qsort ys) @ (x :: (qsort zs))
    )
```
Analysis of quick sort

stable sorting: