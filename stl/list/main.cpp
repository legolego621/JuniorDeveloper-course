#include <iostream>
/* demonstration the realization list v1 */

#include "list.h"

int main(void)
{
    List list1, list2(10, -1), list3(10);
    std::cout << "List1: " << list1 << std::endl;
    std::cout << "List2: " << list2 << std::endl;
    std::cout << "List3: " << list3 << std::endl;

    std::cout << std::endl << "Function push_back: list1: " << std::endl;
    for(std::size_t i = 0; i < 10; ++i)
        list1.push_back(i);
    std::cout << "List1, result: " << list1 << std::endl;

    std::cout << std::endl << "Function pop_back, count eihgt: list2: " << std::endl;
    for(std::size_t i = 0; i < 8; ++i)
        list2.pop_back();
    std::cout << "List2, result: " << list2 << std::endl;

    std::cout << std::endl << "Function constructor copy in list4, copy list2: " << std::endl;
    List list4(list1);
    std::cout << "List4, result: " << list4 << std::endl;

    std::cout << std::endl << "Function copy: list3 = list4" << std::endl;
    list3 = list4;
    std::cout << "List4, result: " << list3 << std::endl;

    std::cout << std::endl << "Function ==: list2 == list4" << std::endl;
    if(list2 == list4)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
    std::cout << "List2 and list4: " << list2 << std::endl;
    std::cout << list4 << std::endl;

    std::cout << std::endl << "Function size: list4" << std::endl;
    std::cout << "List4: " << list4 << std::endl;
    std::cout << "size: " << list4.size() << std::endl;

    list4.push_back(-100);
    list4.push_back(1000);
    list4.push_back(-100);
    list4.push_back(-10);
    list4.push_back(-1);

    std::cout << std::endl << "Function max_size: list4" << std::endl;
    std::cout << "List4: " << list4 << std::endl;
    std::cout << "max_size: " << list4.max_size() << std::endl;
    std::cout << "front: " << list4.front() << std::endl;
    std::cout << "back: " << list4.back() << std::endl;


    std::cout << std::endl << "Function clear: list4" << std::endl;
    std::cout << "List4: " << list4 << std::endl;
    list4.clear();
    std::cout << "List4: " << list4 << std::endl;
    list4 = list1;

    List list5(3, 1);

    std::cout << std::endl << "Function swap: list4 and list5" << std::endl;
    std::cout << "list4: " << list4 << std::endl;
    std::cout << "list5: " << list5 << std::endl;
    std::cout << "swap" << std::endl;
    list4.swap(list5);
    std::cout << "list4: " << list4 << std::endl;
    std::cout << "list5: " << list5 << std::endl;

    std::cout << std::endl << "Function insert: list4" << std::endl;
    std::cout << "list4: " << list4 << std::endl;
    std::cout << "pos 2, value 40: " << std::endl;
    list4.insert(2, 40);
    std::cout << "list4: " << list4 << std::endl;

    std::cout << "Function erase: list 4" << std::endl;
    list4.insert(2, 41);
    std::cout << "list4: " << list4 << std::endl;
    std::cout << "Erase in pos 2" << std::endl;
    list4.erase(2);
    std::cout << "list4: " << list4 << std::endl;

    return 0;
}
