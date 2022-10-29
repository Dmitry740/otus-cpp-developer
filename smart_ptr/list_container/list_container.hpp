#pragma once
#include <iostream>

template <typename T>
class ListContainer {
  struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;
    T data;
  };

 public:
  ListContainer() = default;

  ListContainer(const ListContainer& other) {
    for (const auto& temp : other) {
      push_back(temp);
    }
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

  // ~ListContainer() {
  //   if (m_first == nullptr) {
  //     std::cout << "There are not objects to delete" << std::endl;
  //   }
  //   if (m_first != nullptr) {
  //     while (pop_back()) {
  //     }
  //   }
  // }

  ListContainer& operator=(const ListContainer& rhs) {
    ListContainer temp{rhs};

    *this = std::move(temp);

    return *this;
  }

  ListContainer& operator=(ListContainer&& rhs) noexcept {
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
    auto first = m_first;
    if (pos == 0) {
      auto new_node = std::make_shared<Node>();
      new_node->next = first;
      new_node->data = std::move(value);
      first->prev = new_node;
      m_first = std::move(new_node);
    } else {
      size_t i = 0;
      while (i != pos) {
        first = first->next;
        ++i;
      }
      auto prev = first->prev;

      auto new_node = std::make_shared<Node>();
      new_node->prev = prev;
      new_node->next = first;
      new_node->data = std::move(value);
      first->prev = new_node;
      if (const auto temp = prev.lock(); temp) {
        temp->next = std::move(new_node);
      }
    }

    ++m_size;

    return true;
  }

  bool pop_back() {
    if (m_size == 0) {
      return false;
    }

    if (m_size > 1) {
      auto last = std::move(m_last);
      if (auto temp = last->prev.lock(); temp) {
        m_last = temp;
      };

      m_last->next = nullptr;

      --m_size;
      return true;
    }

    if (m_size == 1) {
      --m_size;
    }
    return true;
  }

  bool erase(const size_t pos) {
    auto first = m_first;
    if (pos >= m_size) {
      return false;
    }
    if (pos == 0 && m_size > 1) {
      auto next = first->next;
      next->prev.reset();
      m_first = std::move(next);

      --m_size;
      return true;
    }
    if (pos > 0 && pos != m_size - 1) {
      size_t i = 1;
      while (i != pos) {
        first = first->next;
        ++i;
      }
      auto next = first->next;
      auto prev = first->prev;
      if (auto temp = prev.lock(); temp) {
        temp->next = next;
      };

      next->prev = std::move(prev);

      --m_size;
      return true;
    }

    if (pos == m_size - 1) {
      auto last = m_last;
      if (auto temp = last->prev.lock(); temp) {
        m_last = temp;
      };

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

  bool empty() const noexcept {
    if (m_size == 0) {
      std::cout << "Error: container is empty" << std::endl;
      return true;
    } else {
      return false;
    }
  }

  struct Iterator {
    Iterator(std::shared_ptr<Node> one) : m_one{one} {}

    T& operator*() const noexcept { return m_one->data; }
    T& get() const noexcept { return m_one->data; }

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
    std::shared_ptr<Node> m_one;
  };

  Iterator begin() const noexcept { return m_first; }

  Iterator end() const noexcept { return {nullptr}; }

  const T& operator[](size_t index) const {
    size_t i = 0;
    auto first = m_first;
    while (i != index) {
      first = first->next;
      ++i;
    }
    return first->data;
  }

  size_t size() const noexcept { return m_size; }

 private:
  size_t m_size = 0;
  std::shared_ptr<Node> m_last = nullptr;
  std::shared_ptr<Node> m_first = nullptr;
};

template <typename T>
std::iostream& operator<<(std::iostream& os, const ListContainer<T>& other) {
  for (const auto& cont : other) {
    os << cont << ' ';
  }
  return os;
}