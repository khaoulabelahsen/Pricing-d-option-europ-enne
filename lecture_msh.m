%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% lecmail.m:
% routine de lecture de fichiers de maillages triangulaires 2D au format .msh 
% 
% SYNOPSIS [Nbpt,Nbtri,Coorneu,Refneu,Numtri,Reftri,Nbaretes,Numaretes,Refaretes]=lecmail(nomfile)
%          
% INPUT * nom_maillage : le nom d'un fichier de maillage au format msh
%                   AVEC SON SUFFIXE .msh
%
% OUTPUT - Nbpt : nbre de sommets (entier) 
%        - Nbtri : nbre de triangles (entier)
%        - Coorneu : coordonnees (x, y) des sommets (matrice reelle Nbpt x 2)
%        - Refneu : reference des sommets (vecteur entier Nbpt x 1)
%        - Numtri : liste de triangles 
%                   (3 numeros de sommets - matrice entiere Nbtri x 3)
%        - Reftri : reference des triangles (matrice entiere Nbtri x 1)
%        - Nbaretes : Nombre d'aretes sur la frontiere.
%        - Numaretes(Nbaretes,2) = numero des 2 Noeuds de chaque Arete de la frontiere 
%		 - Refaretes(Nbaretes,1) = Reference de chaque arete de la
%		 fronti?re
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [Nbpt,Nbtri,Coorneu,Refneu,Numtri,Reftri,Nbaretes,Numaretes,Refaretes]=lecture_msh(nomfile)
fid=fopen(nomfile,'r');
if fid <=0,
   msg=['Le fichier de maillage : ' nomfile ' n''a pas ete trouve'];
   error(msg);
end
while ~strcmp(fgetl(fid),'$MaillageType'), end
maillage_type=str2num(fgetl(fid));
while ~strcmp(fgetl(fid),'$Nodes'), end
Nbpt = str2num(fgetl(fid));
Coorneu = zeros(Nbpt,2);
Refneu = zeros(Nbpt,1);
Nbaretes = 0;
Numaretes = [];
Refaretes = [];
Refneu=[];
RefneuBis = zeros(Nbpt,1);
for i=1:Nbpt
tmp= str2num(fgetl(fid));
Coorneu(i,:) = tmp(2:3);
end


% on traite les references des triangles
if maillage_type==1 % P1
  disp('P1');
  
  while ~strcmp(fgetl(fid),'$Elements'), end
  Nbtri = str2num(fgetl(fid));
  Numtri = zeros(Nbtri,3);
  Reftri = zeros(Nbtri,1);
  
  tmp= str2num(fgetl(fid));
  for i=1:Nbtri
     Numtri(i,:) = tmp(end-2:end);
     Reftri(i)=tmp(end-3);
     tmp= str2num(fgetl(fid));
  end
else
  disp('P2'); % P2
  
  while ~strcmp(fgetl(fid),'$Elements2'), end
  Nbtri=str2num(fgetl(fid));
  Numtri = zeros(Nbtri,3);
  Reftri = zeros(Nbtri,1);
  
  tmp= str2num(fgetl(fid));
  for i=1:Nbtri
     Numtri(i,:) = tmp(end-2:end);
     Reftri(i)=tmp(end-3);
     tmp= str2num(fgetl(fid));
  end
end
fclose(fid);