

#include "padding.h"

//---------------------------------------------------------------
//-----------------PADDING---------------------------------------
//---------------------------------------------------------------

polygone padding_simple(const polygone&  P, double r)
{
    int n=P.nb_sommet;
    vector<sommet> tab(n); //on connait d'emblee la taille finale du vecteur-> evite des resize
    segment seg1=P.segments[0];
    segment seg2;
    tab[0]=(seg1.S1+0.5*r*(seg1.n+P.segments[n-1].n));
    for(int i=1; i<n; i++)
    {
        seg2=P.segments[i];
        tab[i]=(seg1.S2+0.5*r*(seg1.n+seg2.n));
        seg1=seg2;
    };
    polygone pad(tab);
    return pad;
};

/*
polygone arc_cercle(double angle,double r,unsigned int n)
{
    vector<sommet> tab(n);
    int it=0;
    tab[it]=sommet (r,0); it++;
    double xi, yi;
    for(unsigned int j=1; j<n; j++)
        {
            xi=r*cos((angle*j)/n);
            yi=r*sin((angle*j)/n);
            tab[it]=sommet (xi,yi); it++;
        };
    polygone pad(tab);
    return pad;
};

polygone arc_cercle_ext(double angle,double r,unsigned int n)
{
    vector<sommet> tab(n);
    int it=0;
    tab[it]=sommet (r,0); it++;
    double xi, yi;
    double cst=(2*r*sin(angle/(2*(n-1))))/sin(angle/(n-1));
    for(unsigned int j=1; j<n-1; j++)
        {
            xi=cst*cos(angle*(j+0.5)/(n-1));
            yi=cst*sin(angle*(j+0.5)/(n-1));
            tab[it]=sommet (xi,yi); it++;
        };
    tab[it]=sommet(r*cos(angle),r*sin(angle)); it++;
    polygone pad(tab);
    return pad;
};*/

void padding_sommet(segment seg1, segment seg2, vector<sommet> & tab, double r, unsigned int n)
{

        double angle=acos(ps(seg1.n,seg2.n));
        if(angle<EPSILON) return ;
        if(det_d2(seg1.n, seg2.n)<0)
        {//angle "entrant" dans le polygone (non convexe)
            vecteur v=vecteur(seg1.S1,seg1.S2)-vecteur(seg2.S1,seg2.S2);
            v=v/norm(v);
            sommet S=seg1.S2+2*r*sin(angle/2)*v;
            tab.push_back(S);
        }
        else
        {//l'angle d'un polygone convexe
            double xi, yi;
            double cst=(2*r*sin(angle/(2*(n-1))))/sin(angle/(n-1));
            double theta;
            tab.push_back(seg1.S2+r*seg1.n);
            for(unsigned int j=1; j<n-1; j++)
            {
                xi=cst*cos(angle*(j+0.5)/(n-1));
                yi=cst*sin(angle*(j+0.5)/(n-1));
                sommet S(xi,yi);
                //on fait un changement de repère
                theta=acos(ps(seg1.n,vecteur(1,0)));
                if(seg1.n.pts[1]<0){theta=-theta;};
                S=rotation_d2(S,theta);
                S=translation(seg2.S1,S);
                tab.push_back(S);
            };
            tab.push_back(seg2.S1+r*seg2.n);
        }
        return ;
};


//PADDING pour un objet circulaire  de rayon r
// la fonction padding_cercle prend en argument un polygone "P"
//et le rayon "r" de l'objet  et génére le nouveau polygone
// "pad" avec une couche de padding

polygone  padding_cercle(const polygone& P, double r, unsigned int n)
{
    vector<sommet> tab;
    tab.reserve(n*P.nb_sommet); //on connait d'emblee la taille max-> evite des resize
    segment seg1=P.segments[0];
    segment seg2;
    for(int i=1; i<P.nb_sommet; i++)
    {
        seg2=P.segments[i];
        padding_sommet(seg1,seg2,tab,r,n);
        seg1=seg2;
    };
    padding_sommet(seg1,P.segments[0],tab,r,n);
    polygone pad(tab);
    return pad;
};
