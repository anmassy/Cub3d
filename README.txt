/* parsing */

partie global :
/OK\ -verifier que le fichier donner est bien un .cub
/OK\ -verifier si il est pas vide

il y a deux partie a faire dans le parsing une partie texture et une partie map :

Pour la partie texture il faut gerer :
/OK\ -qu'il y est bien les 6 texture "NO, SO, EA, WE, F, C"
/OK\ -que c'est 6 texture sont bien toutes au dessus de la map
/OK\ -verifier si les 4 textures "NO, SO, EA, WE" on un path/ligne correct (a savoir un bon path en .xpm)
     -verifier que les 2 autre texture "F, C" on une ligne correcte a savoir 3 valeur comprise entre 0 et 255
/OK\ -verifier qu'il y est rien d'autre que les 6 texture et la map (c'est a dire pas de ligne intrusif)

Pour la partie map il faut gerer :
/OK\ -que la map ne soit pas trop petite (normalement cela se fait avec toutes les condition que l'on met)
/OK\ -qu'il y est les bonne valeur "1, 0, N, S, E ,W"
/OK\ -qu'il n'y est pas deux player mais qu'il y en ai au moins un
/OK\ -que la map soit bien entourer de mur peut importe la forme

/* Raytracing */


recuperer les colonne et les ligne