#pragma once

template <typename T>
class SuccessiveContainer {
 public:
  SuccessiveContainer() = default;

  SuccessiveContainer(const SuccessiveContainer& other) {
    for (const auto& temp : other) {
      push_back(temp);
    }
  }

  bool operator==(const SuccessiveContainer& rhs) const {
    if (this == &rhs) {
      return true;
    }
    if (m_size != rhs.m_size) {
      return false;
    }
    for (auto temp = 0; temp < rhs.m_size; ++temp) {
      if ((*this)[temp] != rhs[temp]) {
        return false;
      }
      return true;
    }
    return true;
  }

  bool operator!=(const SuccessiveContainer& rhs) const {
    return !(*this == rhs);
  }

  SuccessiveContainer(SuccessiveContainer&& other) noexcept {
    m_cap = other.m_cap;
    m_size = other.m_size;
    m_region = other.m_region;

    other.m_cap = 0;
    other.m_size = 0;
    other.m_region = nullptr;
  }

  // ~SuccessiveContainer() { delete[] m_region; }

  SuccessiveContainer& operator=(const SuccessiveContainer& rhs) {
    SuccessiveContainer temp{rhs};

    auto data = m_region;
    m_region = temp.m_region;
    temp.m_region = data;

    size_t size = m_size;
    m_size = temp.m_size;
    temp.m_size = size;

    size_t cap = m_cap;
    m_cap = temp.m_cap;
    temp.m_cap = cap;

    return *this;
  }

  SuccessiveContainer& operator=(SuccessiveContainer&& rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }
    m_cap = rhs.m_cap;
    m_size = rhs.m_size;
    m_region = rhs.m_region;

    rhs.m_cap = 0;
    rhs.m_size = 0;
    rhs.m_region = nullptr;

    return *this;
  }

  bool push_back(const T& val) {
    if (m_size < m_cap) {
      m_region[m_size] = std::move(val);
      ++m_size;
    } else {
      m_cap = std::move(((m_size + 1) * 2));
      auto new_region = std::make_shared<T[]>(m_cap);

      for (size_t i = 0; i < m_size; ++i) {
        new_region[i] = m_region[i];
      }

      new_region[m_size] = std::move(val);
      // delete[] m_region;
      m_region = std::move(new_region);

      ++m_size;
    }
    return true;
  }

  bool insert(const size_t& pos, const T& val) {
    if (m_size < m_cap) {
      for (size_t i = m_size; i != pos; --i) {
        m_region[i] = m_region[i - 1];
      }
      m_region[pos] = std::move(val);
      ++m_size;
    } else {
      m_cap = std::move(((m_size + 1) * 2));
      auto new_region = std::make_shared<T[]>(m_cap);

      for (size_t i = 0; i < pos; ++i) {
        new_region[i] = m_region[i];
      }

      for (size_t i = m_size; i != pos; --i) {
        new_region[i] = m_region[i - 1];
      }

      new_region[pos] = std::move(val);

      // delete[] m_region;
      m_region = std::move(new_region);
      ++m_size;
    }
    return true;
  }

  bool pop_back() {
    if (m_size == 0) {
      return false;
    }

    m_region[(m_size - 1)] = m_region[m_size];

    --m_size;
    return true;
  }

  bool erase(const size_t pos) {
    if (pos >= m_size) {
      return false;
    }

    for (size_t i = pos; i < m_size; ++i) {
      m_region[i] = m_region[i + 1];
    }
    --m_size;

    return true;
  }

  bool empty() const {
    if (m_size == 0) {
      std::cout << "Error: no elements in container" << std::endl << std::endl;
      return true;
    } else {
      return false;
    }
  }

  struct ConstIterator {
    ConstIterator(const size_t index, const SuccessiveContainer& container)
        : m_index(index), m_cont(&container) {}

    explicit ConstIterator(const size_t size) : m_index(size) {}

    const T& get() const { return (*m_cont)[m_index]; }
    const T& operator*() const { return (*m_cont)[m_index]; }

    ConstIterator& operator++() {
      m_index++;
      return *this;
    }
    ConstIterator& operator++(int) {
      Iterator it(*this);
      ++(*this);
      return *this;
    }

    bool operator==(const ConstIterator& it) const {
      return m_index == it.m_index;
    }

    bool operator!=(const ConstIterator& it) const { return !(*this == it); }

   private:
    size_t m_index = 0;
    const SuccessiveContainer* m_cont = nullptr;
  };

  struct Iterator : ConstIterator {
    // Iterator(const size_t index, SuccessiveContainer& container)
    //     : m_index(index), m_cont(&container) {}

    // explicit Iterator(const size_t size) : m_index(size) {}

    T& get() { return (*m_cont)[m_index]; }
    T& operator*() { return (*m_cont)[m_index]; }

    // Iterator& operator++() {
    //   m_index++;
    //   return *this;
    // }
    // Iterator& operator++(int) {
    //   Iterator it(*this);
    //   ++(*this);
    //   return *this;
    // }

    bool operator==(const Iterator& it) { return m_index == it.m_index; }

    bool operator!=(const Iterator& it) { return !(*this == it); }

   private:
    size_t m_index = 0;
    SuccessiveContainer* m_cont = nullptr;
  };

  Iterator begin() { return Iterator{0, *this}; }

  Iterator end() { return Iterator{m_size}; }

  ConstIterator begin() const { return ConstIterator{0, *this}; }

  ConstIterator end() const { return ConstIterator{m_size}; }

  T& operator[](size_t i) { return m_region[i]; }

  T& operator[](size_t i) const { return m_region[i]; }

  size_t size() const { return m_size; }

  size_t capacity() const { return m_cap; }

 private:
  size_t m_size = 0;
  size_t m_cap = 0;
  std::shared_ptr<T[]> m_region = nullptr;
};