//
//  Utility.cpp
//  SFML Chess
//
//  Created by Andrew Xia on 4/16/21.
//  Copyright © 2021 Andy. All rights reserved.
//

#include "Utility.hpp"
#include "Data_structs.hpp"



char num_to_char(int input) {
    char c;
    switch(input) {
        case 0:
            c = 'a';
            break;
        case 1:
            c = 'b';
            break;
        case 2:
            c = 'c';
            break;
        case 3:
            c = 'd';
            break;
        case 4:
            c = 'e';
            break;
        case 5:
            c = 'f';
            break;
        case 6:
            c = 'g';
            break;
        case 7:
            c = 'h';
            break;
    }
    return c;
}
