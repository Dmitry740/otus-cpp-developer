#include <iostream>

template <typename T>
class ListContainer {
  struct Node {
    Node* next;
    T data;
  };

 public:
  ListContainer() : m_size{0}, m_first{nullptr}, m_last{nullptr} {}

  ListContainer(const ListContainer& other)
      : ListContainer{other.m_first()}, ListContainer{other.m_last()} {
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
    new_node->next = nullptr;
    new_node->data = value;

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
      new_node->next = first;
      new_node->data = std::move(value);
      m_first = std::move(new_node);
    } else {
      size_t i = 0;
      while (i != (pos - 1)) {
        first = first->next;
        ++i;
      }
      Node* prev = std::move(first);
      first = first->next;

      Node* new_node = new Node{};
      new_node->next = first;
      new_node->data = std::move(value);
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
      while (i != (pos - 1)) {
        first = first->next;
        ++i;
      }
      Node* prev = std::move(first);
      Node* del = first->next;
      first = del->next;
      prev->next = std::move(first);

      delete[] del;

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

  bool empty() {
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

  Iterator begin() { return m_first; }

  Iterator end() { return {nullptr}; }

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
  Node* m_first;
  Node* m_last;
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

  if (!int_container.empty()) {
    for (auto iter = int_container.begin(); iter != int_container.end();
         ++iter) {
      std::cout << iter.get() << ' ';
    }
  }

  std::cout << std::endl;

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

  std::cout << "Elements from iterator: ";
  for (auto iter = int_container.begin(); iter != int_container.end(); ++iter) {
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

  std::cout << "Elements from iterator: ";
  for (auto iter = int_container.begin(); iter != int_container.end(); iter++) {
    std::cout << *iter << ' ';
  }

  std::cout << std::endl;

  print_container(int_container);
}

int main() { test_container(); }