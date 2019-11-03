function [P,Coorneu]=visu(results_file, msh_file)
  fid=fopen(results_file,'r');
  if fid <=0,
   msg=['Le fichier de maillage : ' results_file ' n''a pas ete trouve'];
   error(msg);
  end
  
  k_max=str2num(fgetl(fid)); % Nombre de lignes = Nombre d'itéations éffectées
  Delta_t=str2num(fgetl(fid)); % Nombre de points
  P=[];
  fgetl(fid);
  
  for k=1:k_max-1 % On commence par récupérer les P^k à partir de k=2 pour éviter la singularité du log
   P=[P;log(str2num(fgetl(fid)))]; % On prend le log des valeurs sinon ça fait 0
  end
  
  P=real(P);
  [~,~,Coorneu,~,Numtri,~,~,~,~]=lecture_msh(msh_file);
  X=Coorneu(:,1); Y=Coorneu(:,2);
  %myaxis=[min(X), max(X), min(Y), max(Y), min(min(P)), max(max(P)), min(min(P)), max(max(P))];
  fclose(fid);
  
  figure(); % Affichage
  for k=1:k_max-1
    if or(k==51, k==201)
      figure();
    end
    affiche(P(k,:), Numtri, Coorneu, ['Temps = ', num2str(k*Delta_t)]);
    pause(0.01);
  end