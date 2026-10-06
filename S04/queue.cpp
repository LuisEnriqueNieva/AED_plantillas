#include <iostream>
#include <deque>
#include <vector>
using namespace std;

template<typename T, typename ContainerType=std::deque<T>>
class Queue {
public:
    Queue() = default;
    explicit Queue(ContainerType& container) : cnt(container) {}

    template <typename InputIterator>
    Queue(InputIterator start, InputIterator stop) {
        std::copy(start, stop, std::back_inserter(cnt));
    }

    [[nodiscard]] size_t size() const { return cnt.size(); }
    [[nodiscard]] bool empty() const { return cnt.empty(); }
    [[nodiscard]] T back() const { return cnt.back(); }
    [[nodiscard]] T front() const { return cnt.front(); }

    void enqueue(T x) { cnt.push_back(x); }
    void dequeue() { cnt.pop_front(); }

    template <class... Args>
    void emplace(Args... args) {
        cnt.emplace_back(args...);
    }

    friend ostream& operator<<(ostream& os, Queue q) {
        for (auto it = q.cnt.begin(); it != q.cnt.end(); ++it) {
            os << *it << " ";
        }
        return os;
    }

private:
    ContainerType cnt;
};


int main() {
    Queue<int> q1;
    Queue q2(q1);
    std::vector v1={1,2,3};
    Queue<int> q3(v1.begin(), v1.end());

    q3.enqueue(4);
    q3.enqueue(5);
    q3.enqueue(6);
    q3.dequeue();

    cout << q3;

    return 0;
}