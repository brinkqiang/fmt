
#include "dmformat.h"
#include "dmtime.h"
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include "stuple.hpp"

void ttfff(STuple<>* aa)
{
    aa->print();
}

int main()
{
    STuple<std::string, int, std::string, int> stp("{}-{}-{}", 3, "hello", 1);
    STuple<std::string, std::string, std::string> stp2("{}-{}", "a", "b");
    STuple<std::string, int, std::string, int, double> stp3("{}-{}-{}-{}", 3, "hello", 1, 2.0);

    size_t t1 = sizeof(stp);
    size_t t2 = sizeof(stp2);
    size_t t3 = sizeof(stp3);

    //std::cout << get<0>(stp) << " " << typeid(get<0>(stp)).name() << std::endl;
    //std::cout << get<1>(stp) << " " << typeid(get<1>(stp)).name() << std::endl;
    //std::cout << get<2>(stp) << " " << typeid(get<2>(stp)).name() << std::endl;
    //std::cout << ((STuple<std::string, double> &)stp).value << std::endl;

    //stp.print();
    //stp.print();

    ttfff(&stp);
    ttfff(&stp2);
    ttfff(&stp3);

    std::cout << "Hello World!\n";
}