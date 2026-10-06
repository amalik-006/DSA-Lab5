# DSA Lab 5 — Circular Doubly Linked List

## Task 1 — Browser Tab Manager

Implemented operations:

* Open New Tab
* Close Current Tab
* Move Next
* Move Previous
* Display Current Tab
* Display All Tabs Forward
* Display All Tabs Backward
* Search Tab by ID

**File:** `Task1/browser_tabs.cpp`

## Task 2 — Circular Photo Album

Implemented operations:

* Add Photo
* Insert Photo After Current
* Remove Photo by ID
* Remove Current Photo
* Move Next
* Move Previous
* Display Album Forward
* Display Album Backward
* Search Photo by ID
* Count Photos

**File:** `Task2/photo_album.cpp`

## Task 3 — Train Coach Navigation System

Implemented operations:

* Add Coach
* Insert Coach After a Specified Coach
* Remove Coach
* Move Forward
* Move Backward
* Display Train Clockwise
* Display Train Anti-clockwise
* Search Coach
* Find Maximum Available Capacity
* Display Current Coach
* Reverse Train Direction

**File:** `Task3/train_coaches.cpp`

## Implementation

* Circular Doubly Linked List used for all three tasks.
* Nodes are dynamically allocated.
* `next` and `prev` pointers are maintained for bidirectional circular traversal.
* No arrays, vectors, or built-in containers are used to store nodes.
* Empty and single-node cases are handled.
* Deleted nodes are properly deallocated.
* Traversal stops when the starting node is reached.
* Task 3 reverses the train by modifying the existing nodes' `next` and `prev` pointers.

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -pedantic Task1/browser_tabs.cpp -o Task1/browser_tabs
g++ -std=c++17 -Wall -Wextra -pedantic Task2/photo_album.cpp -o Task2/photo_album
g++ -std=c++17 -Wall -Wextra -pedantic Task3/train_coaches.cpp -o Task3/train_coaches
```

## Execution

```bash
./Task1/browser_tabs
./Task2/photo_album
./Task3/train_coaches
```

## Memory Testing

```bash
valgrind --leak-check=full --show-leak-kinds=all ./Task1/browser_tabs
valgrind --leak-check=full --show-leak-kinds=all ./Task2/photo_album
valgrind --leak-check=full --show-leak-kinds=all ./Task3/train_coaches
```

Expected Valgrind result:

```text
ERROR SUMMARY: 0 errors from 0 contexts
```

## Repository Structure

```text
DSA-Lab5/
├── Task1/
│   └── browser_tabs.cpp
├── Task2/
│   └── photo_album.cpp
├── Task3/
│   └── train_coaches.cpp
├── .gitignore
└── README.md
```

