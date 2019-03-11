//
// Created by huxy on 07/03/19.
//

#include <iostream>
#include "Printer.h"

Printer::~Printer()
{
    std::lock_guard<std::mutex> guard(cout_mtx);
    std::cout.clear();
    std::cout << this->str();
}
std::mutex Printer::cout_mtx{};