#ifndef MAP_HPP
#define MAP_HPP

#include "BinarySearchTree.hpp"
#include <cassert>  //assert
#include <utility>  //pair

template <typename Key_type, typename Value_type,
          typename Key_compare=std::less<Key_type> // default argument
         >
class Map {

private:
  using Pair_type = std::pair<Key_type, Value_type>;

  class PairComp {
    private:
      Key_compare less;

    public:
      bool operator()(const Pair_type& lhs, const Pair_type& rhs) const {
        return less(lhs.first, rhs.first);
    }
  };

  BinarySearchTree<Pair_type, PairComp> bst;

public:

  using Iterator = typename BinarySearchTree<Pair_type, PairComp>::Iterator;


  // Default ctor
  Map() {
  }

  // copy ctor
  Map(const Map& other) : bst(other.bst) {}


  // dtor
  ~Map() = default;

  // copy assignment
  Map& operator=(const Map &other) {
    if (this != &other) {
      bst = other.bst;
    }
    return *this;
  }

  // EFFECTS : Returns whether this Map is empty.
  bool empty() const {
    return bst.empty();
  }

  // EFFECTS : Returns the number of elements in this Map.
  // NOTE : size_t is an integral type from the STL
  size_t size() const{
    return static_cast<size_t>(bst.size());
  }

  // EFFECTS : Searches this Map for an element with a key equivalent
  //           to k and returns an Iterator to the associated value if found,
  //           otherwise returns an end Iterator.
  //
  Iterator find(const Key_type& k) const {
    return bst.find({k, Value_type()});
  }


  // MODIFIES: this
  // EFFECTS : Returns a reference to the mapped value for the given
  //           key. If k matches the key of an element in the
  //           container, the function returns a reference to its
  //           mapped value. If k does not match the key of any
  //           element in the container, the function inserts a new
  //           element with that key and a value-initialized mapped
  //           value and returns a reference to the mapped value.
  //           Note: value-initialization for numeric types guarantees the
  //           value will be 0 (rather than memory junk).
  //

 Value_type& operator[](const Key_type& k) {
    Iterator it = find(k);
    if (it != end()) {
      return it->second;
    }
    std::pair<Iterator, bool> result = insert({k, Value_type()});
    return result.first->second;
 }


  // MODIFIES: this
  // EFFECTS : Inserts the given element into this Map if the given key
  //           is not already contained in the Map. If the key is
  //           already in the Map, returns an iterator to the
  //           corresponding existing element, along with the value
  //           false. Otherwise, inserts the given element and returns
  //           an iterator to the newly inserted element, along with
  //           the value true.
  std::pair<Iterator, bool> insert(const Pair_type &val){
    std::pair<Iterator, bool> result;
    if (find(val.first) != end()) {
      result.first = find(val.first);
      result.second = false;
    }
    else {
      result.first = bst.insert(val);
      result.second = true;
    }
    return result;
  }

  // EFFECTS : Returns an iterator to the first key-value pair in this Map.
  Iterator begin() const{
    return bst.begin();
  }

  // EFFECTS : Returns an iterator to "past-the-end".
  Iterator end() const{
    return bst.end();
  }
};


#endif