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
-Le modèle du servo est lx-224.
-Le SERVO_OR_MOTOR_MODE_READ ne pourra pas fonctionner car quand il y a deux réponses, le programme transformes le lower et le higher bits en octet. 
Il n'y aura pas besoin de motor mode dans tous les cas.
-Le servo va à 0.12 sec/60 degrés. Il prendra donc maximum 0.48 sec pour effectuer le plus grand mouvement possible (0 à 240 deg)
-Les servomoteurs fonctionnent en big endian.
-Les servos prennent en moyenne 5500 microsec à répondre (jamais plus de 6 millisec)
