function affiche(UU,Numtri,Coorneu,titre)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% affiche:
% pour visualiser un ensemble de valeurs aux sommets 
% sur un maillage triangulaire 2D -- a un instant donne --
%
% SYNOPSIS : affiche(UU,Numtri,Coorneu,titre)
%          
% INPUT * UU vecteur de valeurs aux sommets (vecteur Nbpt x 1)
%       * Numtri : liste de triangles 
%                   (3 numeros de sommets - matrice entiere Nbtri x 3)
%       * Coorneu : coordonnees (x, y) des sommets (matrice reelle Nbpt x 2)
%       * titre (optionel) un titre (string)
%
% OUTPUT une fenetre graphique
%
% NOTE 
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Control on the input args
% --------
if (nargin<4), titre = ''; end;
trisurf(Numtri,Coorneu(:,1),Coorneu(:,2),UU);

% Unchanged scale of the x- and y-axes (rectangle pictured as a rectangle)
% ----------
 %axis('equal');

% Top view
% --------
 view(2);

% Coloring the triangles (3 choices)
% --------
 shading interp;
% shading faceted
% shading flat

% Adding the color scale
% --------
 colorbar;

% Adding a title
% --------
title(titre);
grid off;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                        fin de la routine
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

