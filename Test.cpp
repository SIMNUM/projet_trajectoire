//
//  Test.cpp
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 07/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#include <iostream>
#include "scene.h"
#include "padding.h"
#include "graph.h"


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
    vectsom.resize(4);
    vectsom[0]=sommet(-5,0);
    vectsom[1]=sommet(-6,-1);
    vectsom[2]=sommet(-4,0);
    vectsom[3]=sommet(-6,1);
    
    std::cout << polygone(vectsom);
    
    // TEST DE SCENE
    
    scene essais;
    essais.nb_obstacle=4;
    essais.depart = sommet(-8,0);
    essais.objectif = sommet(5,0);
    essais.obstacles.resize(4);
    essais.obstacles[0] = padding_cercle(polygone(4,vecteur(2,0),1),0.5);
    essais.obstacles[1] = polygone(3,vecteur(-2,0),1);
    essais.obstacles[2] = polygone(6,vecteur(0,1),1);
    essais.obstacles[3] = padding_cercle(polygone(vectsom),0.5);
    
    essais.exporte("scene1.txt");
    graphe Gra(essais);
    std::cout << Gra;
    int* sollu = new int[Gra.dim];
    calcule_chemin(Gra, sollu);
    for (int i=0; i<Gra.dim; i++) {
        std::cout << sollu[i] << " --> " << i <<"\n";
    };
    
    
    sommet P(0,0);
    segment Bloc(sommet(1,1),sommet(1,-1));
    vecteur v(1,2);
    
    if (intersection_totale(essais, essais.depart, -1, -1, essais.obstacles[3].sommets[3], 3, 3)) std::cout <<"ca intersercte alors que ça devrait pas \n";
    
    if (intersection( essais.depart, essais.obstacles[3].sommets[3],essais.obstacles[3].segments[3])) std::cout <<"ca intersercteCP";
    
    

    scene essais2;
    essais2.nb_obstacle=1;
    essais2.depart = sommet(-2,0);
    essais2.objectif = sommet(2,0);
    essais2.obstacles.resize(1);
    essais2.obstacles[0] = polygone(6,vecteur(0,0.2),1);
    
    graphe G(essais2);
    std::cout << G;
    int* sol = new int[G.dim];
    calcule_chemin(G, sol);
    int* res;
    res=liste_sommet(sol, G.dim);
    for (int i=0; i<G.dim; i++) {
        std::cout << sol[i] << " --> " << i << "+" << res[i]<< "\n";
    };
    essais2.exporte("essais.txt");
    ajoute_au_fichier(res, G.dim, essais2, "essais.txt");
    
    
    return 0;
    
}
