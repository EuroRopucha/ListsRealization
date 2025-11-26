#pragma once
#include <stdexcept>
#include <vector>
#include <algorithm> // std::sort
#include <utility>   // std::swap
using namespace std;

struct Link {
    int val;
    Link* next;
    Link(int _val = 0) : val(_val) {
        next = this;
    }
    Link(int _val, Link* _next) : val(_val), next(_next) {}
};

class HList {
    Link* head;
    Link* last;

public:
    HList() {
        head = new Link();
        last = head;
    }
    HList(const HList& other) {

        Link* tmp = other.head->next;

        head = new Link();
        last = head;

        while (tmp != other.head) {
            addlast(tmp->val);// добавляем элемент в копию
            tmp = tmp->next;
        }
    }
    Link* addafter(Link* p, int val) { //private
        Link* t = new Link(val, p->next);
        p->next = t;
        return t;
    }
    void addfirst(int val) {
        addafter(head, val);
    }
    void addlast(int val) {
        last = addafter(last, val);
    }

    void RemoveLast() {
        if (head == last) throw - 1;
        Link* tmp = head;
        while (tmp->next != last)
            tmp = tmp->next;
        delete last;
        tmp->next = head;
        last = tmp;
    }
    void Reverse() {
        HList cpy;
        Link* tmp = head->next;

        while (tmp != head) {
            cpy.addfirst(tmp->val);
            tmp = tmp->next;
        }
        swap(head, cpy.head);
        swap(last, cpy.last);
    }
    void RemoveAllSame(int val) {
        Link* curr = head->next;
        Link* prev = head;

        while (curr != head) {
            if (curr->val == val) {
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    void RemoveDuplicate() {
        if (head == last) throw - 1;
        Link* curr = head->next;

        while (curr != head) {
            Link* prev = curr;
            Link* tmp = curr->next;

            while (tmp != head) {
                if (tmp->val == curr->val) {
                    prev->next = tmp->next;
                    delete tmp;
                    tmp = prev->next;
                }
                else {
                    prev = tmp;
                    tmp = tmp->next;
                }
            }
            curr = curr->next;
        }
    }
    int Size() const {
        int cnt = 0;
        Link* curr = head->next;
        while (curr != head) {
            cnt++;
            curr = curr->next;
        }
        return cnt;
    }
    bool isEmpty() { return head == last; }



    void insertAt(size_t index, int val) {
        Link* prev = head;
        for (size_t i = 0; i < index; ++i) {
            if (prev->next == head) throw std::out_of_range("Index out of range");
            prev = prev->next;
        }
        if (prev == last) last = addafter(prev, val);
        else addafter(prev, val);
    }

    void removeAt(size_t index) {
        if (head == last) throw std::out_of_range("Empty list");
        Link* prev = head;
        for (size_t i = 0; i < index; ++i) {
            if (prev->next == head) throw std::out_of_range("Index out of range");
            prev = prev->next;
        }
        Link* target = prev->next;
        if (target == head) throw std::out_of_range("Index out of range");
        if (target == last) last = prev;
        prev->next = target->next;
        delete target;
    }

    Link* find(int val) const {
        for (Link* curr = head->next; curr != head; curr = curr->next) {
            if (curr->val == val) return curr;
        }
        return nullptr;
    }

    bool contains(int val) const {
        return find(val) != nullptr;
    }

    // преобразование в вектор
    std::vector<int> toVector() const {
        std::vector<int> result;
        for (Link* curr = head->next; curr != head; curr = curr->next) {
            result.push_back(curr->val);
        }
        return result;
    }

    // cортировка по возрастанию
    void sort() {
        std::vector<int> v = toVector();
        std::sort(v.begin(), v.end());
        clear();
        for (int x : v) addlast(x);
    }

    void merge(const HList& other) {
        for (Link* curr = other.head->next; curr != other.head; curr = curr->next) {
            addlast(curr->val);
        }
    }

    HList& operator=(HList other) {
        std::swap(head, other.head);
        std::swap(last, other.last);
        return *this;
    }

    void clear() {
        Link* curr = head->next;
        while (curr != head) {
            Link* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        head->next = head;
        last = head;
    }

    ~HList() {
        clear();
        delete head;
    }

};

