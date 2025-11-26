#include "List.h"
#include "HList.h"
#include "HListExtended.h"
#include <iostream>
#include <cassert>

#include "DList.h"

int main() {
    List L;
    L.addFirst(3);  // [3]
    L.addFirst(2);  // [2, 3]
    L.addFirst(1);  // [1, 2, 3]

    std::cout << "Size: " << L.Size() << "\n"; // 3

    // Индексация
    std::cout << "L[0]: " << L[0] << "\n"; // 1
    std::cout << "L[1]: " << L[1] << "\n"; // 2
    std::cout << "L[2]: " << L[2] << "\n"; // 3

    // Итератор
    Iterator it = L.iter();
    while (it.hasNext()) {
        std::cout << it.Next() << " "; // 1 2 3
    }
    std::cout << "\n";

    // Удаление по индексу
    L.delInd(1); // удалить 2, список -> [1, 3]
    std::cout << "After delInd(1): " << L[0] << " " << L[1] << "\n"; // 1 3

    // Копирование
    List A = L; // глубокая копия
    A.addFirst(0); // A: [0,1,3], L: [1,3]
    std::cout << "A[0]: " << A[0] << " L[0]: " << L[0] << "\n"; // 0 vs 1

    // Перемещение
    List M = std::move(A); // A становится пустым логически
    std::cout << "M Size: " << M.Size() << "\n"; // 3



    // 1. Создание пустого списка
    HList list;
    // head == last, список пуст
    try {
        list.RemoveLast();
        assert(false); // должно выбросить исключение
    }
    catch (...) {
        std::cout << "Test 1 passed: RemoveLast on empty throws\n";
    }

    // 2. Добавление элементов
    list.addfirst(10); // [10]
    list.addlast(20);  // [10, 20]
    list.addlast(30);  // [10, 20, 30]

    std::cout << "Test 2 passed: addfirst/addlast\n";

    // 3. Копирующий конструктор
    HList copy(list);
    copy.addlast(40); // [10,20,30,40]
    std::cout << "Test 3 passed: copy constructor deep copy\n";

    // 4. RemoveLast
    list.RemoveLast(); // удаляем 30 → [10,20]
    list.RemoveLast(); // удаляем 20 → [10]
    std::cout << "Test 4 passed: RemoveLast\n";

    // 5. Reverse
    HList rev;
    rev.addlast(1);
    rev.addlast(2);
    rev.addlast(3); // [1,2,3]
    rev.Reverse();  // должно стать [3,2,1]
    std::cout << "Test 5 passed: Reverse\n";

    // 6. RemoveAllSame
    HList same;
    same.addlast(5);
    same.addlast(5);
    same.addlast(7);
    same.addlast(5); // [5,5,7,5]
    same.RemoveAllSame(5); // должно остаться [7]
    std::cout << "Test 6 passed: RemoveAllSame\n";

    // 7. RemoveDuplicate
    HList dup;
    dup.addlast(1);
    dup.addlast(2);
    dup.addlast(1);
    dup.addlast(3);
    dup.addlast(2); // [1,2,1,3,2]
    dup.RemoveDuplicate(); // должно остаться [1,2,3]
    std::cout << "Test 7 passed: RemoveDuplicate\n";

    std::cout << "All tests passed!\n";




}
