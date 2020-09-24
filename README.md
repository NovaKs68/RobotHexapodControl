# RobotHexapod


**Pour lancer le projet (sous vs code avec l'extension c/c++ de microsoft) :**

Ctrl + Shift + b (ou dans le terminal taper "make") : Build du projet
(g++ -std=c++17 -ggdb -Iinclude src/communication.cpp src/leftFrontLeg.cpp src/board.cpp src/leg.cpp src/leftBackLeg.cpp src/rightFrontLeg.cpp src/leftMiddleLeg.cpp src/cmdServo.cpp src/rightBackLeg.cpp src/main.cpp src/rightMiddleLeg.cpp -o bin/main  -pthread)
- Le flag std=c++17 veut dire qu'on utilise la version c++17. 
- Le flag ggdb permet d'afficher le debugging.
- Le flag Iinclude permet les includes dans le code.
- Le flag pthread permet l'utilisation du std thread.


f5 : debugging + résultat du programme
(ou de la racine faire ./bin/main)

**Attention il faut être sous linux pour que le code fonctionne**

A noter que :
- Le modèle du servo est lx-224.
- Le SERVO_OR_MOTOR_MODE_READ ne pourra pas fonctionner car quand il y a deux réponses, le programme transformes le lower et le higher bits en octet. 
Il n'y aura pas besoin de motor mode dans tous les cas.
- Le servo va à 0.12 sec/60 degrés. Il prendra donc maximum 0.48 sec pour effectuer le plus grand mouvement possible (0 à 240 deg)
- Les servomoteurs fonctionnent en big endian.
- Les servos prennent en moyenne 5500 microsec à répondre (jamais plus de 6 millisec)


### Fonctionnement général : 

![Diagramme de classe représentant le programme actuel. Par la suite je vais faire du polymorphisme sur l'héritage de leg.](img/UMLRobotHexapod.png?raw=true "UMLRobotHexapod")

###### Main.cpp : 

Représente le client. C'est à dire que c'est lui qui va choisir le comportement du robot.
Exemple : Avancer 3 mètres puis tourner à droite

###### Body :

C'est le corps du robot. C'est lui qui va suivant la demande du main, coordonner les pattes afin d'arriver à ses fins.

###### Leg.cpp : 

C'est le parent de chaque patte. Il va contenir toutes les commandes communes aux mouvements des pattes.
Chaque patte est un regroupement de 3 servos. Les pattes ont pour l'instant des mouvements pré-enregistrés.
Exemple : Patte1, position couchée

###### CmdServo.cpp :

C'est l'objet Servo. Ca va permettre de les contrôler séparément. Chaque méthode est une commande différente.
Celui-ci forme les tram si leg demande l'id du servo, alors il va envoyer à communication.cpp l'id du servo, 
le numéro de la commande et les paramètres si il y en a.
(calculer poids fort et poids faible, convertir les degrés en 0/1000 et vérifier ces données (qu'elles ne dépassent pas les limites et par la suite les 
limites d'angles)).
Exemple : Servo 8, donne-moi son id

###### Board.cpp :

C'est un tableau qui récapitule l'état de tous les servos en temps réel.
Ca va permettre de savoir quand un servo a atteint sa position visée. Et donc quand il sera prêt à recevoir de nouveaux ordres.
Si on envoie deux ordres au même servo, sans le board, le deuxième ordre écrasera le premier.
Il va utiliser CmdServo pour faire des requêtes aux servos afin de connaître leur position.

###### Communication.cpp :

Lui va recevoir les infos de CmdServo.cpp, il va assembler la commande packet avec l'id, le numéro de la commande, les paramètres s'il y en a et il ajoutera le checksum.
Il va soit envoyer en WRITE soit en READ ou soit en COM (il envoie le packet et lit la réponse).
Ce sera donc également lui qui va traiter les erreurs de COM.
Il renvoie true ou false suivant son bon déroulement
