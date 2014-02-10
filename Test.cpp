//
//  Test.cpp
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 07/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#include <iostream>
#include "scene.h"


int main(int argc, const char * argv[])
{
    
    std::cout << "DEMARAGE DU TEST\n";
    
    std::cout << "Test de géométrie.h\n";
    
    std::cout << "Test de la classe vecteur\n";
    vecteur A(1,2);
    vecteur B(A);
    
    std::cout << vecteur() << vecteur(1) << vecteur(1,2) << vecteur(1,2,3) << B;
    
    std::cout << rotation_d2(vecteur(1 ,0), PI/2);
    
    std::cout << "\n" << segment(sommet(0,0),sommet(1,0));
    
    std::cout << "Test de scene\n";
    
    polygone poly(4);
    for (int i =0; i<4; i++) {
        std::cout << poly.segments[i];
    };
    
    
    return 0;
    
}
