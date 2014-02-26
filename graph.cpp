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

std::ostream & operator <<(std::ostream & out,const graphe &gra){
    out <<"Matrice\n";
    for (int i=0; i<gra.dim; i++) {
        for (int j=0; j<gra.dim; j++) {
            out<<gra.dist[i][j]<<"  ";
        }
        out<<"\n";
    }
    return out;
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



bool intersection (const sommet& A,const sommet& B,const segment& cd){
    vecteur v(A,B);
    sommet projection(A);
    vecteur AC(A, cd.S1);
    vecteur CD(cd.S1, cd.S2);
    if (std::abs(ps(v, cd.n))<EPSILON) return false;
    else
    {
        double lambda = ps(AC, cd.n)/ps(v, cd.n);
        if ((lambda > -EPSILON)&&(lambda<1+EPSILON))
        {
            projection += lambda*v;
            double CDpCP =ps(CD, vecteur(cd.S1, projection));
            return ((CDpCP>-EPSILON)&&(CDpCP<(norm(CD)*norm(CD))));
        }
        else return(false);
    }
}

bool intersection_totale(const scene& scn, const sommet& source,int som_o,int som_p, const sommet& arrivee,int arr_o, int arr_p){
    for (int i=0; i<scn.nb_obstacle; i++) {
        for (int j=0; j<scn.obstacles[i].nb_sommet; j++) {
            int n =scn.obstacles[i].nb_sommet;
            if (
                !(((i==som_o)&&(j==som_p))
                ||((i==arr_o)&&(j==arr_p))
                ||((i==som_o)&&(j==(som_p-1+n)%n))
                ||((i==arr_o)&&(j==(arr_p-1+n)%n)))
                )
            {
                if (intersection(source, arrivee, scn.obstacles[i].segments[j])) {
                    return true;
                }
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


bool accessible_sur_soimeme(const scene& scn, const polygone& p,int numpol,int i,int s){
    if (i==s) return true;
    vecteur SI(p.sommets[s],p.sommets[i]);
    int n = p.nb_sommet;
    return((!intersection_totale(scn, p.sommets[s],numpol,s,p.sommets[i],numpol,i))&&((ps(SI, vecteur(p.segments[(s-1+n)%n].n))>-EPSILON)||((ps(SI, vecteur(p.segments[s].n))>-EPSILON))));
    
}

bool accessible_sur_autre(const scene& scn,const polygone& p,int numpol,int i,const sommet s,int s_o,int s_p){
    return(!intersection_totale(scn,s,s_o,s_p,p.sommets[i],numpol,i));
}


graphe::graphe(const scene& scn){
    dim = calcule_dimension(scn);
    dist = new double*[dim];
    for (int i=0; i<dim; i++) {
        dist[i] = new double[dim];
    }
    int position=0;
    
    /* Remplissage du point source*/
    dist[0][0]=0;
    position = 1;
        // Polygones
    for (int i=0; i<scn.nb_obstacle; i++) {
        for (int j=0; j<scn.obstacles[i].nb_sommet; j++) {
            if (accessible_sur_autre(scn, scn.obstacles[i],i, j, scn.depart,-1,-1)) {
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
    if (!intersection_totale(scn, scn.depart,-1,-1, scn.objectif,-1,-1)) {
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
            dist[positioninter+l][positioninter+l]=0;
            // Replissage de sois même
            for (int j=l+1; j<scn.obstacles[k].nb_sommet; j++) {
                if (accessible_sur_soimeme(scn, scn.obstacles[k],k, j, l)) {
                    dist[position+l][positioninter+j]=norm(vecteur(scn.obstacles[k].sommets[l], scn.obstacles[k].sommets[j]));
                    dist[positioninter+j][position+l]=dist[position+l][positioninter+j];
                }
                else{
                    dist[position+l][positioninter+j]=MaxInt;
                    dist[positioninter+j][position+l]=dist[position+l][positioninter+j];
                };
            }
            // Remplissage du reste
            positioninter += scn.obstacles[k].nb_sommet;
            for (int i=k+1; i<scn.nb_obstacle; i++){
                for (int j=0; j<scn.obstacles[i].nb_sommet; j++) {
                if (accessible_sur_autre(scn, scn.obstacles[i],i, j, scn.obstacles[k].sommets[l],k,l)) {
                    dist[position+l][positioninter+j]=norm(vecteur(scn.obstacles[k].sommets[l], scn.obstacles[i].sommets[j]));
                    dist[positioninter+j][position+l]=dist[position+l][positioninter+j];
                }
                else {
                    dist[position+l][positioninter+j]=MaxInt;
                    dist[positioninter+j][position+l]=dist[position+l][positioninter+j];
                }
            }
            positioninter +=scn.obstacles[i].nb_sommet;
            }
            // Remplissage du dernier point (Point d'arrivée)
            if (!intersection_totale(scn, scn.obstacles[k].sommets[l],k,l, scn.objectif,-1,-1)) {
                dist[position+l][dim-1] = norm(vecteur(scn.obstacles[k].sommets[l], scn.objectif));
                dist[dim-1][position+l] =dist[position+l][dim-1];
            }
            else{
                dist[position+l][dim-1] = MaxInt;
                dist[dim-1][position+l] =dist[position+l][dim-1];
            }
            
        }
        position +=scn.obstacles[k].nb_sommet;
    }
    
}


void calcule_chemin (const graphe& graph, int* solution ){
    
    /* INITIALISATION */
    // On intialise un vecteur "longueur" avec la première colonne de la matrice de graphe
    double* longueur = new double[graph.dim];
    //solution = new int[graph.dim];
    for (int i =0; i<graph.dim; i++) {
        longueur[i] = graph.dist[0][i];
        solution[i] = 0;
    }
    
    // On initialise deux ensembles de sommets S et T
    bool* S=new bool[graph.dim];
    bool* T=new bool[graph.dim];
    S[0] = true; T[0] = false;
    for (int i=1; i<graph.dim; i++) {
        S[i] = false;
        T[i] = true;
    }
    
    /* ITERATION */
    
    for (int action = 1; action < graph.dim; action++) {
        int i = minimum(longueur, T, graph.dim);
        T[i] = false; S[i] = true;
        for (int j=0; j<graph.dim; j++) {
            if (j!=i) {
                if (longueur[j]>(longueur[i]+graph.dist[i][j])) {
                    longueur[j] =longueur[i]+graph.dist[i][j];
                    solution[j]=i;
                }
            }
        }
    }

}

int minimum (const double* liste,const bool* T, int n){
    int min = 0;
    while (!T[min]&&(min<n)) {
        min++;
    }
    
    for (int i=(min+1); i<n; i++) {
        if ((liste[i]<liste[min])&&T[i])
            min = i;
    }
    return min;
}
