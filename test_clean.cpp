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
    scn.nb_obstacle=0;
    scn.depart = sommet(0 ,-1);
    scn.objectif = sommet(4,4);
    scn.obstacles.resize(16);
    for (int i =0; i<4; i++) {
        for (int j=0; j<4; j++) {
            scn.obstacles[i+4*j]=polygone((i+j)%7+3,vecteur(i,j+0.1*i),0.3);
            scn.nb_obstacle++;
       }
    }
    
    /* Scene de deux obstacles qui se supperposent */
//    scn.nb_obstacle=2;
//    scn.depart = sommet(0 ,0);
//    scn.objectif = sommet(4,0);
//    scn.obstacles.resize(2);
//    scn.obstacles[0] = polygone(5,vecteur(2,1),1.5);
//    scn.obstacles[1] = polygone(5,vecteur(2,-1),1.5);
    
    /* Scene trop cool avec une sorte de labyrinthe */
    scn.nb_obstacle=5;
    scn.depart = sommet(0 ,-1);
    scn.objectif = sommet(13,13);
    scn.obstacles.resize(5);
    
    vector<sommet> v0;
    v0.resize(10);
    v0[0]=sommet(1,0);
    v0[1]=sommet(9,0);
    v0[2]=sommet(9,7);
    v0[3]=sommet(4,7);
    v0[4]=sommet(4,8);
    v0[5]=sommet(3,8);
    v0[6]=sommet(3,6);
    v0[7]=sommet(8,6);
    v0[8]=sommet(8,1);
    v0[9]=sommet(1,1);
   
    vector<sommet> v1;
    v1.resize(4);
    v1[0]=sommet(3,5);
    v1[1]=sommet(3,4);
    v1[2]=sommet(7,4);
    v1[3]=sommet(7,5);
    
    vector<sommet> v2;
    v2.resize(8);
    v2[0]=sommet(0,2);
    v2[1]=sommet(6,2);
    v2[2]=sommet(6,3);
    v2[3]=sommet(1,3);
    v2[4]=sommet(1,9);
    v2[5]=sommet(9,9);
    v2[6]=sommet(9,10);
    v2[7]=sommet(0,10);
    
    vector<sommet> v3;
    v3.resize(4);
    v3[0]=sommet(4,0.5);
    v3[1]=sommet(4,-15);
    v3[2]=sommet(5,-15);
    v3[3]=sommet(5,0.5);
    
    vector<sommet> v4;
    v4.resize(4);
    v4[0]=sommet(4,25);
    v4[1]=sommet(4,9.5);
    v4[2]=sommet(5,9.5);
    v4[3]=sommet(5,25);
    
    scn.obstacles[0] = polygone(v1);
    scn.obstacles[1] = polygone(v2);
    scn.obstacles[2] = polygone(v3);
    scn.obstacles[3] = polygone(v4);
    scn.obstacles[4] = polygone(v0);
   
    calcule_le_plus_court_chemin(scn, "sanspadding.txt");
    calcule_le_plus_court_chemin_padding_cercle(scn, "avecpadding.txt", 0.2);
    
    std::cout << maxim(MaxInt,1+MaxInt);
    
    return 0;
}