#include <iostream>
#include "date_counter.h"

using namespace DateCounter;

int main(void)
{
    SimpleDate d;
    SimpleDate d1(2019, 12, 21);

    std::cout << d << std::endl;
    std::cout << d1 - d << std::endl;

    return 0;
}

