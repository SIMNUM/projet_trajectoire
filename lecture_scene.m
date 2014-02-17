function [depart,objectif,nbpoly,Poly]=lecture_scene(nomfile)
fid=fopen(nomfile,'r');

if fid <=0,
   msg=['Le fichier de scene : ' nomfile ' n''a pas ete trouve'];
   error(msg);
end

depart = str2num(lisligne(fid));
objectif = str2num(lisligne(fid));

nbpoly = str2num(lisligne(fid));
Poly = cell(nbpoly,1);
for i=1:nbpoly
    taillepoly = str2num(lisligne(fid));
    for j =1:taillepoly
        Poly{i}= [Poly{i} ; str2num(lisligne(fid))];
    end
    Poly{i}= [Poly{i} ; Poly{i}(1,:)];   
end

hold on
for k=1:nbpoly
    fill(Poly{k}(:,1),Poly{k}(:,2),'r');
end
hold off

    


        
        