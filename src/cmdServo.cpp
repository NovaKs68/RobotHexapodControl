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

    if (angle > 3.0) // Je vérifie que le temps recu est bien entre 0 à 3 secondes
        angle = 3.0;
    else if (angle < 0.0)
        angle = 0.0;
    float valueTimeF = time * 1000; // Je transforme les secondes en millisec
    unsigned short valueTimeUs = (unsigned short)valueTimeF; // Je le caste en unsigned short
    unsigned char lsbTime = (uint8_t)(valueTimeUs & (uint16_t)0x00FF); // Poids faible
    unsigned char msbTime = (uint8_t)((valueTimeUs & (uint16_t)0xFF00) >> 8); // Poids fort

    int parametersLen {4}; // Cette cmd a besoin de 4 paramètres
    uint8_t parameters[parametersLen] = {msbAngle,lsbAngle,msbTime,lsbTime}; // Mis dans le sens inverse car c'est du BIG ENDIAN
    uint8_t cmdValue{0x01};
    int cmdLen{10};


    servo.WRITE(a_id, cmdValue, cmdLen, parameters, parametersLen);
}