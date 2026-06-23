#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class LRUCache {
public:
    list<int> order;
    map<int,pair<int,list<int>::iterator>> cacheMap;
    int _capacity;
    LRUCache(int capacity) {
        order.clear();
        cacheMap.clear();
        _capacity = capacity;
    }
    
    void updateDS(int key){
        auto iter = cacheMap[key].second;
        order.erase(iter);
        order.push_front(key);
        cacheMap[key].second = order.begin(); 
    }

    int get(int key) {
        if(cacheMap.find(key) != cacheMap.end()){
            updateDS(key);
            return cacheMap[key].first;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(cacheMap.find(key) != cacheMap.end()){
            cacheMap[key].first = value;
            updateDS(key);
        }
        else{
            if(cacheMap.size() == _capacity){
                int delkey = order.back();
                order.pop_back();
                cacheMap.erase(delkey);
            }
            order.push_front(key);
        }
        cacheMap[key] = make_pair(value,order.begin());
    }
};

class LFUCache {
public:
    map<int,list<int>> freqListMap;
    map<int,pair<int,int>> cacheMap;
    map<int,list<int>::iterator> keyIterMap;
    int lfu=0;
    int _capacity;
    LFUCache(int capacity) {
        _capacity = capacity;
        lfu = 0;
        cacheMap.clear();
        freqListMap.clear();
        keyIterMap.clear();
    }

    void updateDS(int key){
        int freq = cacheMap[key].second;
        auto it = keyIterMap[key];
        cacheMap[key].second++;
        freqListMap[freq].erase(it);
        freqListMap[freq+1].push_back(key);
        keyIterMap[key] = --freqListMap[freq+1].end();
        if(freqListMap[lfu].empty()){
            lfu++;
        }
    }
    
    int get(int key) {
        if(cacheMap.find(key) != cacheMap.end()){
            updateDS(key);
            return cacheMap[key].first;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(!_capacity) return;
        if(cacheMap.find(key) != cacheMap.end()){
            updateDS(key);
            cacheMap[key].first = value;
            return;
        }else{
            if(cacheMap.size() == _capacity){
                int delkey = freqListMap[lfu].front();
                freqListMap[lfu].pop_front();
                cacheMap.erase(delkey);
                keyIterMap.erase(delkey);
            }
            lfu = 1;
        }
        freqListMap[lfu].push_back(key);
        cacheMap[key] = make_pair(value,lfu);
        keyIterMap[key] = --freqListMap[lfu].end();
    }
};

int main(){

    LRUCache lruCache(2);
    lruCache.put(1,1);
    lruCache.put(2,2);
    lruCache.get(1);
    lruCache.put(3,3);
    lruCache.get(2);
    lruCache.put(4,4);
    lruCache.get(4);
    return 0;
}