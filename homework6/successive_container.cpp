#include <iostream>

template <typename T>
class SuccessiveContainer {
 public:
  SuccessiveContainer() : m_size{0}, m_cap{0}, m_region{nullptr} {}

  SuccessiveContainer(const SuccessiveContainer& other)
      : SuccessiveContainer{other.m_region()} {
    std::cout << "SuccessiveContainer const SuccessiveContainer&" << std::endl;
  }

  SuccessiveContainer(SuccessiveContainer&& other) {
    m_cap = other.m_cap;
    m_size = other.m_size;
    m_region = other.m_region;

    other.m_cap = 0;
    other.m_size = 0;
    other.m_region = nullptr;
  }

  ~SuccessiveContainer() {
    delete[] m_region;
    std::cout << "~SuccessiveContainer" << std::endl;
  }

  SuccessiveContainer& operator=(const SuccessiveContainer& rhs) {
    std::cout << "SuccessiveContainer::operator=" << std::endl;
    SuccessiveContainer temp{rhs};

    T* data = m_region;
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

  SuccessiveContainer& operator=(SuccessiveContainer&& rhs) {
    std::cout << "&&SuccessiveContainer::operator=" << std::endl;
    SuccessiveContainer temp{std::move(rhs)};
    return *this = temp;
  }

  bool push_back(const T& val) {
    if (m_size < m_cap) {
      m_region[m_size] = std::move(val);
      ++m_size;
    } else {
      T* new_region = new T[((m_size + 1) * 2)];
      m_cap = std::move(((m_size + 1) * 2));

      for (size_t i = 0; i < m_size; ++i) {
        new_region[i] = m_region[i];
      }

      new_region[m_size] = std::move(val);
      delete[] m_region;
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
      T* new_region = new T[((m_size + 1) * 2)];
      m_cap = std::move(((m_size + 1) * 2));

      for (size_t i = 0; i < pos; ++i) {
        new_region[i] = m_region[i];
      }

      for (size_t i = m_size; i != pos; --i) {
        new_region[i] = m_region[i - 1];
      }

      new_region[pos] = std::move(val);

      delete[] m_region;
      m_region = std::move(new_region);
      ++m_size;
    }
    return true;
  }

  bool erase(const size_t pos) {
    if (pos >= m_size) {
      return false;
    }

    for (size_t i = pos - 1; i < m_size + 1; ++i) {
      m_region[i] = m_region[i + 1];
    }
    --m_size;

    return true;
  }

  bool empty() {
    if (m_size == 0) {
      std::cout << "Error: no elements in container" << std::endl << std::endl;
      return true;
    } else {
      return false;
    }
  }

  struct Iterator {
    Iterator(const size_t index, SuccessiveContainer& container)
        : m_index(index), m_cont(&container) {}

    explicit Iterator(const size_t size) : m_index(size) {}

    T& get() { return (*m_cont)[m_index]; }
    T& operator*() { return (*m_cont)[m_index]; }

    Iterator& operator++() {
      m_index++;
      return *this;
    }
    Iterator& operator++(int) {
      Iterator it(*this);
      ++(*this);
      return *this;
    }

    bool operator==(const Iterator& it) const { return m_index == it.m_index; }

    bool operator!=(const Iterator& it) const { return !(*this == it); }

   private:
    size_t m_index = 0;
    SuccessiveContainer* m_cont = nullptr;
  };

  Iterator begin() { return Iterator{0, *this}; }

  Iterator end() { return Iterator{m_size}; }

  T& operator[](size_t i) { return m_region[i]; }

  size_t size() const { return m_size; }

  size_t capacity() const { return m_cap; }

 private:
  size_t m_size;
  size_t m_cap;
  T* m_region{};
};

template <typename T>
void print_container(SuccessiveContainer<T>& container) {
  std::cout << "Elements: ";
  for (auto i = 0; i < container.size(); ++i) {
    std::cout << container[i] << ' ';
  }
  std::cout << std::endl;

  std::cout << "Size: " << container.size() << std::endl;
  std::cout << std::endl << std::endl;
}

void test_container() {
  SuccessiveContainer<int> int_container;

  if (!int_container.empty()) {
    std::cout << std::endl << "Elements from iterator: ";
    for (auto iter = int_container.begin(); iter != int_container.end();
         ++iter) {
      std::cout << iter.get() << ' ';
    }
    std::cout << std::endl;
  }

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

  std::cout << std::endl << "Elements from iterator: ";
  for (auto iter = int_container.begin(); iter != int_container.end(); iter++) {
    std::cout << iter.get() << ' ';
  }
  std::cout << std::endl;

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

  std::cout << std::endl << "Elements from iterator: ";

  for (auto iter = int_container.begin(); iter != int_container.end(); ++iter) {
    std::cout << *iter << ' ';
  }

  std::cout << std::endl;

  print_container(int_container);
}

int main() {
  test_container();

  return 0;
}