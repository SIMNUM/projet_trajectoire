//
//  Test.cpp
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 07/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#include <iostream>
#include "geometrie.h"

int main(int argc, const char * argv[])
{
    
    std::cout << "DEMARAGE DU TEST\n";
    
    std::cout << "Test de géométrie.h\n";
    
    std::cout << "Test de la classe sommet\n";
    sommet A(1,2);
    sommet B(A);
    
    std::cout << sommet() << sommet(1) << sommet(1,2) << sommet(1,2,3) << B;
    return 0;
}
