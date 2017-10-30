#include "mbed.h"
#include "motordriver.h"

InterruptIn pb(p25);
Motor m(p21, p22, p23, 1);
Timeout motorTimeout;

void startMotor();
void holdMotor();
void stopMotor();
void reverseMotor();

void startMotor(){
    pb.fall(NULL);
    m.speed(-1);
    motorTimeout.attach(&holdMotor, 2);
}

void holdMotor(){
    m.coast();
    motorTimeout.attach(&reverseMotor, 2);
}

void reverseMotor(){
    m.speed(1);
    motorTimeout.attach(&stopMotor, 1);
}

void stopMotor(){
    m.coast();
    pb.fall(&startMotor);
}

int main(){
    pb.mode(PullUp);
    wait(0.01); // delay for pullup to take effect
    pb.fall(&startMotor);
    
    while(true){
        sleep();
    }
}