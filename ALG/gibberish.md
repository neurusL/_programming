The following array access, at first glance, should complain 
index out of bound. However, python interprets it as last row
in ```dp``` and j th element in that row. Keep this in mind when debugging.
```python
    dp[-1][j]
```
#

I spend a while debugging the following python code for coin change, the idea is
simply---we calculate min count of coin to make up the amount via memoization. Let's
see where goes wrong:
```python
    def coinChange(self, coins: List[int], amount: int) -> int:
        memo = {} # memo[amount] = result for min count of coins to obtain amount

        def helper(amount: int) -> int:
            if amount < 0:
                return -1
            if amount == 0:
                return 0
            
            if amount in memo:
                return memo[amount]

            # backtracking
            min_cnt = None
            for coin in coins:
                res = helper(amount-coin)
                if res != -1:
                    if min_cnt is None:
                        min_cnt = res
                    else:
                        min_cnt = min(min_cnt, res)

            memo[amount] = -1 if not min_cnt else (min_cnt+1)
            return memo[amount]
            
        return helper(amount)
```
Blame: shouldn't really use the same name ```amount``` inside helper function. Suggest
move the helper function outside main function.
My original envision was, instead of setting ```min_cnt``` to be ```float(`inf`)```, 
let use modern language feature ```None```.  
The bug was at ```memo[amount] = -1 if not min_cnt else (min_cnt+1)```, where 
```not min_cnt``` is evaluated to ```True``` when ```min_cnt == None``` **OR**
```min_cnt == 0```, which frequently happens when ```amount == coin```.  
Instead of ```memo[amount] = -1 if not min_cnt else (min_cnt+1)```, rather it should 
be ```memo[amount] = -1 if min_cnt is None else (min_cnt+1)```.

A fix, ideally in another language like Rust, is:
```rust
use std::collections::HashMap;

impl Solution {
    pub fn coin_change_helper(coins: &Vec<i32>, memo: &mut HashMap<i32, i32>, amount: i32) -> i32 {
        if let Some(res) = memo.get(&amount) {
            return *res;
        } else {
            if amount < 0 {
                return -1;
            } else if amount == 0 {
                return 0;
            } else {
                let mut min_cnt = None;
                for coin in coins.iter() {
                    let sub_res = Self::coin_change_helper(coins, memo, amount-coin);
                    if sub_res != -1 {
                        min_cnt = match min_cnt {
                            None => Some(sub_res),
                            Some(v) => Some(std::cmp::min(sub_res, v)),
                        }
                    }
                }
                match min_cnt {
                    None => { memo.insert(amount, -1); },
                    Some(v) => { memo.insert(amount, v+1); }
                }
                return memo[&amount];
            }
        }
        
    }
    pub fn coin_change(coins: Vec<i32>, amount: i32) -> i32 {
        let mut memo = HashMap::<i32, i32>::new();
        return Self::coin_change_helper(&coins, &mut memo, amount);
    }
}
```