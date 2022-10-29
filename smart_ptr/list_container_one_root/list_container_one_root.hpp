#pragma once

template <typename T>
class ListContainerOR {
  struct Node {
    std::shared_ptr<Node> next;
    T data;
  };

 public:
  ListContainerOR() = default;

  ListContainerOR(const ListContainerOR& other) {
    for (const auto& temp : other) {
      push_back(temp);
    }
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

  // ~ListContainerOR() {
  //   if (m_first == nullptr) {
  //     std::cout << "There are not objects to delete" << std::endl;
  //   }
  //   if (m_first != nullptr) {
  //     while (pop_back()) {
  //     }
  //   }
  // }

  ListContainerOR& operator=(const ListContainerOR& rhs) {
    ListContainerOR temp{rhs};
    *this = std::move(temp);

    return *this;
  }

  ListContainerOR& operator=(ListContainerOR&& rhs) noexcept {
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
    auto new_node = std::make_shared<Node>();
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
    auto first = m_first;
    if (pos == 0) {
      auto new_node = std::make_shared<Node>();
      new_node->next = first;
      new_node->data = std::move(value);
      m_first = std::move(new_node);
    } else {
      size_t i = 0;
      while (i != (pos - 1)) {
        first = first->next;
        ++i;
      }
      auto prev = first;
      first = first->next;

      auto new_node = std::make_shared<Node>();
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
    auto first = m_first;
    if (m_size == 1) {
    } else {
      size_t i = 1;
      while (i != m_size - 1) {
        first = first->next;
        ++i;
      }
      m_last = first->next;
      first = m_last->next;
    }
    --m_size;
    return true;
  }

  bool erase(const size_t pos) {
    auto first = m_first;
    if (pos >= m_size) {
      return false;
    }

    if (pos == 0 && m_size > 1) {
      auto next = first->next;
      m_first = std::move(next);

      --m_size;
      return true;
    }

    if (pos > 0 && pos != m_size - 1) {
      size_t i = 0;
      while (i != (pos - 1)) {
        first = first->next;
        ++i;
      }
      auto prev = first;
      auto temp = first->next;
      first = temp->next;
      prev->next = first;

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

      --m_size;
      return true;
    }

    if (m_size == 1) {
      --m_size;
    }
    return true;
  }

  bool getelements() const {
    for (auto elem = m_first; elem != m_last->next; elem = elem->next) {
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
    Iterator(std::shared_ptr<Node> one) : m_one{one} {}

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
    std::shared_ptr<Node> m_one;
  };

  Iterator begin() const { return m_first; }

  Iterator end() const { return {nullptr}; }

  const T& operator[](size_t index) const {
    size_t i = 0;
    auto first = m_first;
    while (i != index) {
      first = first->next;
      ++i;
    }
    return first->data;
  }

  size_t size() const { return m_size; }

 private:
  size_t m_size = 0;
  std::shared_ptr<Node> m_first = nullptr;
  std::shared_ptr<Node> m_last = nullptr;
};
