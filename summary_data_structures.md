# Summaries of Data Structures 

## Array List (Dynamic Array)

* automatically resizing when it becomes full 
* access by index - $O(1)$ time 

### Time/Space Complexity of an UNSORTED Array List 

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(n)              | O(n)                 | O(1)              | O(n)              |
| Insert            | O(n)              | O(n)                 | O(1)              | O(n)              |
| Remove            | O(n)              | O(n)                 | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

### Time/Space Complexity of an SORTED Array List 

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(log n)          | O(log n)             | O(1)              | O(n)              |
| Insert            | O(n)              | O(n)                 | O(1)              | O(n)              |
| Remove            | O(n)              | O(n)                 | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

## Linked List 

* nodes connected to one another via pointers
* only keep global access to two pointers: a head pointer (which points to the first node) and a tail pointer (which points to the last node)
* In a Singly-Linked List, each node maintains one pointer: a forward pointer that points to the next node in the list
* In a Doubly-Linked List, each node maintains two pointers: a forward pointer that points to the next node in the list, and a previous pointer that points to the previous node in the list
* no direct access to any nodes other than head and tail
* different places in memory 

### Time/Space Complexity of Linked List

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(n)              | O(n)                 | O(1)              | O(n)              |
| Insert            | O(n)              | O(n)                 | O(1)              | O(n)              |
| Remove            | O(n)              | O(n)                 | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

## Skip List 

* every node has multiple layers, where each layer is a forward pointer
* We denote the number of layers a given node has as the node's height
* We typically choose a maximum height, h, that any node in our Skip List can have, where h << n (the total number of nodes)
* We are able to "skip" over multiple nodes in our searches, which allows us to mimic Binary Search when searching for an element in the list
* To determine the height of a new node, we repeatedly flip a weighted coin that has probability p to land on heads, and we keep adding layers to the new node until we encounter our first tails
* Just like with a Linked List, to insert or remove an element, we first run the regular find algorithm and then perform a single O(h) operation to fix pointers

### Time/Space Complexity of Skip List

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(n)              | O(log n)             | O(1)              | O(n log n)        |
| Insert            | O(n)              | O(log n)             | O(h)              | O(n log n)        |
| Remove            | O(n)              | O(log n)             | O(h)              | O(n log n)        |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

## Heap 

* complete binary tree that satisfies the Heap Property
* Heap Property: For all nodes A and B, if node A is the parent of node B, then node A has higher priority (or equal priority) than node B
* A min-heap is a heap in which every node is smaller than (or equal to) all of its children (or has no children)
* A max-heap is a heap where every node is larger than (or equal to) all of its children (or has no children)
* It is common to implement a Heap as an Array List because all of the data will be localized in memory (faster in practice)
* If a Heap is implemented as an Array List, the root is stored in index 0, the next node (in a level-order traversal) is at index 1, then at index 2, etc.
* If a Heap is implemented as an Array List, for a node u stored at index i, u's parent is stored at index \lfloor{\frac{i-1}{2}}\rfloor, u's left child is stored at index 2i+1, and u's right child is stored at index 2i+2

### Time/Space Complexity of Heap

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Peek              | O(1)              | O(1)                 | O(1)              | O(n)              |
| Insert            | O(log n)          | O(log n)             | O(1)              | O(n)              |
| Pop               | O(log n)          | O(log n)             | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

## Binary Search Trees

* any given node is larger than all nodes in its left subtree and smaller than all nodes in its right subtree
* A Randomized Search Tree is a Binary Search Tree + Heap (a "Treap") in which each node has a key and a priority, and the tree maintains the Binary Search Tree Property with respect to keys and the Heap Property with respect to priorities
* An AVL Tree is a self-balancing Binary Search Tree in which, for all nodes in the tree, the heights of the two child subtrees of the node differ by at most one
* A Red-Black Tree is a self-balancing Binary Search Tree in which all nodes must be "colored" either red or black, the root of the tree must be black, red nodes can only have black children, and every path from any node u to a null reference must contain the same number of black nodes
* AVL Trees are stricter than Red-Black Trees in terms of balance, so AVL Trees are typically faster for find operations
* Red-Black Trees only do one pass down the tree for inserting elements, whereas AVL trees need one pass down the tree and one pass back up, so Red-Black Trees are typically faster for insert operations

### Time/Space Complexity of Regular Binary Search Tree

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(n)              | O(log n)             | O(1)              | O(n)              |
| Insert            | O(n)              | O(log n)             | O(1)              | O(n)              |
| Remove            | O(n)              | O(log n)             | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

### Time/Space Complexity of Randomized Search Tree

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(n)              | O(log n)             | O(1)              | O(n)              |
| Insert            | O(n)              | O(log n)             | O(1)              | O(n)              |
| Remove            | O(n)              | O(log n)             | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

### Time/Space Complexity of an AVL Tree

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(log n)          | O(log n)             | O(1)              | O(n)              |
| Insert            | O(log n)          | O(log n)             | O(log n)          | O(n)              |
| Remove            | O(log n)          | O(log n)             | O(log n)          | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

### Time/Space Complexity of a Rad-Black Tree

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(log n)          | O(log n)             | O(1)              | O(n)              |
| Insert            | O(log n)          | O(log n)             | O(log n)          | O(n)              |
| Remove            | O(log n)          | O(log n)             | O(log n)          | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

## B-Tree and B+ Tree

* self-balancing tree in which internal nodes must have at least b and at most 2b children (for some predefined b), all leaves must be on the same level of the tree, the elements within a given node must be in ascending order, and child pointers appear between elements and on the edges of the node
* For two adjacent elements i and j in a B-Tree (where i < j, so i is to the left of j), all elements down the subtree to the left of i must be smaller than i, all elements down the subtree between i and j must be greater than i and less than j, and all elements down the subtree to the right of j must be greater than j
* A B+ Tree can be viewed as a variant of the B-tree in which each internal node contains only keys and the leaves contain the actual data records
* In a B+ Tree, M denotes the maximum number of children any nodes can have, and L denotes the maximum number of data records
* In a B+ Tree, every node has at most M children, every internal node except the root has at least ⌈M/2⌉ children, the root has at least 2 children (if it's not a leaf), an internal node with k children must contain k–1 elements, all leaves must be on the same level of the tree, internal nodes only contain "search keys" (no data records), and the smallest data record between search keys i and j (where i < j) must equal i

### Time/Space Complexity of a B-Tree

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(log n)          | O(log n)             | O(1)              | O(n)              |
| Insert            | O(b log n)        | O(log n)             | O(log n)          | O(n)              |
| Remove            | O(b log n)        | O(log n)             | O(log n)          | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

### Time/Space Complexity of a B+ Tree

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(log n + log L)  | O(log n)             | O(log n)          | O(n)              |
| Insert            | O(M log n + L)    | O(log n)             | O(log n)          | O(n)              |
| Remove            | O(M log n + L)    | O(log n)             | O(log n)          | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

## Hash Table and Hash Map 

* A Hash Table is an array that, given a key key, computes a hash value from key (using a hash function) and then uses the hash value to compute an index at which to store key
* A Hash Map is the exact same thing as a Hash Table, except instead of storing just keys, we store (key, value) pairs
* The capacity of a Hash Table should be prime (to help reduce collisions)
* When discussing the time complexities of Hash Tables/Maps, we typically ignore the time complexity of the hash function
* The load factor of a Hash Table, \alpha = \frac{N}{M} (N = size of Hash Table and M = capacity of Hash Table), should remain below ~0.75 to keep the Hash Table fast (a smaller load factor means better performance, but it also means more wasted space)
* For a hash function h to be valid, given two equal keys k and l, h(k) must equal h(l)
* For a hash function h to be good, given two unequal keys k and l, h(k) should ideally (but not necessarily) not equal h(l)
* A good hash function for a collection that stores k items (e.g. a string storing k characters, or a list storing k objects, etc.) should perform some non-commutative arithmetic that utilizes each of the k elements
In Linear Probing (a form of Open Addressing), collisions are resolved by simply shifting over to the next available slot
* In Double Hashing (a form of Open Addressing), collisions are resolved in a way similar to Linear Probing, except instead of only shifting over one slot at a time, the Hash Table has a second hash function that it uses to determine the "skip" for the probe
* In Random Hashing (a form of Open Addressing), for a given key key, a pseudorandom number generator is seeded with key, and the possible indices are given by the sequence of numbers returned by the pseudorandom number generator
* In Separate Chaining (a form of Closed Addressing), each slot of the Hash Table is actually a data structure itself (typically a Linked List), and when a key hashes to a given index in the Hash Table, simply insert it into the data structure at that index
* In Cuckoo Hashing (a form of Open Addressing), the Hash Table has two hash functions, and in the case of a collision, the new key pushes the old key out of its slot, and the old key uses the other hash function to find a new slot

### Time/Space Complexity of a Hash Table/Map with Linear Probing 

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(n)              | O(1)                 | O(1)              | O(n)              |
| Insert            | O(n)              | O(1)                 | O(1)              | O(n)              |
| Remove            | O(n)              | O(1)                 | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

### Time/Space Complexity of a Hash Table/Map with Double Hashing 

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(n)              | O(1)                 | O(1)              | O(n)              |
| Insert            | O(n)              | O(1)                 | O(1)              | O(n)              |
| Remove            | O(n)              | O(1)                 | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

### Time/Space Complexity of a Hash Table/Map with Random Hashing 

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(n)              | O(1)                 | O(1)              | O(n)              |
| Insert            | O(n)              | O(1)                 | O(1)              | O(n)              |
| Remove            | O(n)              | O(1)                 | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

### Time/Space Complexity of a Hash Table/Map with Separate Chaining 

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(n)              | O(1)                 | O(1)              | O(n)              |
| Insert            | O(n)              | O(1)                 | O(1)              | O(n)              |
| Remove            | O(n)              | O(1)                 | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

### Time/Space Complexity of a Hash Table/Map with Cuckoo Hashing 

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(1)              | O(1)                 | O(1)              | O(n)              |
| Insert            | O(n)              | O(1)                 | O(1)              | O(n)              |
| Remove            | O(1)              | O(1)                 | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

## Multiway Trie 

* A Multiway Trie is a tree structure in which, for some alphabet Σ, edges are labeled by a single character in Σ and nodes can have at most |Σ| children
* For a given "word node" in a Multiway Trie, the key associated with the "word node" is defined by the concatenation of edge labels on the path from the root of the tree to the "word node"
* We use k to denote the length of the longest key in the Multiway Trie and n to denote the number of elements it contains

### Time/Space Complexity of a Multiway Trie 

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | 
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|
| Find              | O(k)              | O(k)                 | O(1)              |
| Insert            | O(k)              | O(k)                 | O(k)              |
| Remove            | O(k)              | O(k)                 | O(1)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |

## Ternary Search Tree 

* A Ternary Search Tree is a trie in which each node has at most 3 children: a middle, left, and right child
For every node u, the left child of u must have a value less than u, and the right child of u must have a value greater than u
* The middle child of u represents the next character in the current word
* For a given "word node," define the path from the root to the "word node" as path, and define S as the set of all nodes in path that have a middle child also in path. The word represented by the "word node" is defined as the concatenation of the labels of each node in S, along with the label of the "word node" itself

### Time/Space Complexity of a Hash Table/Map with Cuckoo Hashing 

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(n)              | O(log n)             | O(k)              | O(n)              |
| Insert            | O(n)              | O(log n)             | O(k)              | O(n)              |
| Remove            | O(n)              | O(log n)             | O(k)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

## Disjoint Set 

* The Disjoint Set ADT is defined by the "union" and "find" operations: "union" merges two sets, and "find" returns which set a given element is in
* We can implement the Disjoint Set ADT very efficiently using Up-Trees
* Under Union-by-Size (also known as "Union-by-Rank"), when you are choosing which sentinel node to make the parent of the other sentinel node, you choose the sentinel node whose set contains the most elements to be the parent
* Under Union-by-Height, when you are choosing which sentinel node to make the parent of the other sentinel node, you choose the sentinel node whose height is larger to be the parent
* Under Path Compression, any time you are performing the "find" operation to find a given element's sentinel node, you keep track of every node you pass along the way, and once you find the sentinel node, directly connect all nodes you traversed directly to the sentinel node
* Even though Union-by-Height is slightly better than Union-by-Size, Path Compression gives us the biggest bang for your buck as far as speed-up goes, and because tree heights change frequently under Path Compression (thus making Union-by-Height difficult to perform), we typically choose to perform Union-by-Size
* In short, most Disjoint Sets are implemented as Up-Trees that perform Path Compression and Union-by-Size

### Time/Space Complexity of a Disjoint Set

| Operation         | Worst-Case Time   | Average-Case Time    | Best-Case Time    | Space Complexity  |
|:-----------------:|:-----------------:|:--------------------:|:-----------------:|:-----------------:|
| Find              | O(log n)          | O(1)                 | O(1)              | O(n)              |
| Union             | O(log n)          | O(1)                 | O(1)              | O(n)              |
|<img width="250"/> |<img width="250"/> |<img width="250"/>    |<img width="250"/> |<img width="250"/> |

## Graphs and Graph Representation 

* A Graph is simply a set of nodes (or "vertices") V and a set of edges E that connect them
* Edges can be either "directed" (i.e., an edge from u to v does not imply an edge from v to u) or "undirected" (i.e., an edge from u to v can also be traversed from v to u)
* Edges can be either "weighted" (i.e., there is some "cost" associated with the edge) or "unweighted"
* We call a graph "dense" if it has a relatively large number of edges, or "sparse" if it has a relatively small number of edges
* Graphs are typically represented as Adjacency Matrices or Adjacency Lists
* For our purposes in this text, we disallow "multigraphs" (i.e., we are disallowing "parallel edges": multiple edges with the same start and end node), meaning our graphs have at most |V|² edges

### Time/Space Complexities of an Adjacency Matrix

#### Time Complexity (Adjacency Matrix)

* We can check if an edge exists between two vertices u and v (and check its cost, if the graph is "weighted") in O(1) time by simply looking at cell (u, v) of our Adjacency Matrix
* If we want to iterate over all outgoing edges of a given node u, we can do no better than O(|V|) time in the worst case because we would have to iterate over the entire u-th row of the Adjacency Matrix (which has |V| columns)

#### Space Complexity (Adjacency Matrix)

* O(|V|²) — We must allocate the entire |V| by |V| matrix


### Time/Space Complexities of an Adjacency List
#### Time Complexity (Adjacency List)

* We can check if an edge exists between two vertices u and v (and check its cost, if the graph is "weighted") by searching for node v in the list of edges in node u's slot in the Adjacency List, which would take O(|E|) time in the worst case (if all |E| of our edges came out of node u)
* If we want to iterate over all outgoing edges of a given node u, because an adjacency list has direct access to this list, we can do so in the least amount of time possible, which would be O(|E|) only in the event that all |E| of our edges come out of node u

#### Space Complexity (Adjacency List)

* O(|V|+|E|) — We must allocate one slot for each of our |V| vertices, and we place each of our |E| edges in their corresponding slot

## Graph Traversal Algorithms 

* In all graph traversal algorithms we discussed, we choose a specific vertex at which to begin our traversal
* In Breadth First Search, we explore the starting vertex, then its neighbors, then their neighbors, etc. In other words, we explore the graph in layers spreading out from the starting vertex
* Breadth First Search can be easily implemented using a Queue to keep track of vertices to explore
* In Depth First Search, we explore the current path as far as possible before going back to explore other paths
* Depth First Search can be easily implemented using a Stack to keep track of vertices to explore
* In Dijkstra's Algorithm, we explore the shortest possible path at any given moment
* Dijkstra's Algorithm can be easily implemented using a Priority Queue, ordered by shortest distance from starting vertex, to keep track of vertices to explore
* For our purposes in this text, we disallow "multigraphs" (i.e., we are disallowing "parallel edges": multiple edges with the same start and end node), meaning our graphs have at most |V|² edges

### Time/Space Complexities of Breadth First Search

#### Time Complexity (Breadth First Search)

* Exploring the entire graph using Breadth First Search would take time O(|V|+|E|) because we have to potentially visit all |V| vertices and traverse all |E| edges, where each visit/traversal is O(1)

#### Space Complexity (Breadth First Search)

* O(|V|+|E|) — We might theoretically have to keep track of every possible vertex and edge in the graph during our exploration
* If we wanted to keep track of the entire current path of every vertex in our Queue, the space complexity would blow up

### Time/Space Complexities of Depth First Search

#### Time Complexity (Depth First Search)

* Exploring the entire graph using Depth First Search would take time O(|V|+|E|) because we have to potentially visit all |V| vertices and traverse all |E| edges, where each visit/traversal is O(1)
Space Complexity (Depth First Search)

* O(|V|+|E|) — We might theoretically have to keep track of every possible vertex and edge in the graph during our exploration
* Because we are only exploring a single path at a time, even if we wanted to keep track of the entire current path, the space required to do so would only be O(|E|) because a single path can have at most |E| edges

### Time/Space Complexities of Dijkstra's Algorithm

#### Time Complexity (Dijkstra's Algorithm)

* We must initialize each of our |V| vertices, and in the worst case, we will insert (and remove) one element into a Priority Queue for each of our |E| edges, resulting in an overall worst-case time complexity of O(|V| + |E| log |E|) overall if our Priority Queue is implemented intelligently (e.g. using a Heap)
Space Complexity (Dijkstra's Algorithm)

* O(|V|+|E|) — We might theoretically have to keep track of every possible vertex and edge in the graph during our exploration

## Minimum Spanning Trees: Prim's and Kruskal's Algorithms

* Given a graph G, a Spanning Tree of G is a tree that hits every node in G
* Given a graph G, a Minimum Spanning Tree of G is a Spanning Tree of G that has the minimum overall cost (i.e., that minimizes the sum of all edge weights)
* We discussed two algorithms that can find a Minimum Spanning Tree in an arbitrary graph G equally efficiently
* Prim's Algorithm starts with a one-node tree and repeatedly finds a minimum-weight edge that connects a node in the tree to a node that is not in the tree, and adds that connecting edge to the tree
* Kruskal's Algorithm starts with a forest of one-node trees and repeatedly finds a minimum-weight edge that connects two previously unconnected trees in the forest and merges the two trees using the edge

### Time Complexity of Prim's Algorithm

#### Worst-Case Time Complexity (Prim's Algorithm)

* O(|V| + |E| log |E|) — We need to initialize all |V| vertices, and we may need to add each of our |E| edges to a Priority Queue (which should be implemented using a Heap).

### Time Complexity of Kruskal's Algorithm

#### Time Complexity (Adjacency List)

* O(|V| + |E| log |E|) — We need to initialize all |V| vertices, and we need to sort all |E| edges. Note that the fastest algorithms to sort a list of n elements are O(n log n).

## Source

* [Stepik Course](https://stepik.org/course/579/syllabus) 