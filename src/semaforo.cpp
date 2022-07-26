#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaforos.h>
#include <vector>

#define ledPin SEMAFORO_1_VERDE(2)
// P0-P7 is 0-7 works through pins 29
// see pin connections

typedef struct SemaforoState
{
    int minTime;
    int active;
} SemaforoState;

typedef struct SemaforoVias
{
    SemaforoState principal[7];
    SemaforoState auxiliar[7];
} SemaforoVias;

void start_semaforo()
{

    SemaforoVias semaforoVias;
    int numStates = 6;
    semaforoVias.principal[0].active = SEMAFORO_1_VERMELHO(2);
    semaforoVias.principal[0].minTime = 5000;
    semaforoVias.principal[1].active = SEMAFORO_1_VERDE(2);
    semaforoVias.principal[1].minTime = 20000;
    semaforoVias.principal[2].active = SEMAFORO_1_AMARELO(2);
    semaforoVias.principal[2].minTime = 3000;
    semaforoVias.principal[3].active = SEMAFORO_1_VERMELHO(2);
    semaforoVias.principal[3].minTime = 5000;
    semaforoVias.principal[4].active = SEMAFORO_1_VERMELHO(2);
    semaforoVias.principal[4].minTime = 5000;
    semaforoVias.principal[5].active = SEMAFORO_1_VERMELHO(2);
    semaforoVias.principal[5].minTime = 5000;
    semaforoVias.principal[6].active = SEMAFORO_1_AMARELO(2);
    semaforoVias.principal[6].minTime = 3000;

    if (wiringPiSetup() == -1)
        exit(1);
    for (int i = 0; i < 6; i++)
    {
        pinMode(semaforoVias.principal[i].active, OUTPUT);
    }
    int i = 0;
    while (1)
    {
        if (i > 6)
            i = 0;
        digitalWrite(semaforoVias.principal[i % numStates].active, HIGH);
        delay(semaforoVias.principal[i % numStates].minTime);
        digitalWrite(semaforoVias.principal[i % numStates].active, LOW);
        printf("blink");
        i++;
    }
}
