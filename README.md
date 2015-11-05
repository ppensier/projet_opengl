Projet Intervisibilités

Changement: ajout de la classe QGLViewer(librairie pour faciliter l'insertion d'opengl dans qt)
->nouveau widget avec qglviewer dans la fenetre + layout(sinon on ne peut ajouter de paramètre supplémentaire dans les widget créés par Qt Designer)
ajout d'une référence tableau en paramètre de la classe QGLViewer pour récupérer le tableau lu dans QMainWindow
programme:
-récupérer la position d'un point sur le maillage de points si l'utilisateur clique dessus(transformation du système caméra au système terrain?).
