#include <iostream>
#include <deque>
using namespace std;

// Data Structure TDA

template<typename T, typename ContainerType=std::deque<T>>
class Stack {
public:
    Stack() = default;
    T top() { return cnt.back();}
    bool empty() { return cnt.empty();}
    size_t size() { return cnt.size();}
    void push(T x) { cnt.push_back(x);}
    void pop() { cnt.pop_back();}

    friend ostream& operator<<(ostream& os, Stack s) {
        for (auto it = s.cnt.rbegin(); it != s.cnt.rend(); ++it) {
            os << *it;
            if (it == s.cnt.rbegin()) os << " <- top";
            os << endl;
        }
        return os;
    }

    private:
    ContainerType cnt;
};


int main() {

    Stack<int> s1;
    s1.push(6);
    s1.push(7);
    s1.push(8);
    s1.push(9);
    s1.push(10);
    s1.pop();
    cout << s1;

    return 0;
}