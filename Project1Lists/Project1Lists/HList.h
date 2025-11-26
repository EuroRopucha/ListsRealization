/*

#pragma once
#include<utility>
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
    HList(const HList& other) {
        
        Link* tmp = other.head->next;

        head = new Link();
        last = head;

        while (tmp != other.head) {
            addlast(tmp->val);// добавляем элемент в копию
            tmp = tmp->next;
        }
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
        if (head == last) throw -1;
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


    ~HList() {
        Link* curr = head->next;
        while (curr != head) {
            Link* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        delete head;
    }

};
*/




/*

#pragma once
#include <utility>
#include <stdexcept>
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

    void sort() {
    if (head == last) return; // пустой список

    HList sorted; // временный отсортированный список

    Link* curr = head->next;
    while (curr != head) {
        Link* next = curr->next; // сохраним следующий узел

        // вставляем curr в правильное место в sorted
        Link* prev = sorted.head;
        Link* tmp = sorted.head->next;
        while (tmp != sorted.head && tmp->val < curr->val) {
            prev = tmp;
            tmp = tmp->next;
        }

        // вставка узла curr между prev и tmp
        curr->next = tmp;
        prev->next = curr;

        // обновляем last в sorted
        if (tmp == sorted.head) sorted.last = curr;

        curr = next; // переходим к следующему узлу
    }

    // меняем местами списки
    swap(head, sorted.head);
    swap(last, sorted.last);
}







    // --- вспомогательные функции для merge sort ---
    Link* mergeLists(Link* a, Link* b, Link* stop) {
        Link dummy(0, stop);
        Link* tail = &dummy;
        while (a != stop && b != stop) {
            if (a->val <= b->val) {
                tail->next = a;
                a = a->next;
            } else {
                tail->next = b;
                b = b->next;
            }
            tail = tail->next;
        }
        tail->next = (a != stop) ? a : b;
        return dummy.next;
    }

    Link* split(Link* start, Link* stop) {
        Link* slow = start;
        Link* fast = start->next;
        while (fast != stop && fast->next != stop) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Link* mid = slow->next;
        slow->next = stop; // разрываем список
        return mid;
    }

    Link* mergeSort(Link* start, Link* stop) {
        if (start == stop || start->next == stop) return start;
        Link* mid = split(start, stop);
        Link* left = mergeSort(start, stop);
        Link* right = mergeSort(mid, stop);
        return mergeLists(left, right, stop);
    }

public:
    HList() {
        head = new Link();
        last = head;
    }

    Link* addafter(Link* p, int val) {
        Link* t = new Link(val, p->next);
        p->next = t;
        return t;
    }
    void addfirst(int val) { addafter(head, val); }
    void addlast(int val) { last = addafter(last, val); }

    // --- сортировка слиянием ---
    void sort() {
        if (head == last) return; // пустой список
        head->next = mergeSort(head->next, head);
        // обновляем last
        Link* tmp = head;
        while (tmp->next != head) tmp = tmp->next;
        last = tmp;
    }

    // --- слияние двух отсортированных списков ---
    void merge(const HList& other) {
        // просто добавляем элементы другого списка
        Link* curr = other.head->next;
        while (curr != other.head) {
            addlast(curr->val);
            curr = curr->next;
        }
        // сортируем результат
        sort();
    }

    // --- удаление всех чётных элементов ---
    void removeEven() {
        Link* prev = head;
        Link* curr = head->next;
        while (curr != head) {
            if (curr->val % 2 == 0) {
                prev->next = curr->next;
                if (curr == last) last = prev;
                delete curr;
                curr = prev->next;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    // --- разделение списка на два ---
    pair<HList, HList> splitPosNeg() const {
        HList pos, neg;
        Link* curr = head->next;
        while (curr != head) {
            if (curr->val >= 0) pos.addlast(curr->val);
            else neg.addlast(curr->val);
            curr = curr->next;
        }
        return {pos, neg};
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

    bool isEmpty() const { return head == last; }

    ~HList() {
        Link* curr = head->next;
        while (curr != head) {
            Link* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        delete head;
    }
};


*/