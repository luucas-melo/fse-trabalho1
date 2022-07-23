#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaforos.h>
#include <vector>

#define ledPin SEMAFORO_1_VERDE(2)
// P0-P7 is 0-7 works through pins 29
// see pin connections

void start_semaforo()
{

    if (wiringPiSetup() == -1)
        exit(1);
    pinMode(ledPin, OUTPUT);
    while (1)
    {
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
        digitalWrite(ledPin, HIGH);
        printf("blink");
    }
}
