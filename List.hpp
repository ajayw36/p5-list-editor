#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return first == nullptr && last == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const {
    return list_size;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    if (empty()) {
      first = new Node();
      first->datum = datum;
      first->prev = nullptr;
      first->next = nullptr;
      last = first;
    }
    else {
      Node* new_node = new Node();
      new_node->datum = datum;
      new_node->next = first;
      new_node->prev = nullptr;
      first->prev = new_node;
      first = new_node;
    }
    ++list_size;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    if (empty()) {
      first = new Node();
      first->datum = datum;
      first->prev = nullptr;
      first->next = nullptr;
      last = first;
    }
    else {
      Node* new_node = new Node();
      new_node->datum = datum;
      new_node->prev = last;
      new_node->next = nullptr;
      last->next = new_node;
      last = new_node;
    }
    ++list_size;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    if (list_size == 1) {
      delete first;
      first = nullptr;
      last = nullptr;
    }
    else {
      Node* temp = first->next;
      delete first;
      first = temp;
      first->prev = nullptr;
    }
    --list_size;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    if (list_size == 1) {
      delete first;
      first = nullptr;
      last = nullptr;
    }
    else {
      Node* temp = last->prev;
      delete last;
      last = temp;
      last->next = nullptr;
    }
    --list_size;
  }

  //MODIFIES: invalidates all iterators to the removed elements
  //EFFECTS:  removes all items from the list
  void clear() {
    while (first) {
      Node* temp = first->next;
      delete first;
      first = temp;
    }
    last = nullptr;
    list_size = 0;
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

  List() : first(nullptr), last(nullptr), list_size(0) {}

  List(const List &other) : first(nullptr), last(nullptr), list_size(0) {
    copy_all(other);
  }

  ~List() {
    clear();
  }

  List& operator=(const List &other) {
    if (this == &other) {
      return *this;
    }
    clear();
    copy_all(other);
    return *this;
  }



private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    Node* it = other.first;
    while(it) {
      push_back(it->datum);
      it = it->next;
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

  int list_size; // private member variable to keep track of list size 

public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.

    Iterator () : list_ptr(nullptr), node_ptr(nullptr) {};

    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.


    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.

    T & operator* () const {
      assert(node_ptr);
      return node_ptr->datum;
    }

    Iterator & operator++ () {
      assert(node_ptr);
      node_ptr = node_ptr -> next;
      return *this;
    }

    Iterator operator++ (int /* postfix */) {
      assert(node_ptr);
      Iterator copy = *this;
      operator++();
      return copy;
    }

    bool operator== (Iterator rhs) const {
      return node_ptr == rhs.node_ptr && list_ptr == rhs.list_ptr;
    }

    bool operator!= (Iterator rhs) const {
      return !(*this == rhs);
    }


    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      assert(*this != list_ptr->begin());
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here


    // add any friend declarations here

    friend class List;


    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np) : list_ptr(lp), node_ptr(np) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {return Iterator(this, first);}

  // return an Iterator pointing to "past the end"
  Iterator end() const {return Iterator(this, nullptr);}

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i) {
    Node* curr = i.node_ptr;
    Node* after = curr->next;

    if (list_size == 1) {
      first = nullptr;
      last = nullptr;
    }
    else if (curr->prev == nullptr) {
      after->prev = nullptr;
      first = after;
    }
    else if (after == nullptr) {
      curr->prev->next = nullptr;
      last = curr->prev;
    }
    else {
      curr->prev->next = after;
      after->prev = curr->prev;
    }

    delete curr;
    --list_size;

    return Iterator(this, after);

  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum) {
    Node* curr = i.node_ptr;

    Node* new_node = new Node();
    new_node->datum = datum;

    if (empty()) {
      first = new_node;
      last = new_node;
      new_node->prev = nullptr;
      new_node->next = nullptr;
    }
    else if (i.node_ptr == first) {
      new_node->prev = nullptr;
      new_node->next = curr;
      curr->prev = new_node;
      first = new_node;
    }
    else if (curr == nullptr) {
      new_node->next = nullptr;
      new_node->prev = last;
      last->next = new_node;
      last = new_node;
    }
    else {
      new_node->prev = curr->prev;
      new_node->next = curr;
      curr->prev->next = new_node;
      curr->prev = new_node;
    }
  
    ++list_size;
    return Iterator(this, new_node);
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
