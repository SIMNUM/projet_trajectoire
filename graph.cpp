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
    if (det_d2(p.segments[(s-1+n)%n].n, p.segments[s].n)>0) {
        return(!intersection_totale(scn, p.sommets[s],numpol,s,p.sommets[i],numpol,i)
               &&((ps(SI, p.segments[(s-1+n)%n].n)>-EPSILON)
                  ||(ps(SI, p.segments[s].n)>-EPSILON))); // Cas convexe
    }
    else {
        return(!intersection_totale(scn, p.sommets[s],numpol,s,p.sommets[i],numpol,i)
               &&((ps(SI, p.segments[(s-1+n)%n].n)>-EPSILON)
                  &&(ps(SI, p.segments[s].n)>-EPSILON))); // Cas non convexe
    }
    
    
}

// ATTENTION, C'est ici qu'il faut modifier quelque chose : il faut que accessible sur autre prenne en compte qu'on ne puisse pas traverser le polygone du point source : s'inspirer de la fonction du haut.
// Ca permet d'éviter que deux polygones ne se recoupent. Et que ça merde en conséquent.

bool accessible_sur_autre(const scene& scn,const polygone& p,int numpol,int i,const sommet s,int s_o,int s_p){
    vecteur SI(s,p.sommets[i]);
    int n = scn.obstacles[s_o].nb_sommet;
    if (s_o<0||s_p<0) {
        return (!intersection_totale(scn,s,s_o,s_p,p.sommets[i],numpol,i));
    }
    else{
        if (det_d2(scn.obstacles[s_o].segments[(s_p-1+n)%n].n, scn.obstacles[s_o].segments[s_p].n)>0) {
            return(!intersection_totale(scn,s,s_o,s_p,p.sommets[i],numpol,i)
                   &&((ps(SI, scn.obstacles[s_o].segments[((s_p-1+n)%n)].n)>-EPSILON)
                      ||(ps(SI, scn.obstacles[s_o].segments[s_p].n)>-EPSILON))); // Cas convexe
        }
        else {
            return(!intersection_totale(scn,s,s_o,s_p,p.sommets[i],numpol,i)
                   &&((ps(SI, scn.obstacles[s_o].segments[((s_p-1+n)%n)].n)>-EPSILON)
                      &&(ps(SI, scn.obstacles[s_o].segments[s_p].n)>-EPSILON))); // Cas non convexe
        }
    }
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
            dist[position+l][position+l]=0;
            // Replissage de sois même
            for (int j=0; j<scn.obstacles[k].nb_sommet; j++) {
                if (accessible_sur_soimeme(scn, scn.obstacles[k],k, j, l)) {
                    dist[position+l][position+j]=maxim(norm(vecteur(scn.obstacles[k].sommets[l], scn.obstacles[k].sommets[j])),dist[position+j][position+l]);
                    dist[position+j][position+l]=dist[position+l][position+j];
                }
                else{
                    dist[position+l][position+j]=MaxInt;
                    dist[position+j][position+l]=dist[position+l][position+j];
                };
            }
            // Remplissage du reste
            positioninter =1;
            for (int i=0; i<scn.nb_obstacle; i++){
                if (i!=k) {
                    for (int j=0; j<scn.obstacles[i].nb_sommet; j++) {
                        if (accessible_sur_autre(scn, scn.obstacles[i],i, j, scn.obstacles[k].sommets[l],k,l)) {
                            dist[position+l][positioninter+j]=maxim(norm(vecteur(scn.obstacles[k].sommets[l], scn.obstacles[i].sommets[j])),dist[positioninter+j][position+l]);
                            dist[positioninter+j][position+l]=dist[position+l][positioninter+j];
                        }
                        else {
                            dist[position+l][positioninter+j]=MaxInt;
                            dist[positioninter+j][position+l]=dist[position+l][positioninter+j];
                        }
                    }
                    positioninter +=scn.obstacles[i].nb_sommet;
                }
                else{
                    positioninter +=scn.obstacles[i].nb_sommet;
                }
            }
            // Remplissage du dernier point (Point d'arrivée)
            if (!intersection_totale(scn, scn.obstacles[k].sommets[l],k,l, scn.objectif,-1,-1)) {
                dist[position+l][dim-1] = maxim(norm(vecteur(scn.obstacles[k].sommets[l], scn.objectif)),dist[dim-1][position+l]);
                dist[dim-1][position+l] =dist[position+l][dim-1];
            }
            else{
                dist[position+l][dim-1] = MaxInt;
                dist[dim-1][position+l] = dist[position+l][dim-1];
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
    solution[graph.dim-1]=123456789;
    
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
                if ((longueur[j]>(longueur[i]+graph.dist[i][j]))) {
                    longueur[j] =longueur[i]+graph.dist[i][j];
                    solution[j]=i;
                }
            }
        }
    }
    if (solution[graph.dim-1]==123456789) {
        std::cout << "ATTENTION, PAS DE SOLUTION \n";
        solution[graph.dim-1]=graph.dim-1;
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

int* liste_sommet (int* brut,int n){
    int compteur=0;
    int intermediaire = n-1;
    while (brut[intermediaire]!=0&&compteur<n) {
        intermediaire=brut[intermediaire];
        compteur++;
    }
    compteur++;
    int* retraite = new int[compteur+1];
    std::cout << compteur<< "\n";
    intermediaire = n-1;
    for (int i=0; i<compteur+1; i++) {
        retraite[compteur+1-i]=intermediaire;
        intermediaire=brut[intermediaire];
    }
    retraite[0] = compteur+1;
    return retraite;
}

void cherche_coord( int nb_som,int dim, int& poly,int& som,int num,const scene& scn){
    if (num==0||num==dim) {
        poly=-1;
        som=-1;
    }
    else{
        poly=0;
        som =num-1;
        while ((scn.obstacles[poly].nb_sommet)<=som&&poly<scn.nb_obstacle) {
            som -= scn.obstacles[poly].nb_sommet;
            poly++;
        }
        if (poly==scn.nb_obstacle) {
            poly--;
        }
    }
}

void ajoute_au_fichier(int* sol,int dim,const scene& scn, string titre){
    

    ofstream fichier(titre.c_str(), ios::out |ios::app);  // on ouvre le fichier en lecture et écriture, tout en supprimant tout fichier existant qui aurait le même type
    
    if(fichier)  // si l'ouverture a réussi
    {
        fichier << "##  LISTE DES SOMMETS SOLUTIONS \n";
        fichier << "# Nombre de sommets\n";
        fichier << sol[0] << "\n";
        scn.depart.print_fichier(fichier);
        
        for (int i=2; i<sol[0]; i++) {
            int poly,som;
            cherche_coord(sol[0], dim, poly, som, sol[i], scn);
            scn.obstacles[poly].sommets[som].print_fichier(fichier);
        }
        scn.objectif.print_fichier(fichier);

        
        fichier << "END";
        fichier.close();  // on ferme le fichier
        std::cout << "L'écriture a du bien se passer" << endl;
    }
    else  // sinon
        std::cout << "Impossible d'ouvrir le fichier !" << endl;

}

void calcule_le_plus_court_chemin (scene& scn, string titre){
    
    graphe G(scn);
    scn.exporte(titre);
    
    int* sol = new int[G.dim];
    calcule_chemin(G, sol);
    int* res;
    res=liste_sommet(sol, G.dim);
    
    ajoute_au_fichier(res, G.dim, scn, titre);
}

void calcule_le_plus_court_chemin_padding_cercle (scene scn, string titre,double rayon){
    
    // On exporte
    scn.exporte(titre);
    
    // On padding
    for (int i=0; i<scn.nb_obstacle; i++) {
        scn.obstacles[i]= padding_cercle(scn.obstacles[i], rayon,4);
        //scn.obstacles[i]= padding_rectangle(scn.obstacles[i], vecteur(0,1), vecteur(2,0));
        
    }
    
//    for (int j =0; j<scn.obstacles[1].nb_sommet; j++) {
//        std::cout << "n " << j << " = " << scn.obstacles[1].segments[j].n <<"\n";
//    }
    
    //scn.exporte(titre);
    graphe G(scn);
    int* sol = new int[G.dim];
    calcule_chemin(G, sol);
    int* res;
    res=liste_sommet(sol, G.dim);
    ajoute_au_fichier(res, G.dim, scn, titre);
    
}
