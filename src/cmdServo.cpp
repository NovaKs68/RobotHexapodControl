#include "cmdServo.hpp"
#include "communication.hpp"

Servo::Servo(int id) : a_id{id} {
    std::cout << "Initialisation d'un servo d'id " << a_id << std::endl;
    Communication::openUART();
}

void Servo::READ_id() { // doit retourner cmdValue et parmts
    Communication& servo=Communication::Instance(); // Ouverture de la communication si elle a pas déjà été ouverte

    uint8_t cmdValue{0x0E};
    int cmdLen {6};
    servo.COM(a_id, cmdValue, cmdLen);
}
 
void Servo::WRITE_Servo_Angle(float angle, float time) { // doit déplacer le servo à l'angle donnée pour la vitesse donnée
    // L'angle est en degrés et le temps en secondes
    Communication& servo=Communication::Instance(); // Ouverture de la communication si elle a pas déjà été ouverte

    if (angle > 240.0)
        angle = 240.0;
    else if (angle < 0.0)
        angle = 0.0;
    float valueAngleF = angle / 0.24;
    unsigned short valueAngleUs = (unsigned short)valueAngleF;
    unsigned char lsbAngle = (uint8_t)(valueAngleUs & (uint16_t)0x00FF);
    unsigned char msbAngle = (uint8_t)((valueAngleUs & (uint16_t)0xFF00) >> 8);

    if (angle > 3.0)
        angle = 3.0;
    else if (angle < 0.0)
        angle = 0.0;
    float valueTimeF = time * 1000;
    unsigned short valueTimeUs = (unsigned short)valueTimeF;
    unsigned char lsbTime = (uint8_t)(valueTimeUs & (uint16_t)0x00FF);
    unsigned char msbTime = (uint8_t)((valueTimeUs & (uint16_t)0xFF00) >> 8);

    int parametersLen {4};
    uint8_t parameters[parametersLen] = {msbAngle,lsbAngle,msbTime,lsbTime};
    uint8_t cmdValue{0x0E};
    int cmdLen{10};

    servo.COM(a_id, cmdValue, cmdLen, parameters, parametersLen);
}