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
    
    polygone poly(4,vecteur(2,0),2);
    for (int i =0; i<4; i++) {
        std::cout << poly.segments[i];
    };
    
    std::cout << EPSILON;
    
    // Test de Translation et dilatation
//    
//    sommet S(1,1);
//    vecteur v(0,1);
//    
//    std::cout << translation(v, S);
    
    poly.transformation_poly(vecteur(-2,0), 2, PI/4);
    for (int i =0; i<4; i++) {
        std::cout << poly.segments[i];
    };
    
    std::cout << poly;
    
    vector<sommet> vectsom;
    vectsom.resize(3);
    vectsom[0]=sommet(1,0);
    vectsom[1]=sommet(0,3);
    vectsom[2]=sommet(0,-2);
    
    std::cout << polygone(vectsom);
    
    // TEST DE SCENE
    
    scene essais;
    essais.nb_obstacle=3;
    essais.depart = sommet(-5,0);
    essais.objectif = sommet(0,5);
    essais.obstacles.resize(3);
    essais.obstacles[0] = polygone(4,vecteur(2,0),1);
    essais.obstacles[1] = polygone(3,vecteur(-2,0),1);
    essais.obstacles[2] = polygone(6,vecteur(0,1),1);
    
    essais.exporte("scene1.txt");
    
    
    return 0;
    
}
