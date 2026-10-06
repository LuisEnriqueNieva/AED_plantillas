#include <iostream>
#include <deque>
#include <vector>
using namespace std;

template<typename T, typename ContainerType=std::deque<T>>
class Deque {
public:
    Deque() = default;
    explicit Deque(ContainerType& container) : cnt(container) {}

    template <typename InputIterator>
    Deque(InputIterator start, InputIterator stop) {
        std::copy(start, stop, std::back_inserter(cnt));
    }

    [[nodiscard]] size_t size() const { return cnt.size(); }
    [[nodiscard]] bool empty() const { return cnt.empty(); }
    [[nodiscard]] T front() const { return cnt.front(); }
    [[nodiscard]] T back() const { return cnt.back(); }

    void push_front(T x) { cnt.push_front(x); }
    void push_back(T x) { cnt.push_back(x); }
    void pop_front() { cnt.pop_front(); }
    void pop_back() { cnt.pop_back(); }

    template <class... Args>
    void emplace_back(Args... args) { cnt.emplace_back(args...); }
    template <class... Args>
    void emplace_front(Args... args) { cnt.emplace_front(args...); }

    friend ostream& operator<<(ostream& os, Deque d) {
        for (auto it = d.cnt.begin(); it != d.cnt.end(); ++it) os << *it << " ";
        return os;
    }
private:
    ContainerType cnt;
};


int main() {


    return 0;
}