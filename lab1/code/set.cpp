#include "set.hpp"

#include <algorithm>  //std::swap

/*
* std::size_t is defined in the C++ standard library
* std::size_t is an unsigned integer type that can store the maximum size of any possible object
* sizes are non-negative integers -- i.e. unsigned integer type
*/

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ************************************ */

// Default constructor
Set::Set() : head{new Node{}}, counter{0} {  // create the dummy node
}

// Constructor for creating a singleton {x}
Set::Set(int x) : Set() {
    insert(head, x);
}

// Constructor: create a set with elements
// elements is not sorted and values in it may not be unique
Set::Set(const std::vector<int>& elements) : Set() {
    /*
    * Sorting a vector cannot be used here
    * std::sort and std::unique cannot be used
    */
    for (int i : elements) {
        if (!(member(i))) {
            Node* current = head;
            while ((current->next != nullptr) && current->next->value < i){
                current = current->next;
            }
            insert(current, i);
            // current = current->next;
        }
    }
}

// copy constructor
Set::Set(const Set& rhs) : Set() {
    if (rhs.head == nullptr) {
        return; // Nothing to copy
    }
    Node* current = head;
    Node* ptr_rhs = rhs.head->next;
    while (ptr_rhs != nullptr) {
        insert(current, ptr_rhs->value);
        ptr_rhs = ptr_rhs->next;
        current = current->next;
    }
}

// Assignment operator: use copy-and-swap idiom
Set& Set::operator=(Set rhs) {
    std::swap(head, rhs.head);
    std::swap(counter, rhs.counter);
    return *this;
}

// Destructor: deallocate all nodes
Set::~Set() {
    Node* ptr = head;
    remove(ptr);
}

// Return number of elements in the set
std::size_t Set::cardinality() const {
    return counter;
}

// Test if set is empty
bool Set::empty() const {
    if(counter == 0)
    return true;
    else {
        return false;
    }
}

// Test if x is an element of the set
bool Set::member(int x) const {
    Node* ptr = head->next;
    while ((ptr != nullptr) && (ptr->value != x)) {
        ptr = ptr->next;
    }
    if (ptr == nullptr)
        return false;
    else {
        return true;
    }
}

// Return true, if *this is a subset of Set b
// Otherwise, false is returned
bool Set::is_subset(const Set& b) const {
    if (b.counter < counter) {
        return false;
    }
    Node* ptr = head->next;
    while (ptr != nullptr) {
        if (!b.member(ptr->value)) {
            return false;
        }
        ptr = ptr->next;
    }
    return true;
}

// Return a new Set representing the union of Sets *this and b
// Repeated values are not allowed
// Implement an algorithm similar to the one in exercise 3/Set 1, but don't use vectors
Set Set::set_union(const Set& b) const {
    Set S{};
    Node* ptr = head->next;
    Node* ptrb = b.head->next;
    Node* S_end = S.head;
    while (ptr != nullptr && ptrb != nullptr) {
        if (ptr->value < ptrb->value) {
            S.insert(S_end, ptr->value);
            ptr = ptr->next;
            S_end = S_end->next;
        }
        else if (ptrb->value < ptr->value) {
            S.insert(S_end, ptrb->value);
            ptrb = ptrb->next;
            S_end = S_end->next;
        }
        else {
            S.insert(S_end, ptr->value);
            ptr = ptr->next;
            ptrb = ptrb->next;
            S_end = S_end->next;
        }   
    }
    while (ptr != nullptr) {
        S.insert(S_end, ptr->value);
        ptr = ptr->next;
        S_end = S_end->next;
    }
    while (ptrb != nullptr) {
        S.insert(S_end, ptrb->value);
        ptrb = ptrb->next;
        S_end = S_end->next;
    }
    return S;
}

// Return a new Set representing the intersection of Sets *this and b
Set Set::set_intersection(const Set& b) const {
    Set S{};
    Node* ptr = head->next;
    Node* ptrb = b.head->next;
    Node* S_end = S.head;
    while (ptr != nullptr && ptrb != nullptr) {
        if (ptr->value < ptrb->value) {
            ptr = ptr->next;
        }
        else if (ptrb->value < ptr->value) {
            ptrb = ptrb->next;
        }
        else {
            S.insert(S_end, ptr->value);
            ptr = ptr->next;
            ptrb = ptrb->next;
            S_end = S_end->next;
        }
    }
    return S; 
}

// Return a new Set representing the difference between Set *this and Set b
Set Set::set_difference(const Set& b) const {
    Set S{};
    Node* ptr = head->next;
    Node* ptrb = b.head->next;
    Node* S_end = S.head;
    while (ptr != nullptr && ptrb != nullptr) {
        if (ptr->value < ptrb->value) {
            S.insert(S_end, ptr->value);
            ptr = ptr->next;
            S_end = S_end->next;
        }
        else if (ptrb->value < ptr->value) {
            ptrb = ptrb->next;
        }
        else {
            ptr = ptr->next;
            ptrb = ptrb->next;
        }
    }
    while (ptr != nullptr) {
        S.insert(S_end, ptr->value);
        ptr = ptr->next;
        S_end = S_end->next;
    }
    return S; 
}

std::ostream& operator<<(std::ostream& os, const Set& rhs) {
    if (rhs.empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* ptr = rhs.head->next;
        os << "{ ";
        while (ptr != nullptr) {
            os << ptr->value << " ";
            ptr = ptr->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/

void Set::insert(Node* p, int value) {
    Node* newNode = new Node(value, nullptr);
    newNode->next = p->next;
    p->next = newNode;
    ++counter;
}

 void Set::remove(Node* p) {
     while (p != nullptr) {
         head = p->next;
         delete p;
         p = head;
     }
 }
