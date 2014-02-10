//
//  geometrie.cpp
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 07/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#include "geometrie.h"

/* FONCTIONS DE LA CLASSE SEGMENT */

    // Constructeurs


sommet::sommet(){ // Point de dimension 2 par défaut nul
    dim=2;
    pts = new double[2];
    pts[0] = 0.;pts[1] = 0.;
};
sommet::sommet(double x){
    dim=1;
    pts = new double[1];
    pts[0] = x;
}
sommet::sommet(double x,double y){
    dim=2;
    pts = new double[2];
    pts[0] = x;pts[1] = y;
}
sommet::sommet(double x,double y,double z){
    dim=3;
    pts = new double[3];
    pts[0] = x;pts[1] = y;pts[2]=z;
}
sommet::sommet(const sommet& s){
    dim = s.dim;
    pts = new double[dim];
    for (int i=0; i<dim; i++) {
        pts[i]=s.pts[i];
    }
}
sommet& sommet::operator= (const sommet& s){
    dim = s.dim;
    pts = new double[dim];
    for (int i=0; i<dim; i++) {
        pts[i]=s.pts[i];
    }
    return *this;
}

    // Affichage

std::ostream& operator <<(std::ostream & out,const sommet & s){
    out<< "(" << s.pts[0];
    for (int i=1; i<s.dim; i++) {
        out << "," << s.pts[i];
    };
    out<< ")";
    return out;
}
void sommet::print(){
    std::cout<< "(" << pts[0];
    for (int i=1; i<dim; i++) {
        std::cout << "," << pts[i];
    };
    std::cout<< ")";
}
