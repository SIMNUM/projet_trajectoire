//
//  scene.cpp
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 10/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#include "scene.h"

polygone::polygone(int n,const vecteur& v,double d){
    nb_sommet = n;
    sommets.resize(n);
    segments.resize(n);
    
    sommets[0]=sommet(d,0.) + v;
    for (int i=1; i<n; i++) {
        sommets[i] = v + rotation_d2(sommet[i-1]-v, 2*PI/n);
        segments.[i-1]=segment(sommets[i-1], sommets[i])
    }
    segments[n-1]=segment(sommets[n-1], sommets[0]);
}