# RobotHexapod

**Pour lancer le projet (sous vs code avec l'extension c/c++ de microsoft) :**

Ctrl + Shift + b (ou dans le terminal taper "make") : Build du projet
(g++ -std=c++17 -ggdb -Iinclude src/communication.cpp src/cmdServo.cpp src/main.cpp -o bin/main )

f5 : debugging + résultat du programme
(ou de la racine faire ./bin/main)

**Attention il faut être sous linux pour que le code fonctionne**

Les servomoteurs fonctionnent en big endian.

A noter que le SERVO_OR_MOTOR_MODE_READ ne pourra pas fonctionner car quand il y a deux réponses, le programme transformes le lower et le higher bits en octet. 
Il n'y aura pas besoin de motor mode dans tous les cas.