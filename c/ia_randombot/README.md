cretinhex/c/randombot
=====================


Description
-----------

BridgeBot est l'IA la plus simple, nous l'appelons parfois *Stupidité artificielle*.  
Elle se contente de placer un pion, au hasard, sur une case libre.

Son code source est écrit *en JNI*, si cela veut dire quelque chose.  
C'est-à-dire que les manipulations sont faîtes directement grâces aux méthodes de la structure *JNIEnv*
proposées dans la bibliothèque *<jni.h>* que nous utilisons.

Son principal fait d'armes a été de valider l'integration des IA externes à l'application Java.  
Jouer contre elle n'a absluement aucun interêt sinon.


Options du makefile
-------------------

Compilation : génère les .o

	make

Nettoyage : supprime les .o

	make [max]clean

