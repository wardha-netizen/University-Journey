# Snake Game (Doubly Linked List) 
**Course:** Data Structures & Algorithms (Semester 3)

A classic Snake Game implemented in **C++** using a **Doubly Linked List** to manage the snake's body segments. This project demonstrates efficient data structure handling for real-time applications.

##  Data Structure Implementation
* **Doubly Linked List (DLL):** Each segment of the snake is a node containing coordinates, with pointers to the next and previous segments.
* **Efficiency:** Adding a new head (when eating) and deleting the tail (during movement) are handled in $O(1)$ time complexity.
* **Logic:** The DLL structure allows the snake to grow dynamically without the memory overhead of a fixed-size array.

##  Features
* **Real-time Movement:** Smooth directional control.
* **Growth Mechanism:** Snake increases in length upon consuming food.
* **Collision Detection:** Includes logic for wall collisions and self-biting detection.

##  Project Files
* **[SnakeGameDoublyLinkedList.cpp](./SnakeGameDoublyLinkedList.cpp):** The complete C++ source code.
* **[DSAProject-Report.pdf](./DSAProject-Report.pdf):** Detailed technical report and algorithm analysis.

##  Tech Stack
* **Language:** C++
* **Concepts:** Doubly Linked Lists, Pointers, Game Logic.
