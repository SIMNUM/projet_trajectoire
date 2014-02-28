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
#include <fstream>
#include "geometrie.h"
#include "graph.h"

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
    // A partir d'une liste de points
    polygone(const vector<sommet>&);
    // Translation, dilatation, rotation par rapport au centre de gravité du polygone
    void transformation_poly(const vecteur&,double dill ,double theta);
    void remplissage_segm();

    // AFFICHAGE
    friend std::ostream& operator <<(std::ostream &,const polygone &);
    // ECRITURE
    void print_fichier(std::ostream&);
};

class scene {
public:
    int nb_obstacle;
    sommet depart;
    sommet objectif;
    vector<polygone> obstacles;

    // ECRITURE DANS UN FICHIER
    void exporte(string titre);

    // LECTURE D'UN FICHIER
    void importe(string titre);


};



#endif /* defined(__Projet_Xcode___Planification_de_trajectoire__scene__) */
