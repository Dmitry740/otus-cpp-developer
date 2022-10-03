#pragma once

template <typename T>
class ListContainerOR {
  struct Node {
    Node* next;
    T data;
  };

 public:
  ListContainerOR() = default;

  ListContainerOR(const ListContainerOR& other) {
    for (const auto& temp : other) {
      push_back(temp);
    }

    std::cout << "ListContainerOR(const ListContainerOR&)" << std::endl;
  }

  bool operator==(const ListContainerOR& rhs) const {
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

  bool operator!=(const ListContainerOR& rhs) const { return !(*this == rhs); }

  ListContainerOR(ListContainerOR&& other) noexcept {
    m_first = other.m_first;
    other.m_first = nullptr;
    m_last = other.m_last;
    other.m_last = nullptr;
    m_size = other.m_size;
    m_size = 0;
  }

  ~ListContainerOR() { std::cout << "~ListContainerOR" << std::endl; }

  ListContainerOR& operator=(const ListContainerOR& rhs) {
    std::cout << "ListContainerOR::operator=" << std::endl;

    ListContainerOR temp{rhs};
    *this = std::move(temp);

    return *this;
  }

  ListContainerOR& operator=(ListContainerOR&& rhs) noexcept {
    std::cout << "&&ListContainerOR::operator=" << std::endl;
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
    new_node->next = nullptr;
    new_node->data = value;

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
      new_node->next = first;
      new_node->data = std::move(value);
      m_first = std::move(new_node);
    } else {
      size_t i = 0;
      while (i != (pos - 1)) {
        first = first->next;
        ++i;
      }
      Node* prev = first;
      first = first->next;

      Node* new_node = new Node{};
      new_node->next = first;
      new_node->data = std::move(value);
      prev->next = std::move(new_node);
    }

    ++m_size;

    return true;
  }

  bool pop_back() {
    if (m_size == 0) {
      return false;
    }
    Node* first = m_first;
    if (m_size == 1) {
      delete[] m_first;
    } else {
      size_t i = 1;
      while (i != m_size - 1) {
        first = first->next;
        ++i;
      }
      m_last = first->next;
      first = m_last->next;

      delete[] first;
    }
    --m_size;
    return true;
  }

  bool erase(const size_t pos) {
    Node* first = m_first;
    if (pos >= m_size) {
      return false;
    }

    if (pos == 0 && m_size > 1) {
      Node* next = first->next;
      m_first = std::move(next);
      delete[] first;

      --m_size;
      return true;
    }

    if (pos > 0 && pos != m_size - 1) {
      size_t i = 0;
      while (i != (pos - 1)) {
        first = first->next;
        ++i;
      }
      Node* prev = first;
      Node* temp = first->next;
      first = temp->next;
      prev->next = first;

      delete[] temp;

      --m_size;
      return true;
    }

    if (pos == m_size - 1) {
      size_t i = 1;
      while (i != m_size - 1) {
        first = first->next;
        ++i;
      }
      m_last = first;
      first = m_last->next;
      m_last->next = nullptr;

      delete[] first;

      --m_size;
      return true;
    }

    if (m_size == 1) {
      delete[] m_first;

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

    bool operator==(const Iterator& it) const { return m_one == it.m_one; }

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
  Node* m_first = nullptr;
  Node* m_last = nullptr;
};
