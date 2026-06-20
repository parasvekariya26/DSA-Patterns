#include <iostream>
#include <set>
using namespace std;

class MedianFinder {
public:
    multiset<int> ms1, ms2;
    MedianFinder() {
        ms1.clear();
        ms2.clear();
    }
    void addNum(int num) {
        if (!ms1.empty())
            if (*ms1.rbegin() >= num) {
                ms1.insert(num);
                return;
            }
        if (!ms2.empty())
            if (*ms2.begin() <= num) {
                ms2.insert(num);
                return;
            }
        ms1.insert(num);
    }
    void rebalnce(multiset<int> &ms1, multiset<int> &ms2) {
        while (ms1.size() >= ms2.size() + 2) {
            ms2.insert(*ms1.rbegin());
            ms1.erase(ms1.find(*ms1.rbegin()));
        }
        while (ms2.size() > ms1.size()) {
            ms1.insert(*ms2.begin());
            ms2.erase(ms2.find(*ms2.begin()));
        }
    }

    double findMedian() {
        rebalnce(ms1, ms2);
        if ((ms1.size() + ms2.size()) % 2 == 0)
            return (double)(*ms1.rbegin() + *ms2.begin()) / 2;
        else
            return (double)(*ms1.rbegin());
    }
};

int main() {
    MedianFinder mf;

    //median static test case
    // mf.addNum(6);
    // mf.addNum(10);
    // mf.addNum(2);
    // mf.addNum(6);
    // mf.addNum(5);
    // mf.addNum(0);
    // mf.addNum(6);
    // mf.addNum(3);
    // mf.addNum(1);
    // mf.addNum(0);
    // mf.addNum(0);
    return 0;
}