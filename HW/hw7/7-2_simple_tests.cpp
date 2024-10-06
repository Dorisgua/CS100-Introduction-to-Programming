#include <iostream>
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>
#include <algorithm>

// The node structure of the linked-list.
template <typename T>
struct Slist_node {
  T value;
  Slist_node<T> *next;
  Slist_node(const T &val,Slist_node<T> *p):value(val),next(p){}
};

// A declaration for the 'Slist' class.
template <typename T>
class Slist;

// When 'is_const' is true, this is a const_iterator. Otherwise, it is a normal iterator.
template <typename T, bool is_const>
class Slist_iterator {
 public:
  using value_type = T;
  using difference_type = typename Slist<T>::difference_type;
  // What is std::conditional<...>::type? Have a guess.
  using pointer = typename std::conditional<is_const, const T *, T *>::type;
  using reference = typename std::conditional<is_const, const T &, T &>::type;
  using iterator_category = std::forward_iterator_tag;

 private:
  using node_t = Slist_node<T>;
  using self_t = Slist_iterator<T, is_const>;

  // The current position that this iterator is pointing to.
  node_t *m_cur;

 public:
  Slist_iterator(node_t *pos = nullptr) : m_cur(pos) {}

  // Allow conversion from iterator to const_iterator, but not vice versa.
  // You don't need to understand the definition of this function.
  template <typename Other,
            typename = typename std::enable_if<
                is_const &&
                std::is_same<Other, Slist_iterator<T, false>>::value>::type>
  Slist_iterator(const Other &oi) : m_cur(oi.base()) {}

  // You may need these two functions in your Slist.
  node_t *base() const {
    return m_cur;
  }

  self_t next() const {
    return self_t(m_cur->next);
  }

  // Dereference operator.
  reference operator*() const {
    return m_cur->value;
  }

  // This operator is a little bit tricky.
  // To work in consistence with operator*, it is always defined as follows.
  pointer operator->() const {
    return std::addressof(operator*());
  }

  // Prefix operator++, as in '++iter'.
  self_t &operator++() {
    m_cur = m_cur->next;
	  return *this;
  }

  // Postfix operator++, as in 'iter++'.
  self_t operator++(int) {
    // Slist_iterator a(*this);
    // m_cur=m_cur->next;
    // return a;
    self_t t=*this;
    m_cur=m_cur->next;
    return t;
  }
};

// Comparison between iterator and const_iterator should be allowed.
template <typename T, bool C1, bool C2>
inline bool operator==(const Slist_iterator<T, C1> &lhs,
                       const Slist_iterator<T, C2> &rhs) {
  return lhs.base() == rhs.base();
}

template <typename T, bool C1, bool C2>
inline bool operator!=(const Slist_iterator<T, C1> &lhs,
                       const Slist_iterator<T, C2> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
class Slist {
 public:
  // Every STL container should have the following type aliases.
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = T *;
  using reference = T &;
  using const_pointer = const T *;
  using const_reference = const T &;

  using iterator = Slist_iterator<T, false>;
  using const_iterator = Slist_iterator<T, true>;

 private:
  using node_t = Slist_node<T>;

  // m_head is the head of the linked-list.
  // m_length is the number of elements stored in the list.
  node_t *m_head;
  size_type m_length;

 public:
  // You also need to implement the default-constructor, copy-constructor, copy-assignment operator and destructor.
  // The default-constructor initializes an empty linked-list.
  Slist():m_head(nullptr),m_length(0){};
  // Both the copy-constructor and the copy-assignment operator provide 'value-semantics',
  // which means that they copy all the elements stored in the list instead of copying only the 'm_head' pointer.
  Slist(const Slist &other)
  {
    m_length=other.m_length;
    if(other.m_head==nullptr) return;
    else{
      m_head=new node_t(other.m_head->value,nullptr);
      node_t *p=m_head;
      node_t *temp=other.m_head->next;
      while(temp!=nullptr){
        p->next=new node_t(temp->value,nullptr);
        temp=temp->next;
        p=p->next;
      }
    }
  }
  Slist &operator=(const Slist &other)
  {
    if(this==&other) return *this;
    else{
      clear();
      m_length=other.m_length;
      if(other.m_head==nullptr){
        m_head=nullptr;
        return *this;
      }
      else{
        m_head=new node_t(other.m_head->value,nullptr);
        node_t *p=m_head;
        node_t *temp=other.m_head->next;
        while(temp!=nullptr){
          p->next=new node_t(temp->value,nullptr);
          temp=temp->next;
          p=p->next;
        }
        return *this;
      }
    }
  }
  // For the copy-assignment operator, we highly recommend using the
  // 'copy-and-swap' technique. If you don't know what it is, you can refer to the reference solution of hw5-1.
  // The destructor should destroy every node and deallocate the memory they take up.
  ~Slist(){
    while(m_head!=nullptr){
      node_t *temp=m_head->next;
      delete m_head;
      m_head=temp;
    }
    m_length=0;
  }
  // Insert an element with given value to be the front of the list.
  void push_front(const value_type &value) {
    node_t *p=m_head;
    m_length++;
    m_head=new node_t(value,nullptr);
    m_head->next=p;
  }
  // Remove the element at the beginning of the list.
  void pop_front() {
    if(m_head!=nullptr){     
      node_t *p=m_head;
      m_head=m_head->next;
      delete p;
      m_length--;
    }
  }
  // Insert an element with given value after the position denoted by 'pos'.
  // Return an iterator pointing to the element that has been inserted.
  iterator insert_after(const_iterator pos, const value_type &value) {    
    node_t *b=new node_t(value,pos.base()->next);
    pos.base()->next=b;
    m_length++;
    iterator iter(b);
    return iter;
  }
  // Erase the element after the position denoted by 'pos'.
  void erase_after(const_iterator pos) {
    if(pos!=end()&&pos.next()!=end()){
      //pos.base()->next=pos.base()->next->next;
      node_t *a,*b,*c;
      a=pos.base();
      b=(++pos).base();
      c=(++pos).base();
      delete b;
      a->next=c;
      m_length--;
    }
  }
  // You also need to implement size(), empty(), clear(), which all follow the STL fashion.
  // Note that://size() should return a value of the type 'size_type'.
               // After clear(), the list should contain zero elements and size() == 0.
  size_type size()const{
    return m_length;
  }
  bool empty()const{
    if(m_length==0) return true;
    else return false;
  }
  void clear(){
    while(m_head!=nullptr){
      node_t *temp=m_head->next;
      delete m_head;
      m_head=temp;
    }
    m_length=0;
  }
  // The following are the well-known 'begin' and 'end' functions.
  iterator begin() {
    return iterator(m_head);
  }
  iterator end() {
    return iterator(nullptr);
  }
  // Why do we need these two functions? Think about this.
  const_iterator begin() const {
    return const_iterator(m_head);
  }
  const_iterator end() const {
    return const_iterator(nullptr);
  }
  // Note: It was not until C++11 that cbegin() and cend() were added to the standard.
  const_iterator cbegin() const {
    return begin();
  }
  const_iterator cend() const {
    return end();
  }
};
// Two Slists are equal if they are of the same length, and every pair of corresponding elements are equal.
// It is guaranteed that we will only use this operator when bool operator==(const T &, const T &) is defined.
// Hint: Use std::equal and the iterators you have defined.
template <typename T>
inline bool operator==(const Slist<T> &lhs, const Slist<T> &rhs) {
  if(lhs.size()!=rhs.size()) return false;
  else{
    return std::equal(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
  }
}
// Lexicographical-order comparison.
// It is guaranteed that we will only use this operator when bool operator<(const T &, const T &) is defined.
// Hint: Use std::lexicographical_compare and the iterators you have defined.
template <typename T>
inline bool operator<(const Slist<T> &lhs, const Slist<T> &rhs) {
  return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}

// Why do we define the following functions like this? Think about it.
template <typename T>
inline bool operator!=(const Slist<T> &lhs, const Slist<T> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
inline bool operator>(const Slist<T> &lhs, const Slist<T> &rhs) {
  return rhs < lhs;
}

template <typename T>
inline bool operator<=(const Slist<T> &lhs, const Slist<T> &rhs) {
  return !(lhs > rhs);
}

template <typename T>
inline bool operator>=(const Slist<T> &lhs, const Slist<T> &rhs) {
  return !(lhs < rhs);
}

/**********************************************************/

// #include or paste your code here and compile this code.

/**********************************************************/

// This type is not default-constructible and not copy-assignable.
// You should make sure that your Slist can store such thing.
class Special_type {
  int x;

 public:
  Special_type() = delete;
  Special_type(const Special_type &) = default;
  Special_type &operator=(const Special_type &) = delete;
  Special_type(int xx) : x(xx) {}
  int get() const {
    return x;
  }
};

inline bool operator==(const Special_type &lhs, const Special_type &rhs) {
  return lhs.get() == rhs.get();
}

inline bool operator<(const Special_type &lhs, const Special_type &rhs) {
  return lhs.get() < rhs.get();
}

// The following are some compile-time checks.

static_assert(std::is_default_constructible<Slist<int>>::value,
              "Slist should be default-constructible.");

static_assert(std::is_copy_constructible<Slist<int>>::value,
              "Slist should be copy-constructible.");

static_assert(std::is_copy_assignable<Slist<int>>::value,
              "Slist should be copy-assignable.");

// Note: even if the following two assertions succeed, your Slist may still have
// some problem when storing data of the Special_type. These static-assertions
// only deduce whether the relevant functions are callable, without actually
// calling them. You need to try on your own to test whether any error arises
// when some functions are called.

static_assert(std::is_default_constructible<Slist<Special_type>>::value,
              "Slist<T> should be default-constructible even if T is not.");

static_assert(std::is_copy_assignable<Slist<Special_type>>::value,
              "Slist<T> should be copy-assignable even if T is not.");

static_assert(
    std::is_same<decltype(++std::declval<Slist_iterator<int, false>>()),
                 Slist_iterator<int, false> &>::value,
    "Prefix operator++ should return reference to the object itself.");

namespace detail {

template <typename T = Slist_iterator<int, false>,
          typename = decltype(((const T *)nullptr)->operator*())>
std::true_type deref_const_helper(int);

std::false_type deref_const_helper(double);

constexpr bool deref_is_const = decltype(deref_const_helper(0))::value;

template <typename T = Slist<int>,
          typename = decltype(((const T *)nullptr)->size())>
std::true_type size_const_helper(int);

std::false_type size_const_helper(double);

constexpr bool size_is_const = decltype(size_const_helper(0))::value;

template <typename T = Slist<int>,
          typename = decltype(((const T *)nullptr)->empty())>
std::true_type empty_const_helper(int);

std::false_type empty_const_helper(double);

constexpr bool empty_is_const = decltype(empty_const_helper(0))::value;

constexpr bool size_return_size_type =
    std::is_same<decltype(std::declval<Slist<int>>().size()),
                 Slist<int>::size_type>::value;

constexpr bool assignment_return_ref =
    std::is_same<decltype(std::declval<Slist<int>>().operator=(
                     std::declval<Slist<int>>())),
                 Slist<int> &>::value;

} // namespace detail

static_assert(detail::deref_is_const,
              "Why don't you define Slist_iterator::operator* as a const "
              "member function?");

static_assert(detail::size_is_const,
              "Why don't you define Slist::size as a const member function?");

static_assert(detail::empty_is_const,
              "Why don't you define Slist::empty as a const member function?");

static_assert(
    detail::size_return_size_type,
    "The return-type of Slist<T>::size() should be Slist<T>::size_type.");

static_assert(
    detail::assignment_return_ref,
    "operator= should return reference to the object on the left-hand side.");

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define SET_COLOR(COLOR, STRING) (ANSI_COLOR_##COLOR STRING ANSI_COLOR_RESET)

#define RED(STRING) SET_COLOR(RED, STRING)
#define GREEN(STRING) SET_COLOR(GREEN, STRING)

inline void report_if_wrong(bool condition, long line) {
  if (!condition) {
    std::cout << ANSI_COLOR_RED "Wrong on line " << line << ANSI_COLOR_RESET
              << std::endl;
    exit(0);
  }
}

#ifdef assert
#undef assert
#endif

#define assert(COND) report_if_wrong(COND, __LINE__)

int main() {
  std::cout << GREEN("You've passed the compile-time tests.") << std::endl;

  int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  Slist<int> list;
  for (auto x : a)
    list.push_front(x);
  assert(list.size() == 10);
  assert(!list.empty());
  int num = 0;
  for (auto x : list)
    assert(x == num++);

  for (auto i = 0; i != 5; ++i)
    list.pop_front();
  assert(list.size() == 5);
  assert(!list.empty());
  num = 5;
  for (auto x : list)
    assert(x == num++);

  --*list.begin();
  --*list.begin();
  list.insert_after(list.cbegin(), 5);
  list.insert_after(list.cbegin(), 4);
  assert(list.size() == 7);
  assert(!list.empty());
  num = 3;
  for (auto x : list)
    assert(x == num++);

  for (auto i = 0; i != 4; ++i)
    list.erase_after(list.begin());
  assert(list.size() == 3);
  assert(!list.empty());
  *list.begin() = 7;
  num = 7;
  for (auto x : list)
    assert(x == num++);

  list.clear();
  assert(list.size() == 0);
  assert(list.empty());
  assert(list.begin() == list.end());

  std::cout << GREEN("Congratulations! You've passed the simple test.")
            << std::endl;
  return 0;
}