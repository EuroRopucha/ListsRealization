#pragma once
#include <utility>  

struct Link1 {
    int val;
    Link1* next;
    Link1(int _val = 0, Link1* _next = nullptr) : val(_val), next(_next) {}
};

//Хранит позицию. указатель tmp на текущий узел
class Iterator {
    Link1* tmp;

public:
    Iterator(Link1* _tmp) : tmp(_tmp) {}

    bool hasNext() {
        return tmp != nullptr;
    }
    int Next() {
        if (!hasNext()) throw - 1;
        int curr = tmp->val;
        tmp = tmp->next;
        return curr;
    }

};

class List {
    Link1* fp;
public:
    List() { fp = nullptr; }

    void addFirst(const int value) {
        Link1* tmp = new Link1(value, fp);
        fp = tmp;
    }
    void delFirst() {
        if (fp == nullptr)
            return;
        Link1* tmp;
        tmp = fp;
        fp = fp->next;
        delete tmp;
    }
    void Clean() {
        while (fp != nullptr)
            delFirst();
    }
    ~List(){
        Clean();
    }

    List(const List& other) {
        Link1* tmp = other.fp;
        
        if (tmp == nullptr) {
            fp = nullptr;
            return;
        }
        fp = new Link1(tmp->val);

        Link1* tmp2 = fp;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
            tmp2->next = new Link1(tmp->val);
            tmp2 = tmp2->next;
            
        }
    }
    List& operator=(List other) noexcept {
        std::swap(fp, other.fp);
        return *this;
    }

    int& operator[](const int ind) {
        if (ind < 0) throw - 1;
        Link1* tmp = fp;
        for (int i = 0; i < ind; i++)
        {
            if (tmp == nullptr) throw - 1;
            tmp = tmp->next;
        }
        if (tmp == nullptr) throw - 1;
        return tmp->val;
    }

    int Size() {
        int cnt = 0;
        Link1* tmp = fp;
        while (tmp != nullptr) {
            cnt++;
            tmp = tmp->next;
        }
        return cnt;
    }

    Iterator iter() { return Iterator(fp); };

    void delInd(int ind) {
        if (fp==nullptr) throw - 1;
        if (ind == 0) {
            delFirst();
            return;
        }
        Link1* tmp = fp;
        while (ind > 1) {
            if (tmp == nullptr) throw - 1;
            tmp = tmp->next;
            ind--;
        }

        Link1* tmp2 = tmp->next;
        tmp->next = tmp2->next;
        delete tmp2;
    }
    
};








/*

#include <stdexcept>
#include <utility>  // std::swap
#include <cstddef>  // size_t

struct Link1 {
    int val;
    Link1* next;
    Link1(int _val = 0, Link1* _next = nullptr) : val(_val), next(_next) {}
};

class Iterator {
    Link1* tmp;

public:
    explicit Iterator(Link1* _tmp) : tmp(_tmp) {}

    bool hasNext() const {
        return tmp != nullptr;
    }

    int Next() {
        if (!hasNext()) throw std::out_of_range("Iterator: no next element");
        int curr = tmp->val;
        tmp = tmp->next;
        return curr;
    }
};

class List {
    Link1* fp;

    // Вспомогательная функция для глубокого копирования
    static Link1* copyNodes(Link1* head) {
        if (!head) return nullptr;
        Link1* newHead = new Link1(head->val);
        Link1* tail = newHead;
        Link1* curr = head->next;
        while (curr) {
            tail->next = new Link1(curr->val);
            tail = tail->next;
            curr = curr->next;
        }
        return newHead;
    }

public:
    // Конструкторы/деструкторы
    List() noexcept : fp(nullptr) {}

    ~List() noexcept {
        Clean();
    }

    List(const List& other) : fp(copyNodes(other.fp)) {}

    List(List&& other) noexcept : fp(other.fp) {
        other.fp = nullptr;
    }

    List& operator=(List other) noexcept {
        // copy-and-swap идиома: безопасно, исключения не протекают
        std::swap(fp, other.fp);
        return *this;
    }

    // Операции
    void addFirst(const int value) {
        Link1* tmp = new Link1(value, fp);
        fp = tmp;
    }

    void delFirst() noexcept {
        if (!fp) return;
        Link1* tmp = fp;
        fp = fp->next;
        delete tmp;
    }

    void Clean() noexcept {
        while (fp) delFirst();
    }

    // Индексация: O(n)
    int& operator[](const size_t ind) {
        Link1* tmp = fp;
        for (size_t i = 0; i < ind; ++i) {
            if (!tmp) throw std::out_of_range("List::operator[]: index out of range");
            tmp = tmp->next;
        }
        if (!tmp) throw std::out_of_range("List::operator[]: index out of range");
        return tmp->val;
    }

    const int& operator[](const size_t ind) const {
        Link1* tmp = fp;
        for (size_t i = 0; i < ind; ++i) {
            if (!tmp) throw std::out_of_range("List::operator[]: index out of range");
            tmp = tmp->next;
        }
        if (!tmp) throw std::out_of_range("List::operator[]: index out of range");
        return tmp->val;
    }

    size_t Size() const noexcept {
        size_t cnt = 0;
        for (Link1* tmp = fp; tmp; tmp = tmp->next) ++cnt;
        return cnt;
    }

    Iterator iter() const { return Iterator(fp); }

    // Удаление по индексу: O(n)
    void delInd(size_t ind) {
        if (!fp) throw std::out_of_range("List::delInd: list is empty");
        if (ind == 0) { delFirst(); return; }

        Link1* prev = fp;
        // Идем к узлу перед удаляемым
        for (size_t i = 0; i + 1 < ind; ++i) {
            if (!prev->next) throw std::out_of_range("List::delInd: index out of range");
            prev = prev->next;
        }
        Link1* target = prev->next;
        if (!target) throw std::out_of_range("List::delInd: index out of range");
        prev->next = target->next;
        delete target;
    }
};


*/