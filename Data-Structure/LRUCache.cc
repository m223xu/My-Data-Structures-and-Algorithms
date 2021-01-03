/* LRU cache using STL library */

#include <iostream>
#include <deque>
#include <unordered_map>

template<typename T>
class LRUCache
{
    size_t capacity;
    std::deque<T> dq;
    std::unordered_map<T, std::deque<T>::iterator> hm;
public:
    LRUCache(size_t);
    void refer(T);
    void display();
};

template<typename T>
LRUCache<T>::LRUCache(size_t capacity) : capacity(capacity)
{
}

template<typename T>
void LRUCache<T>::refer(T x)
{
    if (hm.find(x) != hm.end())     // the element is in the cache, move it to the front
    {
        dq.erase(hm[x]);
    }
    else if (dq.size() == capacity) // not in the cache, but cache is full, remove the LRU one
    {
        hm.erase(dq.back());
        dq.pop_back();
    }
    dq.emplace_front(x);
    hm[x] = dq.begin();
}

template<typename T>
void LRUCache<T>::display()
{
    for (auto& x : dq)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}
