#pragma once
#include <cassert>

template<typename T>
class ForwardList {
public:
    ForwardList() : first(nullptr) {}
    ~ForwardList();

    bool empty() const;
    void push_front(const T& val);
    void pop_front();

    // Implement these functions without using
    //  any loops - only recursion. 
    // You will need to use
    //  helper functions e.g. contains_impl
    //  to assist with the recursion.

    // This one is implemented as an example
    int size() const;

    // EFFECTS: returns true if and only if T is
    //  in the list.
    bool contains(const T &val) const;
    // EFFECTS: pushes val onto the end of the list.
    void push_back(const T &val);
    // EFFECTS: removes the element at the end of the list
    void pop_back();

    // EFFECTS: adds all the elements between begin and end
    //  to the beginning of the list.
    // HINT: go backwards through (begin, end).
    //       This one does not need a helper function.
    template<typename Iter_type>
    void prepend_range(Iter_type begin, Iter_type end);

private:
    struct Node {
        T datum;
        Node *next;
    };
    Node *first;

    // Helper functions defined here
    void dtor_impl();
    static int size_impl(Node *n);
    static bool contains_impl(Node *n, const T& val);
    static void push_back_impl(Node *n, const T& val);
    static void pop_back_impl(Node *n);

    // Disallow copying
    ForwardList &operator=(ForwardList &other) {}
    ForwardList(ForwardList &other) {}

public:
    struct Iterator : std::iterator<std::forward_iterator_tag, T> {
    public:
        Iterator() : n(nullptr) {}
        Iterator(Node *n) : n(n) {}
        T &operator*() const {
            return n->datum;
        }
        Iterator &operator++() {
            n = n->next;
            return *this;
        }
        bool operator!=(Iterator &other) {
            return n != other.n;
        } 
    private:
        Node *n;
    };

    Iterator begin() { return Iterator{first}; }
    Iterator end() { return Iterator{nullptr}; }
};

template<typename T>
ForwardList<T>::~ForwardList() {
    dtor_impl();
}

template<typename T>
void ForwardList<T>::dtor_impl() {
    if (empty()) {
        return;
    }
    pop_front();
    dtor_impl();
}

template<typename T>
bool ForwardList<T>::empty() const {
    return first == nullptr;
}

template<typename T>
void ForwardList<T>::pop_front() {
    if (!first) {
        return;
    }
    Node *n = first;
    first = first->next;
    delete n;
}

template<typename T>
void ForwardList<T>::push_front(const T& val) {
    Node *n = new Node{val, first};
    first = n;
}


template<typename T>
int ForwardList<T>::size() const {
    return size_impl(first);
}

template<typename T>
int ForwardList<T>::size_impl(Node *n) {
    // base case: empty list has size 0
    if (!n) {
        return 0;
    }
    // recursive case
    return 1 + size_impl(n->next);
}

template<typename T>
bool ForwardList<T>::contains(const T &val) const {
     return contains_impl(first, val);
}

template<typename T>
bool ForwardList<T>::contains_impl(Node *n, const T &val) {
    if (n == nullptr){
        return false;
    }
    if (n->datum == val){
        return true;
    }
    return contains_impl(n->next, val);
}

template<typename T>
void ForwardList<T>::push_back(const T &val) {
    if (empty()){
        push_front(val);
        return;
    }
    push_back_impl(first, val);   
}

template<typename T>
void ForwardList<T>::push_back_impl(Node *n, const T &val) {
    if (n->next == nullptr){
        n->next = new Node{val, nullptr};
        return;
    }
    push_back_impl(n->next, val);
}

template<typename T>
void ForwardList<T>::pop_back() {
    if (empty()){
        return;
    }
    if (first->next == nullptr){
        pop_front();
        return;
    }
    pop_back_impl(first);
}

template<typename T>
void ForwardList<T>::pop_back_impl(Node *n) {
    if (n->next->next == nullptr) {
        delete n->next;
        n->next = nullptr;
        return;
    }
    pop_back_impl(n->next);
}

template<typename T> template<typename Iter_type>
void ForwardList<T>::prepend_range(Iter_type begin, Iter_type end) {
    if (begin == end) {
        return;
    }
    Iter_type temp = begin;
    ++temp;
    prepend_range(temp, end);
    push_front(*begin);
}