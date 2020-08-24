#include "cmdServo.hpp"
#include "communication.hpp"

Servo::Servo(int id) : a_id{id} {
    std::cout << "Initialisation d'un servo d'id " << a_id << std::endl;
}

int Servo::READ_id() { // doit retourner cmdValue et parmts
    Communication& servo=Communication::Instance(); // Ouverture de la communication si elle a pas déjà été ouverte

    uint8_t cmdValue{0x0E};
    int cmdLen{6};
    int responseLen{1}; // Il attend 1 réponse : l'id

    int result = servo.COM(a_id, cmdValue, responseLen, cmdLen);
    
    return result;
}
 
void Servo::WRITE_Servo_Angle(float angle, float time) { // doit déplacer le servo à l'angle donnée pour la vitesse donnée
    // L'angle est en degrés et le temps en secondes
    Communication& servo=Communication::Instance(); // Ouverture de la communication si elle a pas déjà été ouverte

    if (angle > 240.0) // Je vérifie que l'angle recu est bien entre 0 à 240 degrés
        angle = 240.0;
    else if (angle < 0.0)
        angle = 0.0;
    float valueAngleF = angle / 0.24; // Je transforme l'angle en valeur de 0 à 1000
    unsigned short valueAngleUs = (unsigned short)valueAngleF; // Je le caste en unsigned short
    unsigned char lsbAngle = (uint8_t)(valueAngleUs & (uint16_t)0x00FF); // Poids faible 
    unsigned char msbAngle = (uint8_t)((valueAngleUs & (uint16_t)0xFF00) >> 8); // Poids fort

    if (time > 3.0) // Je vérifie que le temps recu est bien entre 0 à 3 secondes
        time = 3.0;
    else if (time < 0.0)
        time = 0.0;
    float valueTimeF = time * 1000; // Je transforme les secondes en millisec
    unsigned short valueTimeUs = (unsigned short)valueTimeF; // Je le caste en unsigned short
    unsigned char lsbTime = (uint8_t)(valueTimeUs & (uint16_t)0x00FF); // Poids faible
    unsigned char msbTime = (uint8_t)((valueTimeUs & (uint16_t)0xFF00) >> 8); // Poids fort

    int parametersLen {4}; // Cette cmd a besoin de 4 paramètres
    uint8_t parameters[parametersLen] = {lsbAngle,msbAngle,lsbTime,msbTime};
    uint8_t cmdValue{0x01};
    int cmdLen{10};


    servo.WRITE(a_id, cmdValue, cmdLen, parameters, parametersLen);

    uint8_t cmdValueReadPos{0x1C};
    int cmdLenReadPos{6};
    int responseLenReadPos{2}; // Il attend 2 réponse : position actuelle du servo lower 8 bits et higher

    
    // Tant que le servo n'est pas dans sa position final alors attendre afin de de ne pas écraser le mouvement par son prochain
    bool position{false};
    while(!position)
    {
        usleep(1000); // wait 1 millisec
        signed short int resultReadPos = servo.COM(a_id, cmdValueReadPos, responseLenReadPos, cmdLenReadPos); // resultReadPos est en signed short int car l'angle peut être négatif
        
        // position doit etre vérifiée avec une marge d'erreur de 5 deg pour l'instant
        unsigned short int currentPos = resultReadPos * 0.24; 
        std::cout << "La position du servo : " << resultReadPos << " en degres ca donne : " << currentPos << " l'objectif est : " << angle << std::endl;
        if ((angle-2) < currentPos & (angle+2) > currentPos)
        {
            position = true;
        }
    }
}