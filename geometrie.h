//
//  geometrie.h
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 07/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#ifndef __Projet_Xcode___Planification_de_trajectoire__geometrie__
#define __Projet_Xcode___Planification_de_trajectoire__geometrie__

#include <iostream>

class sommet {
    public :
    int dim;
    double* pts;
// CONSTRUCTEURS
    sommet(); // Point de dimension 2 par défaut nul
    sommet(double x);
    sommet(double x,double y);
    sommet(double x,double y,double z);
    sommet(const sommet& s);
    sommet& operator= (const sommet& s);
// AFFICHAGE
    friend std::ostream& operator <<(std::ostream &,const sommet &);
    void print();
};

class segment {
    public :
    sommet S1,S2;
};

#endif /* defined(__Projet_Xcode___Planification_de_trajectoire__geometrie__) */
