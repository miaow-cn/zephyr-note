#include "00_ref.h"
#include <zephyr/logging/log.h>
#include <iostream>

LOG_MODULE_REGISTER(ref, LOG_LEVEL_INF);

static void increment(int& value)
{
    value++;
    std::cout << "Value of b: " << value << std::endl;
}

int ref_entry()
{
    LOG_INF("Starting Reference example...");

    int a = 5;
    int b = 9;
    int& ref = a;

    ref = b;

    increment(ref);

    std::cout << "Value of a: " << a << std::endl;
    std::cout << "Value of ref: " << ref << std::endl;
    std::cout << std::endl;
    return 0;
}