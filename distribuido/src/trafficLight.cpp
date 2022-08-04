#include <wiringPi.h>
#include <stdlib.h>
#include <unistd.h>
#include <TrafficLight.hpp>
#include <vector>
#include <json.hpp>
#include <iostream>
#include <chrono>

using json = nlohmann::json;

int buttonp1 = 0;

typedef struct TrafficLightState
{
    int minTime;
    int maxTime;
    int active;
} TrafficLightState;

typedef struct TrafficLightVias
{
    TrafficLightState principal[9];
    TrafficLightState auxiliar[9];
} TrafficLightVias;

TrafficLightVias trafficLightVias;

TrafficLight::TrafficLight(json trafficLightInputs, json buttons)
{
    trafficLightInputs_ = trafficLightInputs;
    if (wiringPiSetup() == -1)
        exit(1);

    buttonp1 = buttons[0]["wiringPin"];
    button_pedrestre_2 = buttons[1]["wiringPin"];

    std::cout << button_pedrestre_1 << '\n';
    // vermelho total
    trafficLightVias.principal[0].active = trafficLightInputs[2]["wiringPin"]; // red
    trafficLightVias.auxiliar[0].active = trafficLightInputs[5]["wiringPin"];  // red
    trafficLightVias.principal[0].minTime = 1000;
    trafficLightVias.principal[0].maxTime = 1000;

    trafficLightVias.principal[1].active = trafficLightInputs[0]["wiringPin"]; // green
    trafficLightVias.auxiliar[1].active = trafficLightInputs[5]["wiringPin"];  // red
    trafficLightVias.principal[1].minTime = 10000;
    trafficLightVias.principal[1].maxTime = 20000;

    trafficLightVias.principal[2].active = trafficLightInputs[1]["wiringPin"]; // yellow
    trafficLightVias.auxiliar[2].active = trafficLightInputs[5]["wiringPin"];  // red
    trafficLightVias.principal[2].minTime = 3000;
    trafficLightVias.principal[2].maxTime = 3000;

    // vermelho total
    trafficLightVias.principal[3].active = trafficLightInputs[2]["wiringPin"]; // red
    trafficLightVias.auxiliar[3].active = trafficLightInputs[5]["wiringPin"];  // red
    trafficLightVias.principal[3].minTime = 1000;
    trafficLightVias.principal[3].maxTime = 1000;

    trafficLightVias.principal[4].active = trafficLightInputs[2]["wiringPin"]; // red
    trafficLightVias.auxiliar[4].active = trafficLightInputs[3]["wiringPin"];  // green
    trafficLightVias.principal[4].minTime = 5000;
    trafficLightVias.principal[4].maxTime = 10000;

    trafficLightVias.principal[5].active = trafficLightInputs[2]["wiringPin"]; // red
    trafficLightVias.auxiliar[5].active = trafficLightInputs[4]["wiringPin"];  // yellow
    trafficLightVias.principal[5].minTime = 5000;
    trafficLightVias.principal[5].maxTime = 10000;

    // nightMode
    trafficLightVias.principal[7].active = trafficLightInputs[1]["wiringPin"];
    trafficLightVias.auxiliar[7].active = trafficLightInputs[4]["wiringPin"];
    trafficLightVias.principal[7].minTime = 1500;
    trafficLightVias.principal[7].maxTime = 1500;

    // nightMode
    trafficLightVias.principal[8].active = trafficLightInputs[0]["wiringPin"];
    trafficLightVias.auxiliar[8].active = trafficLightInputs[3]["wiringPin"];
    trafficLightVias.principal[8].minTime = 1500;
    trafficLightVias.principal[8].maxTime = 1500;

    for (json::iterator it = trafficLightInputs_.begin(); it != trafficLightInputs_.end(); it++)
    {
        pinMode(it.value()["wiringPin"], OUTPUT);
        pullUpDnControl(it.value()["wiringPin"], PUD_UP);

        std::cout << it.value()["wiringPin"] << '\n';
    }
    resetLights();
}

int waitedMin = 0;
int pressedPedestrianButton = 0;

int timeWaited = 0;

unsigned short int isPressed(unsigned short int button)
{
    static struct timespec lastCall;
    struct timespec thisCall;
    float timeDiff;

    clock_gettime(CLOCK_REALTIME, &thisCall);
    timeDiff = (thisCall.tv_sec + thisCall.tv_nsec / 1E9 - lastCall.tv_sec - lastCall.tv_nsec / 1E9) * 5;
    lastCall = thisCall;

    return timeDiff > 1 ? 1 : 0;
}

int wasPressed = 0;
void handlePedestrianButton1()
{

    if (isPressed(buttonp1))
    {
        std::cout << "PRESSED" << '\n';
        wasPressed = 1;
    }
}

int passedMinTime = 0;

void TrafficLight::start()
{

    wiringPiISR(buttonp1, INT_EDGE_FALLING, &handlePedestrianButton1);

    while (1)
    {
        if (this->currentState > 5 && this->currentState != 7 && this->currentState != 8)
            this->currentState = 0;

        std::cout << "CURRENT STATE " << this->currentState << '\n';

        digitalWrite(trafficLightVias.principal[this->currentState].active, HIGH);
        digitalWrite(trafficLightVias.auxiliar[this->currentState].active, HIGH);
        delay(trafficLightVias.principal[this->currentState].maxTime);
        digitalWrite(trafficLightVias.principal[this->currentState].active, LOW);
        digitalWrite(trafficLightVias.auxiliar[this->currentState].active, LOW);

        if (this->currentState <= 5)
            this->currentState++;
    }
}

void TrafficLight::setNightMode(json mode)
{
    resetLights();
    if (mode == "on")
        this->currentState = 7;
    else
    {
        this->currentState = 0;
    }
}

void TrafficLight::setEmergencyMode(json mode)
{
    resetLights();
    if (mode == "on")
        this->currentState = 8;
    else
    {
        this->currentState = 0;
    }
}

void TrafficLight::setStandardMode()
{
    resetLights();
    this->currentState = 0;
}

void TrafficLight::resetLights()
{

    for (json::iterator it = trafficLightInputs_.begin(); it != trafficLightInputs_.end(); it++)
    {
        digitalWrite(it.value()["wiringPin"], LOW);

        std::cout << it.value()["wiringPin"] << '\n';
    }
}