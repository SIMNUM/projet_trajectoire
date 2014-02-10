//
//  scene.h
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 10/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#ifndef __Projet_Xcode___Planification_de_trajectoire__scene__
#define __Projet_Xcode___Planification_de_trajectoire__scene__

#include <iostream>
#include <vector>
#include "geometrie.h"

using namespace std;

class polygone {
    // On tourne dans le sens trigo
public:
    int nb_sommet;
    vector<sommet> sommets;
    vector<segment> segments;
    
    // CONSTRUCTEUR
// Polygone régulier, centre ve, n >=3cotés,
    polygone(int n=4,const vecteur& v =vecteur(),double d=1.);
    
    
    
    
};

#endif /* defined(__Projet_Xcode___Planification_de_trajectoire__scene__) */
