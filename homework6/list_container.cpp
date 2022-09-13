#include <iostream>

template <typename T>
class ListContainer {
  struct Node {
    Node* next;
    Node* prev;
    T data;
  };

 public:
  ListContainer() : m_size{0}, m_first{nullptr}, m_last{nullptr} {}

  ListContainer(const ListContainer& oter)
      : ListContainer{other.m_first(), other.m_last()} {
    std::cout << "ListContainer(const ListContainer&)" << std::endl;
  }

  ListContainer(ListContainer&& other) {
    m_first = other.m_first;
    other.m_first = nullptr;
    m_last = other.m_last;
    other.m_last = nullptr;
    m_size = other.m_size;
    m_size = 0;
  }

  ~ListContainer() {
    delete[] m_first;
    delete[] m_last;
    std::cout << "~ListContainer" << std::endl;
  }

  ListContainer& operator=(const ListContainer& rhs) {
    std::cout << "ListContainer::operator=" << std::endl;
    ListContainer temp{rhs};
    Node* last = m_last;
    m_last = temp.m_last;
    temp.m_last = last;

    Node* first = m_first;
    m_first = temp.m_first;
    temp.m_first = first;

    size_t size = m_size;
    m_size = temp.m_size;
    temp.m_size = size;

    return *this;
  }

  ListContainer& operator=(ListContainer&& other) {
    std::cout << "&&ListContainer::operator=" << std::endl;
    ListContainer temp{std::move(rhs)};
    return *this = temp;
  }

  bool push_back(const T& value) {
    Node* new_node = new Node{};
    new_node->prev = std::move(m_last);
    new_node->next = nullptr;
    new_node->data = std::move(value);

    if (m_size == 0) {
      m_first = std::move(new_node);
    }

    if (m_size >= 1) {
      m_last->next = std::move(new_node);
    }

    m_last = std::move(new_node);

    ++m_size;

    return true;
  }

  bool insert(size_t pos, const T& value) {
    Node* first = std::move(m_first);
    if (pos == 0) {
      Node* new_node = new Node{};
      new_node->prev = nullptr;
      new_node->next = std::move(first);
      new_node->data = std::move(value);
      first->prev = std::move(new_node);
      m_first = std::move(new_node);
    } else {
      size_t i = 0;
      while (i != pos) {
        first = first->next;
        ++i;
      }
      Node* prev = first->prev;

      Node* new_node = new Node{};
      new_node->prev = std::move(prev);
      new_node->next = std::move(first);
      new_node->data = std::move(value);
      first->prev = std::move(new_node);
      prev->next = std::move(new_node);
    }

    ++m_size;

    return true;
  }

  bool erase(const size_t pos) {
    Node* first = m_first;
    if (pos >= m_size) {
      return false;
    } else {
      size_t i = 1;
      while (i != pos) {
        first = first->next;
        ++i;
      }
      Node* next = first->next;
      Node* prev = first->prev;
      prev->next = std::move(next);
      next->prev = std::move(prev);

      delete[] first;

      --m_size;
    }
    return true;
  }

  bool getelements() const {
    for (Node* elem = m_first; elem != m_last->next; elem = elem->next) {
      std::cout << elem->data << ' ';
    }
    return true;
  }

  // struct Iterator {
  //   T& operator*() const {
  //     for (Node* elem = m_first; elem != m_last->next; elem = elem->next) {
  //       return elem->data;
  //     }
  //   }

  //   Iterator& operator++() { return *this; }
  //   Iterator& operator++(int) {
  //     Iterator it(*this);
  //     ++*this;

  //     return it;
  //   }

  //   bool operator==(const Iterator& it) const {
  //     if (m_last == it.m_last) return true;
  //   }

  //   bool operator!=(const Iterator& it) const { return !(it == *this); }
  // };

  // Iterator begin() { return m_first; }

  // Iterator end() { return m_last; }

  const T operator[](size_t index) const {
    size_t i = 0;
    Node* first = m_first;
    while (i != index) {
      first = first->next;
      ++i;
    }
    return first->data;
  }

  size_t size() const { return m_size; }

 private:
  size_t m_size;
  Node* m_last;
  Node* m_first;
};

template <typename T>
void print_container(ListContainer<T>& container) {
  std::cout << "Elements: ";
  container.getelements();
  std::cout << std::endl;

  std::cout << "Get 6th elenent: " << container[5];
  std::cout << std::endl;

  std::cout << "Size: " << container.size() << std::endl;
  std::cout << std::endl << std::endl;
}

void test_container() {
  ListContainer<int> int_container;

  int_container.push_back(0);
  int_container.push_back(1);
  int_container.push_back(2);
  int_container.push_back(3);
  int_container.push_back(4);
  int_container.push_back(5);
  int_container.push_back(6);
  int_container.push_back(7);
  int_container.push_back(8);
  int_container.push_back(9);

  // for (auto iter = int_container.begin(); iter != int_container.end();
  // ++iter) {
  //   std::cout << *iter << std::endl;
  // }

  print_container(int_container);

  int_container.erase(7);
  int_container.erase(5);
  int_container.erase(3);

  print_container(int_container);

  int_container.insert(0, 10);

  print_container(int_container);

  int_container.insert(4, 20);

  print_container(int_container);

  int_container.push_back(30);

  print_container(int_container);
}

int main() { test_container(); }