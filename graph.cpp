//
//  graph.cpp
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 17/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#include "graph.h"

void initialise(double** dist, int dim){
    dist = new double*[dim];
    for (int i=0; i<dim; i++) {
        dist[i] = new double[dim];
    }
}

graphe::graphe(const graphe& gra){
    dim = gra.dim;
    initialise(dist, dim);
    for (int i=0; i<dim; i++) {
        for (int j=0; j<dim; j++) {
            dist[i][j]=gra.dist[i][j];
        }
    }
}


                       
bool intersection (const sommet& A,const vecteur& v,const segment& cd){
    sommet projection(A);
    vecteur AC(A, cd.S1);
    vecteur CD(cd.S1, cd.S2);
    if (std::abs(ps(v, cd.n))<EPSILON) return false;
    else{
    double lambda = ps(AC, cd.n)/ps(v, cd.n);
    projection += lambda*v;
    double CDpCP =ps(CD, vecteur(cd.S1, projection));
        return ((CDpCP>-EPSILON)&&(CDpCP<(norm(CD)*norm(CD))));
    }
}

bool intersection_totale(const scene& scn, const sommet& source, const sommet& arrivee){
    for (int i=0; i<scn.nb_obstacle; i++) {
        for (int j=0; j<scn.obstacles[i].nb_sommet; j++) {
            if (intersection(source, vecteur(source, arrivee), scn.obstacles[i].segments[j])) {
                return true;
            }
        }
    }
    return false;
}

int calcule_dimension (const scene& scn){
    int dimention = 2;
    for (int i =0; i<scn.nb_obstacle; i++) {
        dimention += scn.obstacles[i].nb_sommet;
    }
    return dimention;
};


bool accessible_sur_soimeme(const scene& scn, const polygone& p,int i,int s){
    if (i==s) return true;
    vecteur SI(p.sommets[s],p.sommets[i]);
    int n = p.nb_sommet;
    return((!intersection_totale(scn, p.sommets[s],p.sommets[i]))&&((ps(SI, vecteur(p.segments[(s-1+n)%n].n))>-EPSILON)||((ps(SI, vecteur(p.segments[s].n))>-EPSILON))));
    
}

bool accessible_sur_autre(const scene& scn,const polygone p,int i,const sommet s){
    return(!intersection_totale(scn,s,p.sommets[i]));
}


graphe::graphe(const scene& scn){
    dim = calcule_dimension(scn);
    initialise(dist, dim);
    int position=0;
    
    /* Remplissage du point source*/
    dist[0][0]=0;
    position = 1;
        // Polygones
    for (int i=0; i<scn.nb_obstacle; i++) {
        for (int j=0; j<scn.obstacles[i].nb_sommet; j++) {
            if (accessible_sur_autre(scn, scn.obstacles[i], j, scn.depart)) {
                dist[0][position+j]=norm(vecteur(scn.depart, scn.obstacles[i].sommets[j]));
                dist[position+j][0]=dist[0][position+j];
            }
            else {
                dist[0][position+j]=MaxInt;
                dist[position+j][0]=dist[0][position+j];
            }
        }
        position +=scn.obstacles[i].nb_sommet;
    }
        // Point d'arrivée
    if (intersection_totale(scn, scn.depart, scn.objectif)) {
        dist[0][dim-1] = norm(vecteur(scn.depart, scn.objectif));
        dist[dim-1][0] =dist[0][dim-1];
    }
    else{
        dist[0][dim-1] =MaxInt;
        dist[dim-1][0] =dist[0][dim-1];
    }
    
    /* Remplissage des polygones*/
    position= 1;
    for (int k=0; k<scn.nb_obstacle; k++) {
        for (int l=0; l<scn.obstacles[k].nb_sommet; l++) {
            int positioninter = position;
            // Replissage de sois même
            
            
        }
    }
    
}
