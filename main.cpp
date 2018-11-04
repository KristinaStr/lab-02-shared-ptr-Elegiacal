//
//  main.cpp
//  lab_32 (shared_ptr)
//
//  Created by Артём Песоцкий on 25/09/2018.
//  Copyright © 2018 Артём Песоцкий. All rights reserved.
//
#include "SharedPtr.hpp"

int main(int argc, const char * argv[])
{
    int temp = 1001;
    SharedPtr<int> hello(&temp);
    SharedPtr<int> bye = hello;
    std::cout << hello.use_count();   
}
