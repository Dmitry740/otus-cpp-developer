#pragma once

template <typename T>
class ListContainer {
  struct Node {
    Node* next;
    Node* prev;
    T data;
  };

 public:
  ListContainer() = default;

  ListContainer(const ListContainer& other) {
    for (const auto& temp : other) {
      push_back(temp);
    }
    std::cout << "ListContainer(const ListContainer&)" << std::endl;
  }

  bool operator==(const ListContainer& rhs) const {
    if (this == &rhs) {
      return true;
    }
    if (m_size != rhs.m_size) {
      return false;
    }
    auto cont = rhs.begin();
    for (const auto& temp : *this) {
      if (temp != *cont) {
        return false;
      }
      ++cont;
    }
    return true;
  }

  bool operator!=(const ListContainer& rhs) const { return !(*this == rhs); }

  ListContainer(ListContainer&& other) noexcept {
    m_first = other.m_first;
    other.m_first = nullptr;
    m_last = other.m_last;
    other.m_last = nullptr;
    m_size = other.m_size;
    other.m_size = 0;
  }

  ~ListContainer() { std::cout << "~ListContainer" << std::endl; }

  // ~ListContainer() {
  //   delete[] m_first;
  //   delete[] m_last;
  //   std::cout << "~ListContainer" << std::endl;
  // }

  ListContainer& operator=(const ListContainer& rhs) {
    std::cout << "ListContainer::operator=" << std::endl;

    ListContainer temp{rhs};

    *this = std::move(temp);

    return *this;
  }

  ListContainer& operator=(ListContainer&& rhs) noexcept {
    std::cout << "&&ListContainer::operator=" << std::endl;
    if (this == &rhs) {
      return *this;
    }
    m_first = rhs.m_first;
    rhs.m_first = nullptr;
    m_last = rhs.m_last;
    rhs.m_last = nullptr;
    m_size = rhs.m_size;
    rhs.m_size = 0;

    return *this;
  }

  bool push_back(const T& value) {
    Node* new_node = new Node{};
    new_node->prev = std::move(m_last);
    new_node->next = nullptr;
    new_node->data = std::move(value);

    if (m_size == 0) {
      m_first = new_node;
    }

    if (m_size >= 1) {
      m_last->next = new_node;
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
      first->prev = new_node;
      m_first = std::move(new_node);
    } else {
      size_t i = 0;
      while (i != pos) {
        first = first->next;
        ++i;
      }
      Node* prev = first->prev;

      Node* new_node = new Node{};
      new_node->prev = prev;
      new_node->next = first;
      new_node->data = std::move(value);
      first->prev = new_node;
      prev->next = std::move(new_node);
    }

    ++m_size;

    return true;
  }

  bool pop_back() {
    if (m_size == 0) {
      return false;
    }

    if (m_size > 1) {
      Node* last = std::move(m_last);
      m_last = last->prev;
      m_last->next = nullptr;

      delete[] last;

      --m_size;
      return true;
    }

    if (m_size == 1) {
      delete[] m_last;

      --m_size;
    }
    return true;
  }

  bool erase(const size_t pos) {
    Node* first = m_first;
    if (pos >= m_size) {
      return false;
    }
    if (pos == 0 && m_size > 1) {
      Node* next = first->next;
      next->prev = nullptr;
      m_first = std::move(next);

      delete[] first;

      --m_size;
      return true;
    }
    if (pos > 0 && pos != m_size - 1) {
      size_t i = 1;
      while (i != pos) {
        first = first->next;
        ++i;
      }
      Node* next = first->next;
      Node* prev = first->prev;
      prev->next = next;
      next->prev = std::move(prev);

      delete[] first;

      --m_size;
      return true;
    }

    if (pos == m_size - 1) {
      Node* last = m_last;
      m_last = last->prev;
      m_last->next = nullptr;

      delete[] last;
      --m_size;
      return true;
    }

    if (m_size == 1) {
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

  bool empty() const {
    if (m_size == 0) {
      std::cout << "Error: container is empty" << std::endl;
      return true;
    } else {
      return false;
    }
  }

  struct Iterator {
    Iterator(Node* one) : m_one{one} {}

    T& operator*() const { return m_one->data; }
    T& get() const { return m_one->data; }

    Iterator& operator++() {
      m_one = m_one->next;
      return *this;
    }
    Iterator& operator++(int) {
      Iterator it(*this);
      (*this) = m_one->next;
      return *this;
    }

    bool operator==(const Iterator& it) const { return (m_one == it.m_one); }

    bool operator!=(const Iterator& it) const { return !(*this == it); }

   private:
    Node* m_one;
  };

  Iterator begin() const { return m_first; }

  Iterator end() const { return {nullptr}; }

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
  size_t m_size = 0;
  Node* m_last = nullptr;
  Node* m_first = nullptr;
};

template <typename T>
std::iostream& operator<<(std::iostream& os, const ListContainer<T>& other) {
  for (const auto& cont : other) {
    os << cont << ' ';
  }
  return os;
}