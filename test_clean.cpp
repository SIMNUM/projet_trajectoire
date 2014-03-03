//
//  test_clean.cpp
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 03/03/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#include "graph.h"


int main(int argc, const char * argv[])
{
    scene scn;
    
    /* Scene mozaique */
//    scn.nb_obstacle=0;
//    scn.depart = sommet(0 ,-1);
//    scn.objectif = sommet(4,4);
//    scn.obstacles.resize(16);
//    for (int i =0; i<4; i++) {
//        for (int j=0; j<4; j++) {
//            scn.obstacles[i+4*j]=polygone((i+j)%7+3,vecteur(i,j+0.1*i),0.3);
//            scn.nb_obstacle++;
//        }
//    }
    
    scn.nb_obstacle=2;
    scn.depart = sommet(0 ,0);
    scn.objectif = sommet(4,0);
    scn.obstacles.resize(2);
    scn.obstacles[0] = polygone(5,vecteur(2,1),1.5);
    scn.obstacles[1] = polygone(5,vecteur(2,-1),1.5);
   
    calcule_le_plus_court_chemin(scn, "sanspadding.txt");
    calcule_le_plus_court_chemin_padding_cercle(scn, "avecpadding.txt", 0.5);
    
    return 0;
}