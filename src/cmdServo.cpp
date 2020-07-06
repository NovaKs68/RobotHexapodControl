#include "cmdServo.hpp"
#include "communication.hpp"

Servo::Servo(int id, int device) : a_id{id}, m_device{device} {
    std::cout << "Initialisation d'un servo d'id " << a_id << std::endl;
    Communication::openUART(0);
}

void Servo::READ_id() { // doit retourner cmdValue et parmts
char const cmdValue = 0x0E;
Communication servo(a_id, m_device);
Communication::openUART(10);
servo.COM(cmdValue);
}

// uint8_t checksum(uint8_t* buf, uint8_t buflen)
// {
// uint16_t cksum = { 0 };

// for (int i = 2; i < buflen - 1; i++) cksum += buf[i];
// buf[buflen - 1] = 0xff - cksum;

// return ~cksum;
// }