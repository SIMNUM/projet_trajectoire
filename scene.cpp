//
//  scene.cpp
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 10/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#include "scene.h"

    /* CONSTRUCTEURS */

polygone::polygone(int n,const vecteur& v,double d){
    nb_sommet = n;
    sommets.resize(n);
    segments.resize(n);
    
    sommets[0]=sommet(d,0.) + v;
    for (int i=1; i<n; i++) {
        sommets[i] = v + rotation_d2(sommets[i-1]-v, 2*PI/n);
        segments[i-1]=segment(sommets[i-1], sommets[i]);
    }
    segments[n-1]=segment(sommets[n-1], sommets[0]);
}

polygone::polygone(const vector<sommet>& soms){
    nb_sommet = int(soms.size());
    sommets.resize(nb_sommet);
    segments.resize(nb_sommet);
    
    sommets[0] = soms[0];
    for (int i=1; i<nb_sommet; i++) {
        sommets[i] = soms[i];
        segments[i-1]=segment(sommets[i-1], sommets[i]);
    }
    segments[nb_sommet-1]=segment(sommets[nb_sommet-1], sommets[0]);

}


void polygone::transformation_poly(const vecteur& v,double dill ,double theta){
    
    // Calcul du centre de gravité translaté
    sommet G = sommets[0];
    for (int i=1; i<nb_sommet; i++) {
        G+=sommets[i];
    };
    G/=nb_sommet;
    G += v;
    
    //Translation et Dillatation
    for (int i=0; i<nb_sommet; i++) {
        sommets[i] +=v;
        sommets[i] = dillatation(G, sommets[i], dill);
    };
    
    // Rotation
    if (sommets[0].dim==2) {
        for (int i=0; i<nb_sommet; i++) {
            sommets[i] = rotation_d2(vecteur(G,sommets[i]), theta);
        }
    }
    else {
        // Créer une rotation 3d
    }
    // Remplissage des segments
    remplissage_segm();
};

void polygone::remplissage_segm(){
    for (int i=1; i<nb_sommet; i++) {
        segments[i-1]=segment(sommets[i-1], sommets[i]);
    }
    segments[nb_sommet-1]=segment(sommets[nb_sommet-1], sommets[0]);
};


    /* AFFICHAGE */

std::ostream& operator <<(std::ostream & out,const polygone & poly){
    for (int i=1; i<= poly.nb_sommet; i++) {
        out<< "Segment " << i << "\n";
        out<< poly.segments[i-1];
    };
    
    return out;
};



