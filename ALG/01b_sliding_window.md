# Chapter 01: Search Space
- two pointer 
- sliding window
- binary search

## When search space can be pruned...

## 2. by a "sliding window"
### scenario 1: when looking for consecutive sub-array with some property
1. search for string matching (Rabin Karp algorithm, where each check for window is built incrementally), or match up to permutation
2. search for shortest sub-string containing a multiset of chars
3. search for longest sub-string without duplicated chars
The problems can be solved by sliding window trick share the same property that:
- the solution space can be iterated thoroughly by maintain a window and slide over a larger search space
- lower boundary of the sliding window acts depending on the upper boundary of the window, which prevents the search on all potential combinations of lower and upper boundary, the key **challenge** is to come up with **invariant property of sliding window**
- after reaching the first sliding window with desired invariant, we will need to do next is shrink lower bound to break the invariant just right, followed by upper bound resume the invariant

Going back to the examples:
1. for string matching, window should only be size of string we match against,
2. window should cover all the chars in multiset, after that, 
3. window should never have duplicated chars in it, if there is, we pop lower side of the window until resume the invariant.

```python
    left, right = 0, 0 # window boundary [left, right)
    window = {} # can be int, set, map, counters, array if keys are fixed, or 
    # other combined data structure
    # for instance in 3, you may maintain a hashmap together with a counter
    # of the number of char whose appearance is covered in the sliding window

    while right < len(iterable):
        window.add(iterable[right])
        right += 1

        while is_invariant(window): # sometimes worth additional check of left < right
            # customized operation, e.g. update answer
            # ...
            # it can be trick to wisely update information here (*)

            # then shrink the window to break the invariant
            window.remove(iterable[left])
            left += 1
        # now invariant is temporarily broken
        # in next (serveral) iterations invariant will be resumed
```
exercise: L76, L3297
here's an example how to break the final answer into partitions with bijection to each valid sliding window:
```python
    def validSubstringCount(self, word1: str, word2: str) -> int:
        # first step if find all matching of word2 in word1 up to permutation
        # the step is same as L76
        # second step is accumulate the counts based on each sliding window
        # * a general techique of counting result in another way

         
        target_char_cnt = 0
        target = [0] * 26 # hardcode the window info here, since a fixed alphabet
        for s in word2:
            w = ord(s) - ord('a')
            target[w] += 1

        for i in range(26):
            if target[i] > 0:
                target_char_cnt += 1

        char_cnt = 0   # +1 if c in word2 and window[c] >= target[c]
        window = [0] * 26

        left, right = 0, 0

        res = 0 # total number count of desired substring

        while right < len(word1):
            w = ord(word1[right]) - ord('a')
            if target[w] > 0:
                window[w] += 1
                if window[w] == target[w]:
                    char_cnt += 1

            right += 1

            while char_cnt == target_char_cnt:
                print(left, right)
                res += len(word1) - right + 1   # this step is crucial (*)
                w2 = ord(word1[left]) - ord('a')
                if target[w2] > 0:
                    window[w2] -= 1
                    if window[w2] < target[w2]:
                        char_cnt -= 1
                left += 1

        return res
```
let's conclude with an extended discussion: when do not use sliding window? Namely, when you cannot narrow down the search space to a collection of windows that share an invariant, such that the growth of upper boundary doesn't "drag" the lower boundary to move forward. In this scenario, try to think about other optimization techniques, like reusing calculated results (e.g. dynamic programming).
