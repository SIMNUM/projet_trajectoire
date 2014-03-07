

#include "padding.h"


// quelques fonctions utiles
int sign(double x){return (x<0)?(-1):1;};
int sign0(double x)
{
    if (abs(x)<EPSILON) return 0;
    return (x<0)?(-1):1;
};

int nb_change_sign(double x1,double x2,double y1,double y2)
{
    int res=0;
    if ((sign0(x1)<0 && sign0(x2)>0) || (sign0(x1)>0 && sign0(x2)<0)) {res++;}
    if ((sign0(y1)<0 && sign0(y2)>0) || (sign0(y1)>0 && sign0(y2)<0)) {res++;}
    return res;
};

//calcul la distance entre le segment seg et le vecteur pt
double distance_pt_segment(segment seg, sommet pt)
{
  const double l2 = norm(seg.S1-seg.S2)*norm(seg.S1-seg.S2);  //longueur du segment
  if (l2 == 0.0) return norm(seg.S1-pt);   // v == w case
  // On trouve la projection du point pt sur la droite
  const double t = ps(pt - seg.S1, seg.S2 - seg.S1) / l2;
  if (t < 0.0) return norm(pt-seg.S1);       // la projection tombe au delà de S1
  else if (t > 1.0) return norm(pt-seg.S2);  // la projection tombe au delà de S2
  // Projection appartient au segment
  return abs(ps(seg.n,vecteur(seg.S1,pt)));
};


double distance_pt_polygone(polygone p, sommet pt)
{
    double aux;
    double res=numeric_limits<double>::max();
    for(int i=0; i<p.nb_sommet; i++)
    {
       aux=distance_pt_segment(p.segments[i],pt);
       if(aux<res) res=aux;
    }
    return res;
};
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

void padding_sommet(const polygone &P, segment seg1, segment seg2,vector<sommet> & tab, double r, unsigned int n)
{
        double angle=acos(ps(seg1.n,seg2.n));
        if (debug) cout<<"angle="<<angle*360/PI<<endl;
        if(angle<EPSILON) return ;
        if(det_d2(seg1.n, seg2.n)<0)
        {//angle "entrant" dans le polygone (non convexe)
            vecteur v=vecteur(seg1.S2,seg1.S1);
            v=v/norm(v);
            double L=r/tan((PI-angle)/2);
            if (debug) cout<<"angle alpha="<<(PI-angle)*360/PI<<endl;
            sommet S=seg1.S2+r*seg1.n+L*v;
            if (distance_pt_polygone(P,S)>(r-EPSILON) && det_d2(seg2.S2-seg1.S1, S-seg1.S1)>0) tab.push_back(S);
            if (debug)
            {
                cout<<"pour le segment :"<<seg1<<endl;
                cout<<"c'est un angle entrant"<<endl;
                cout<<"on push_back le point"<<S<<endl;
            }
        }
        else
        {//l'angle d'un polygone convexe
            double xi, yi;
            double cst=(2*r*sin(angle/(2*(n-1))))/sin(angle/(n-1));
            double theta;
            sommet S1=seg1.S2+r*seg1.n;
            if (distance_pt_polygone(P,S1)>(r-EPSILON)) tab.push_back(S1);
            if (debug) cout<<"on push_back le point"<<seg1.S2+r*seg1.n<<endl;
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
                if (distance_pt_polygone(P,S)>(r-EPSILON)) tab.push_back(S);
                if (debug) cout<<"on push_back le point"<<S<<endl;
            };
            sommet S=seg2.S1+r*seg2.n;
            if (distance_pt_polygone(P,S)>(r-EPSILON))  tab.push_back(S);
            if (debug) cout<<"on push_back le point"<<S<<endl;
        }
        return ;
};


void padding_sommet_rectangle(segment seg1, segment seg2, vector<sommet> & tab, vecteur el, vecteur eL)
{
    double angle=PI-acos(ps(seg1.n,seg2.n));
        if(angle<EPSILON) return ;
        if(det_d2(seg1.n, seg2.n)<0)
        {//angle "entrant" dans le polygone (non convexe)
            vecteur v=vecteur(seg1.S2,seg1.S1);
            v=v/norm(v);
            //épaisseur du padding  sur les segments seg1 et seg2
            double r1=0.5*(abs(ps(seg1.n,eL))+abs(ps(seg1.n,el))) ;
            double r2=0.5*(abs(ps(seg2.n,eL))+abs(ps(seg2.n,el))) ;
            double L=(r1*cos(angle)+r2)/sin(angle);
            sommet S=seg1.S2+r1*seg1.n+L*v;
            if (debug)
            {
                cout<<"pour le segment :"<<seg1<<endl;
                cout<<"c'est un angle entrant : angle="<<angle*360/PI<<", L="<<L<<" et v="<<v<<endl;
                cout<<"on push_back le point"<<S<<endl;
                cout<<"r1="<<r1<<" et r2="<<r2<<endl;
                cout<<"padding1="<<ps(vecteur(seg1.S2,S),seg1.n)<<" et padding2="<<ps(vecteur(seg1.S2,S),seg2.n)<<endl;
            }
            tab.push_back(S);
        }
        else
        {
            int L1, l1, L2, l2;
            L1=sign0(ps(eL,seg1.n)); l1=sign0(ps(el,seg1.n));
            L2=sign0(ps(eL,seg2.n)); l2=sign0(ps(el,seg2.n));
            int n=nb_change_sign(l1,l2,L1,L2);
            if (debug)
                {
                    cout<<"pour le segment :"<<seg1<<endl;
                    cout<<"L1="<<L1<<", l1="<<l1<<", L2="<<L2<<", l2="<<l2<<", change_signe="<<n<<endl;
                };

            if(l1==0) l1=sign(ps(seg2.n,el));
            if(L1==0) L1=sign(ps(seg2.n,eL));
            sommet S=seg1.S2+0.5*(L1*eL+l1*el);
            if (debug) cout<<"on push_back le point"<<S<<endl;
            tab.push_back(S);
            if (n>0)
            {
                if(l2==0) l2=sign(ps(seg1.n,el));
                if(L2==0) L2=sign(ps(seg1.n,eL));
                sommet S2=seg2.S1+0.5*(L2*eL+l2*el);
                if(n==2)
                {
                    vecteur v=L1*eL-l1*el;
                    sommet S3=seg1.S2+0.5*sign(det_d2(L1*eL+l1*el,v))*v ;
                    if (debug){cout<<"on push_back le point"<<S3<<endl;}
                    tab.push_back(S3);
                }
                if (debug)
                {
                    cout<<"on push_back le point"<<S2<<endl;
                    cout<<"padding="<<ps(vecteur(seg1.S2,S2),seg2.n)<<endl;
                }
                tab.push_back(S2);
            }
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
        padding_sommet(P, seg1, seg2, tab, r, n);
        seg1=seg2;
    };
    padding_sommet(P, seg1,P.segments[0],tab,r,n);
    polygone pad(tab);
    return pad;
};

//PADDING pour un objet rectnagulaire  décrit par les deux vecteurs
// "el" et "eL".
// La fonction padding_cercle prend en argument un polygone "P"
//et les deux vecteurs "el" et "eL" et génére le nouveau polygone
// "pad" avec une couche de padding

polygone  padding_rectangle(const polygone& P, vecteur el, vecteur eL)
{
    vector<sommet> tab;
    tab.reserve(3*P.nb_sommet); //on connait d'emblee la taille max-> evite des resize
    segment seg1=P.segments[0];
    segment seg2;
    for(int i=1; i<P.nb_sommet; i++)
    {
        seg2=P.segments[i];
        padding_sommet_rectangle(seg1,seg2,tab,el,eL);
        seg1=seg2;
    };
    padding_sommet_rectangle(seg1,P.segments[0],tab,el,eL);
    polygone pad(tab);
    return pad;
};
