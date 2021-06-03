#include <iostream>
#include <string>
#include <cstring>  // or include string.h
#include <cassert>
#include <vector>

using namespace std;

template <typename T>
class MyMap {

    class mapNode {
    public:
        uint32_t key;
        T value;
        mapNode* next;
    };

public:
    MyMap():head(nullptr),
    size(0)
    {

    };
    ~MyMap(){
        while (head)
        {
            mapNode* tmp = head->next;
            delete head;
            head = tmp;
        }
        
    }
    void set (uint32_t key, const T& v){
        if(!head) // new map
        {
            head = new mapNode();
            head->key = key;
            head->value = v;
            size++;
        }else { //insert 
            mapNode* tmp = head;
            mapNode* pre = nullptr;
            while (tmp)
            {
                if(tmp->key == key) //exist, just change value
                {
                    tmp->value = v;
                    return;
                }else if (tmp->key > key) // insert at front of tmp
                {
                    mapNode* newNode = new mapNode();
                    newNode -> key = key;
                    newNode -> value = v; 
                    newNode->next = tmp;
                    if(pre)
                    {
                        pre-> next = newNode; // header is no keep
                    }else
                    {
                        head = newNode;  // newNode is header now
                    }
                    size++;
                    return;
                }else if(!(tmp->next) ||( tmp->next && tmp->next->key > key)) // insert node after tmp
                {
                    mapNode* newNode = new mapNode();
                    newNode -> key = key;
                    newNode -> value = v; 
                    newNode->next = tmp->next;
                    tmp->next = newNode;
                    size++;
                    return;

                }else  // next loop
                {
                    pre = tmp;
                    tmp = tmp->next;
                }
            }
            
        }

    };

    const T* get(uint32_t key) {
        mapNode* tmp = head;
        while (tmp)
        {
            if(tmp->key == key)
                return &(tmp->value);
            tmp = tmp->next;
        }
        return nullptr;
    };
    void remove(uint32_t key) {
        mapNode* tmp = head;
        mapNode* pre = nullptr;
        while (tmp)
        {
            if(tmp->key == key)
            {
                if(pre)
                {
                    pre->next = tmp->next;
                }

                delete tmp;
                size--;
                return;
            }else if (tmp->key > key)
            {
                return;
            }
            pre = tmp;
            tmp = tmp->next;
        }
        
    };

    int getSize()
    {
        return this->size;
    }
    bool isEmpty()
    {
        return (size == 0);
    }

private:
    mapNode* head;
    int size;
    
};


void testMyMap()
{
    MyMap<string> myMap;
    myMap.set(3, "3rd");
    myMap.set(5, "fifth");
    myMap.set(1, "first");
    myMap.set(4,"fourth");
    myMap.set(2, "second");
    myMap.set(4,"fourth,with new data");
    


    cout << "find 4nd:" << *(myMap.get(4)) << endl;
    myMap.remove(7);
    myMap.remove(4);

    cout << "find 3nd:" << *(myMap.get(3)) << endl;
    myMap.get(4);
    cout << "find 2nd:" << myMap.get(4) << endl;
}
