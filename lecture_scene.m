function []=lecture_scene(nomfile)
fid=fopen(nomfile,'r');

if fid <=0,
   msg=['Le fichier de scene : ' nomfile ' n''a pas ete trouve'];
   error(msg);
end


depart = str2num(lisligne(fid));
        
        