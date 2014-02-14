
#include "scene.h"
#include "geometrie.h"
#include "padding.h"

//---------------------------------------------------------------
//-----------------PADDING---------------------------------------
//---------------------------------------------------------------


//PADDING pour un objet circulaire  de rayon r
// la fonction padding_cercle prend en argument un polygone "P"
//et le rayon "r" de l'objet  et génére le nouveau polygone
// "pad" avec une couche de padding
polygone padding_cercle(polygone P, double r, unsigned int n=8)
{
    vector<sommet> tab; //faut-il donner la taille pour éviter les resize
    seg1=P.segments[0];
    tab.push_back(seg1.S1+r*seg1.n);
    for(int i=1; i<P.nb_sommet; i++)
    {
        tab.push_back(seg1.S2+r*seg.n);
        seg2=P.segments[i];
        angle=acos(ps(seg1.n,seg2.n);
        double xi, yi;
        double cst=(2*r*sin(angle/(2*(n-1))))/sin(angle/(n-1));
        double theta;
        for(int j=1; j<n; j++)
        {
            xi=cst*cos(angle*(j+0.5)/(n-1));
            yi=xi=cst*sin(angle*(j+0.5)/(n-1));
            sommet S(xi,yi);
            //on fait un chngement de repère
            theta=acos(ps(seg1.n,vecteur(1,0)));
            if(seg1.n.pts[1]<0){theta=theta-PI;};
            S=rotation_d2(S,theta);
            S=translation(seg2.S1,S);
            tab.push_back(S);
        };
        tab.push_back(seg2.S1+r*seg2.n);
        seg1=seg2;
    };
    polygone pad(tab);
    return pad;
};
