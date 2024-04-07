/* parsing */

partie global :
/OK\ -verifier que le fichier donner est bien un .cub
/OK\ -verifier si il est pas vide

il y a deux partie a faire dans le parsing une partie texture et une partie map :

Pour la partie texture il faut gerer :
/OK\ -qu'il y est bien les 6 texture "NO, SO, EA, WE, F, C" peut importe l'ordre
/OK\ -que c'est 6 texture sont bien toutes au dessus de la map
/OK\ -verifier si les 4 textures "NO, SO, EA, WE" on un path/ligne correct (a savoir un bon path en .xpm)
/OK\ -verifier que les 2 autre texture "F, C" on une ligne correcte a savoir 3 valeur comprise entre 0 et 255, attention au virgule
/OK\ -verifier qu'il y est rien d'autre que les 6 texture et la map (c'est a dire pas de ligne intrusif)
/OK\ -vérifier qu'il y ai pas une ligne en doublon (2 fois NO par exemple)
/OK\ -vérifier que la ligne apres les element soit pas vide
/OK\ -vérifier que cela ne soit pas un dossier

Pour la partie map il faut gerer :
/OK\ -que la map ne soit pas trop petite
/OK\ -qu'il y est les bonne valeur "1, 0, N, S, E ,W"
/OK\ -qu'il n'y est pas deux player mais qu'il y en ai au moins un
/OK\ -que la map soit bien entourer de mur peut importe la forme


parsing se deroule ainsi :

-on check si on a bien le bon nombre d'argument et que cela soit les bons
-on recupere les 6 textures chacune dans une variable differente
-on verifie si leurs ligne de path est bonne et que rien ne gene autour
-ensuite on capture la map dans une variable puis on verifie qu'elle soit bonne et fonctionnelle
-on check les mur en fonction du joueur
-puis on lance le raycasting