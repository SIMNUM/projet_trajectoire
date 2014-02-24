//
//  graph.h
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 17/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#ifndef __Projet_Xcode___Planification_de_trajectoire__graph__
#define __Projet_Xcode___Planification_de_trajectoire__graph__

#include <iostream>
#include "scene.h"

const double MaxInt = 1E+37;

class graphe {
public:
    // La matrice de graphe est ordonnée comme suit :
    int dim;
    double** dist;
    graphe(const graphe&);
    graphe(const scene& );
    double& distance(int i,int j){return dist[i][j];}
    friend std::ostream & operator <<(std::ostream &,const graphe &);
    
};

// Savoir si un segment est sur le chemin d'une trajectoire (point plus vecteur)
bool intersection (const sommet&,const sommet&,const segment&);

// Savoir si il y a un obstacle entre deux points d'une scène.
bool intersection_totale(const scene&, const sommet& source,int,int, const sommet& arrivee,int,int);
// Calcule la dimention de la matrice pour une scene
int calcule_dimension (const scene&);

// Initialise la matrice dist a la dimention dim
void initialise(double** dist, int dim);

// Vérifie si le sommet i est accessible par le sommet s d'un même polygone
bool accessible_sur_soimeme(const scene& scn, const polygone& p,int numpol,int i,int s);

// Vérifie si le sommet i du polygone p est accessible depuis le sommet s
bool accessible_sur_autre(const scene& scn,const polygone& p,int numpol,int i,const sommet s,int,int);



#endif /* defined(__Projet_Xcode___Planification_de_trajectoire__graph__) */