//
//  main.cpp
//  lab_32 (shared_ptr)
//
//  Created by Артём Песоцкий on 25/09/2018.
//  Copyright © 2018 Артём Песоцкий. All rights reserved.
//
#include "SharedPtr.hpp"

int main()
{
    SharedPtr<double> temp1;
    SharedPtr<double> temp2(temp1);
//     SharedPtr<double> temp3 = temp1;
    std::cout << temp1.use_count() << std::endl;
    std::cout << temp2.use_count() << std::endl;
    temp2.swap(temp1);
}
