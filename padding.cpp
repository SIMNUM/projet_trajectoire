

#include "padding.h"


// quelques fonctions utiles
int sign(const double& x){return (x<0)?(-1):1;};
int sign0(const double& x)
{
    if (abs(x)<EPSILON) return 0;
    return (x<0)?(-1):1;
};


int nb_change_sign(const double& x1, const double& x2, const double& y1, const double& y2)
{
    int res=0;
    if ((sign0(x1)<0 && sign0(x2)>0) || (sign0(x1)>0 && sign0(x2)<0)) {res++;}
    if ((sign0(y1)<0 && sign0(y2)>0) || (sign0(y1)>0 && sign0(y2)<0)) {res++;}
    return res;
};


vector<double> trinome(const double& a, const double& b, const double& c)
{
    vector<double> res(2,0);
    if (a==0)
    {
        if(b!=0)
        {
            res[0]=-c/b;
            cout<<"équation du 1er ordre"<<endl;
            return res;
        }
        else
        {
            if(c==0)
            {cout<<"equation vérifiée pour tout nombre"<<endl; return res;}
            else {cout<<"aucune solution"<<endl; return res;}
        }

    }
    //equation du second degré
    res[0]=-0.5*(b+sign(b)*sqrt(pow(b,2)-4*a*c))/a;
    res[1]=c/(a*res[0]);
    return res;
};


double distance_pt_polygone(const polygone& p, const sommet& pt)
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


//calcul la distance entre le segment seg et le vecteur pt
double distance_pt_segment( const segment& seg, const sommet& pt)
{
  const double l2 = pow(norm(seg.S1-seg.S2),2) ;  //longueur du segment
  if (l2 == 0.0) return norm(seg.S1-pt);   // v == w case
  // On trouve la projection du point pt sur la droite
  const double t = ps(pt - seg.S1, seg.S2 - seg.S1) / l2;
  if (t < 0.0) return norm(pt-seg.S1);       // la projection tombe au delà de S1
  else if (t > 1.0) return norm(pt-seg.S2);  // la projection tombe au delà de S2
  // Projection appartient au segment
  return abs(ps(seg.n,vecteur(seg.S1,pt)));
};

double distance_tronquee_pt_segment(const segment& seg, const sommet& pt)
{
    const double l2 = pow(norm(seg.S1-seg.S2),2) ;  //longueur du segment
    if (l2 == 0.0) return norm(seg.S1-pt);   // v == w case
    // On trouve la projection du point pt sur la droite
    const double t = ps(pt - seg.S1, seg.S2 - seg.S1) / l2;
    if (t < 0.0 || t>1.0 ) return numeric_limits<double>::max();// la projection tombe au delà de S1 ou S2
    // Projection appartient au segment
    return abs(ps(seg.n,vecteur(seg.S1,pt)));
};


sommet inter_droites(const sommet& s0, const vecteur& v0, const sommet& s1,const vecteur& v1)
{
    if (det_d2(v0,v1)==0)
    {
        cout<<"attention : les droites sont paralelles"<<endl;
        return sommet(0,0);
    }
    double t0=-(s0.pts[0]*v1.pts[1]-s1.pts[0]*v1.pts[1]-v1.pts[0]*s0.pts[1]+v1.pts[0]*s1.pts[1])/det_d2(v0,v1);
    return s0+t0*v0;
};



vector<sommet> inter_droite_cercle(const sommet& s0, const vecteur& v, const sommet& c, const double& r)
{
    vector<sommet> res(2,sommet(0,0));
    vecteur n(v.pts[1],-v.pts[0]);//normale à la droite
    double d=abs(ps(n,c-s0))/norm(n);//distance entre le point c et la droite
    if(norm(v)==0)
        {
            cout<<"le vecteur directeur de la droite est nul !"<<endl;
            return res;
        }
    if(d>r)
        {
            cout<<"la droite et le cercle ne se coupent pas !"<<endl;
            return res;
        }
    //on va résoudre en t l'équation a*t^2+b*t+cs=0
    double a=pow(v.pts[0],2)+pow(v.pts[1],2) ;
    double b=2*(v.pts[0]*(s0.pts[0]-c.pts[0])+v.pts[0]*(s0.pts[1]-c.pts[1])) ;
    double cs=pow(s0.pts[0]-c.pts[0],2)+pow(s0.pts[1]-c.pts[1],2)-pow(r,2) ;
    vector<double> t=trinome(a,b,cs);
    res[0]=s0+t[0]*v;
    res[1]=s0+t[1]*v;
    return res;
};


vector<sommet> inter_cercles(const sommet& c0, const double r0, const sommet& c1, const double r1)
{
    vector<sommet> res(2,0);
    double d=norm(c0-c1); //distance entre les deux centres
    if(d>r0+r1 || d<abs(r1-r0))
    {
        cout<<"les cercles ne s'intersectent pas"<<endl;
        return res;
    }
    if(d==0 && r0==r1)
        {
        cout<<"les deux cercles sont confondus"<<endl;
        res[0]=c1+r1*vecteur(0,1); res[1]=c1+r1*vecteur(0,-1);
        return res;
    }
    double x0=c0.pts[0]; double y0=c0.pts[1];
    double x1=c1.pts[0]; double y1=c1.pts[1];
    double n=0.5*(pow(r1,2)-pow(r0,2)-pow(x1,2)+pow(x0,2)-pow(y1,2)+pow(y0,2))/(y0-y1);
    double aux=(x0-x1)/(y0-y1);
    double a=pow(aux,2)+1;
    double b=2*y0*aux-2*n*aux-2*x0;
    double c=pow(x0,2)+pow(y0,2)+pow(n,2)-pow(r0,2)-2*y0*n;
    vector<double> sol_x=trinome(a,b,c);
    res[0]=sommet(sol_x[0],n-sol_x[0]*aux);
    res[1]=sommet(sol_x[1],n-sol_x[1]*aux);
    return res;
};

int in_padding(const polygone& p,const sommet pt, const vecteur el, const vecteur eL)
{
    bool res=false;
    int i=0;
    double padding;
    while(i<p.nb_sommet && (!res))
    {
        padding=0.5*(abs(ps(p.segments[i].n,eL))+abs(ps(p.segments[i].n,el))) ;
        res=(distance_tronquee_pt_segment(p.segments[i],pt)<padding);
        i ++;
    }
    return res;
};


//---------------------------------------------------------------
//-----------------PADDING---------------------------------------
//---------------------------------------------------------------


polygone padding_simple(const polygone&  P, const double& r)
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


void padding_sommet(const polygone &P, const segment& seg1, const segment& seg2,vector<sommet> & tab, const double& r, const unsigned int n)
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
            if ( det_d2(seg1.n,S-seg1.S1)>=0 && det_d2(seg2.n,S-seg2.S2)<=0 && distance_pt_polygone(P,S)>(r-EPSILON)) tab.push_back(S);

            /*ESSAI ne fonctionnant pas toujours
            cas "grand padding" : comparer la position de S et S_extrem (distance à un segment et non à une droite) !
            segment seg_extrem(seg1.S1,seg2.S2);
            vecteur v_extrem=seg2.S2-seg1.S1;
            sommet S_extrem=seg1.S1+0.5*v_extrem+seg_extrem.n*sqrt(pow(r,2)-pow(norm(v_extrem),2)/4); //r*sqrt(1-pow(0.5*norm(v_extrem)/r,2)); evite de faire sin(arccos(x)) !
            // ajout ou non de S en fonction de la configuration géométrique
            bool b=det_d2(v_extrem,S-seg1.S1)>0 || ( det_d2(S_extrem-seg1.S1,S-seg1.S1)>0 && det_d2(S_extrem-seg1.S1,S-seg2.S2)<0 );
            if (b && distance_pt_polygone(P,S)>(r-pow(EPSILON,2))) tab.push_back(S);*/

            if (debug)
            {
                cout<<"pour le segment :"<<seg1<<endl;
                cout<<"c'est un angle entrant"<<endl;
                cout<<"b="<<(det_d2(seg1.n,S-seg1.S1)>=0 || (det_d2(seg2.n,S-seg2.S2)<=0))<<endl;
                cout<<"b2="<<(distance_pt_polygone(P,S)>(r-EPSILON))<<endl;
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


void padding_sommet_rectangle(const polygone& P,const segment& seg1, const segment& seg2, vector<sommet> & tab, const vecteur& el, const vecteur& eL)
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
            //les angles orientés pour différencier les cas
            double alpha=det_d2(seg1.n,S-seg1.S1);
            double beta=det_d2(seg2.n,S-seg2.S2);
            if(alpha<0 && beta<0)
            {//intersection droite et cercle
                vector<sommet> inter=inter_droite_cercle(seg2.S2+r2*seg2.n,seg2.S1-seg2.S2,seg1.S1,r1);
                if(det_d2(seg1.n,inter[0]-seg1.S1)<=0 && det_d2(seg2.n,inter[0]-seg2.S2)<=0) S=inter[0];
                else S=inter[1];
            }
            if(alpha>0 && beta>0)
            {//intersection droite et cercle
                vector<sommet> inter=inter_droite_cercle(seg1.S1+r1*seg1.n,seg1.S1-seg1.S2,seg2.S2,r2);
                if(det_d2(seg1.n,inter[0]-seg1.S1)>=0 && det_d2(seg2.n,inter[0]-seg2.S2)>=0) S=inter[0];
                else S=inter[1];
            }
            if(alpha<0 && beta>0)
            {//intersection deux cercles
                vector<sommet> inter=inter_cercles(seg1.S1, r1, seg2.S2, r2);
                if(det_d2(seg1.n,inter[0]-seg1.S1)<=0 && det_d2(seg2.n,inter[0]-seg2.S2)>=0) S=inter[0];
                else S=inter[1];
            }
            if (!in_padding(P,S,el,eL)) tab.push_back(S);
            if (debug)
            {
                cout<<"pour le segment :"<<seg1<<endl;
                cout<<"c'est un angle entrant : angle="<<angle*360/PI<<", L="<<L<<" et v="<<v<<endl;
                cout<<"on push_back le point"<<S<<endl;
                cout<<"r1="<<r1<<" et r2="<<r2<<endl;
                cout<<"alpha="<<alpha<<" et beta="<<beta<<endl;
                cout<<"padding1="<<ps(vecteur(seg1.S2,S),seg1.n)<<" et padding2="<<ps(vecteur(seg1.S2,S),seg2.n)<<endl;
            }
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
            if (!in_padding(P,S,el,eL)) tab.push_back(S);
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
                    if (!in_padding(P,S3,el,eL)) tab.push_back(S3);
                }
                if (debug)
                {
                    cout<<"on push_back le point"<<S2<<endl;
                    cout<<"padding="<<ps(vecteur(seg1.S2,S2),seg2.n)<<endl;
                }
                if (!in_padding(P,S2,el,eL)) tab.push_back(S2);
            }
        }
    return ;
};


//PADDING pour un objet circulaire  de rayon r
// la fonction padding_cercle prend en argument un polygone "P"
//et le rayon "r" de l'objet  et génére le nouveau polygone
// "pad" avec une couche de padding

polygone  padding_cercle(const polygone& P, const double& r, const unsigned int n)
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

polygone  padding_rectangle(const polygone& P, const vecteur& el, const vecteur& eL)
{
    vector<sommet> tab;
    tab.reserve(3*P.nb_sommet); //on connait d'emblee la taille max-> evite des resize
    segment seg1=P.segments[0];
    segment seg2;
    for(int i=1; i<P.nb_sommet; i++)
    {
        seg2=P.segments[i];
        padding_sommet_rectangle(P,seg1,seg2,tab,el,eL);
        seg1=seg2;
    };
    padding_sommet_rectangle(P,seg1,P.segments[0],tab,el,eL);
    polygone pad(tab);
    return pad;
};
