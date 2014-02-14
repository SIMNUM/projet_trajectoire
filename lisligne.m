function [ligne] = lisligne(fid)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
ligne = fgetl(fid);
while (ligne(0) == '#')
    ligne = fgetl(fid);
end

end

