# c++ data structure cheatsheet

## tuple(pair)
```cpp
```

## vector
```cpp
vector<int> a;
vector<int> a = {2, 3, 4};
vector<int> a(10);
vector<int> a(10, 0);

vector<vector<int>> twoDimVector(3);
vector<vector<int>> twoDimVector(3,  vector<int>(2, 0));

int len = a.size();
a.push_back(1); // or a.insert(a.begin(), 1);
a.pop_back();

a[4] = 2;
int a4 = a[4];
```

## map, unordered_map
```cpp
std::map<int, std::string> mymap;

// Adding elements to the map
mymap[10] = "Ten";
mymap[20] = "Twenty";
mymap[30] = "Thirty";
mymap[40] = "Forty";

for (const auto& pair : mymap) {
    std::cout << pair.first << " : " << pair.second << '\n';
}

auto it = mymap.find(25);
if (it != mymap.end()) {
    std::cout << "Found: " << it->first << " => " << it->second << '\n';
}

if (mymap.count(30)) {
    std::cout << "Key 3 exists\n";
}

mymap.erase(10); 

// Using lower_bound on map
auto itlow = mymap.lower_bound(25);  // First element NOT LESS than 25
if (itlow != mymap.end()) {
    std::cout << "Lower bound for key 25: " << itlow->first << " => " << itlow->second << '\n';
}

// Ordered map's min element sorted by key
auto minelt = *(mymap.begin());
```

## set, unordered_set, multiset
### set (tree based)
```cpp
set<int> s;     
s.insert(20);
s.insert(30);
s.insert(20);   // no new element inserted
s.insert(40);
s.insert(50);

if (ret.second==false) it=ret.first;  // "it" now points to element 20

myset.insert (it,25);                 // max efficiency inserting
myset.insert (it,24);                 // max efficiency inserting
myset.insert (it,26);                 // no max efficiency inserting

it = myset.find (26);
myset.erase (it, myset.end());        // erase [it, end)
myset.erase (27)                      // erase nothing since not found

int size = s.size();

for(auto it = s.begin(); it != s.end(); it++) {
    cout << *it << endl;
}

s.clear();
bool exists = s.find(20) != s.end();
int count = s.count(20);               // return either 0 or 1


// lower bound and upper bound can be used, since set is ordered
for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

itlow=myset.lower_bound (30);                //       ^
itup=myset.upper_bound (60);                 //       |            ^
                                             //       [           )|
                                             // 10 20              70 80 90
if (itlow != myset.end()) {
    int value = *itlow;
    cout << "at position " << (itlow- v.begin()) << "with value" << value << endl; 
}                             
myset.erase(itlow,itup);  

```
### unordered_set (hash table based)
```cpp
```

## linked list
Sometimes dummy head/tail node are helpful.
```cpp

```

## priority queue
```cpp
priority_queue<int> maxHeap;
priority_queue<int, vector<int>, greater<int>> minHeap;

priority_queue<int> pq;
// Inserting elements
pq.push(10);
pq.push(30);
pq.push(20);
pq.push(5);

// Size of the priority queue
cout << "Size of priority queue: " << pq.size() << endl;

// Accessing the top element (largest)
cout << "Top element (max): " << pq.top() << endl;

while(!pq.empty()) {
    pq.pop();
}

// custom comparator 
struct Compare {
    bool operator()(pair<int, int>& p1, pair<int, int>& p2) {
        return p1.second > p2.second;
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
pq.push({1, 10});
pq.push({2, 5});
pq.push({3, 20});

```

## stack
```cpp
stack<int> s;
s.push(1);
s.push(2);

int len = s.size();

int sum = 0;
while (!s.empty()) {
    sum += s.top();
    s.pop();
}
```
Here's a more interesting example using a stack when doing DFS on a graph represented by a 2D vector: 
```

```

## queue
```cpp
queue<int> q;
q.push(1);  // push BACK to the queue
q.push(2);
q.push(3);
int head = q.front(); // 1
int tail = q.back();  // 3

int sum = 0;
while (!q.empty()) {
    sum += q.front(); // q front is next item to pop
    q.pop();          // pop FRONT of the queue
}
```

## dequeue

## string
### basic operations
```cpp
string s1;
string s2 ("Hello");
string s3(10, 'x');
string s3(10, 42); // ascii for x


s1.push_back('a');
s1 += 'b';
s1 += "cdef";

s1.substr(start_pos, len);
size_t pos = s1.find("def");
string s = s1.substr(pos);
```

```cpp
string deep_slice = s.substr(startIdx, length);
// deep copy the substring to deep_slice

std::string_view shallow_slice(s.c_str() + startIdx, length);
// creates a shallow_slice referencing to original string
```

### prefix tree (trie)
```cpp
class Trie {
private:
    vector<Trie*> children;
    bool isEnd;

    Trie* searchPrefix(string s) {
        Trie* node = this;
        for (char c : s) {
            int idx = c - 'a';
            if (!node->children[idx]) return nullptr;
            node = node->children[idx];
        }
        return node;
    }

public:
    Trie()
        : children(26)    // initialize children = vector<int>(26,nullptr)
        , isEnd(false) {} // initialize isEnd = false

    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) node->children[idx] = new Trie();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        Trie* node = searchPrefix(word);
        return node != nullptr && node->isEnd;
    }

    bool startsWith(string prefix) {
        Trie* node = searchPrefix(prefix);
        return node != nullptr;
    }
};
```
several remarks (on oop):
-  ```Trie* t = new Trie()``` vs ```Trie t = Trie()```: first allocate memory on heap (and requires you manually ```delete```) while second allocate on stack
- ```this``` is a pointer to current object
- 
 

 # Advanced data structure 

## union find
naive union find without path contraction:
```cpp
int find(vector<int>& p, int x) {
    if (find[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

void union(vector<int>& p, int x, int y) {
    int p1 = find(p, x);
    int p2 = find(p, y);
    if (p1 != p2) {
        p[p1] = p2;
    }
}

int main() {
    int n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i; // union set initialized as n nodes
    }
    int m;
    vector<pair<int, int> > relations(m);
    for (int i = 0; i < m; i++) {
        int x = relations[i].first;
        int y = relations[i].second;
        union(p, x, y);
    }
}
```

## dequeue + obtain max element in O(1)
