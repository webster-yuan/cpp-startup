#include<iostream>
#include<list>//双向链表容器
#include<unordered_map>
using namespace std;
//splice() 函数的功能可以总结如下：
//1. splice(iterator position, list& x)：将 x 中的所有元素移动到当前 list 的 position 之前。
//2. splice(iterator position, list& x, iterator i)：将 x 中迭代器 i 指向的元素移动到当前 list 的 position 之前。
//3. splice(iterator position, list& x, iterator first, iterator last)：将 x 中范围[first, last) 内的所有元素移动到当前 list 的 position 之前。
//这些操作可以在 O(1) 时间复杂度内完成，因为 std::list 是双向链表，只需要调整节点的指针即可实现元素的移动，而不需要像其他容器一样进行数据的复制。
//这使得 splice() 操作非常高效，特别适合用于需要频繁移动元素的场景。
class LRUCache 
{
private:
    size_t _cap;
    list<pair<int, int>> _LRUList;//<key,val>
    typedef list<pair<int, int>>::iterator iterator;//链表节点迭代器很方便
    unordered_map<int, iterator> hashMap;//<key,iterator>
public:
    LRUCache(int capacity) 
        :_cap(capacity)
    {}

    int get(int key) 
    {
        auto ret = hashMap.find(key);
        if (ret != hashMap.end())
        {
            iterator it = ret->second;
            _LRUList.splice(_LRUList.begin(),_LRUList,it);
            return it->second;
        }
        else
            return -1;
    }

    void put(int key, int value) 
    {
        auto ret = hashMap.find(key);
        if (ret != hashMap.end())
        {
            //需要将值进行更新,然后移动到链表的首部
            auto it = ret->second;
            it->second = value;
            _LRUList.splice(_LRUList.begin(),_LRUList,it);
        }
        else
        {
            //新增节点,一般容器是考虑是否扩容,但是LRU就是将链表尾部淘汰
            if (_cap == _LRUList.size())
            {
                pair<int, int> back = _LRUList.back();
                _LRUList.pop_back();
                hashMap.erase(back.first);
            }
            //放在链表头部位置
            _LRUList.push_front({key,value});
            hashMap[key] = _LRUList.begin();
        }
    }
};