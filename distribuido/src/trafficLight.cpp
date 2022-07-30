#include <wiringPi.h>
#include <stdlib.h>
#include <unistd.h>
#include <TrafficLight.hpp>
#include <vector>
#include <json.hpp>
#include <iostream>
#include <chrono>

using json = nlohmann::json;

int currentState = 0;
int buttonp1 = 0;

TrafficLight::TrafficLight(json trafficLightInputs, json buttons)
{

    if (wiringPiSetup() == -1)
        exit(1);
    buttonp1 = buttons[0]["wiringPin"];
    button_pedrestre_2 = buttons[1]["wiringPin"];

    std::cout << button_pedrestre_1 << '\n';
    // vermelho total
    trafficLightVias.principal[0].active = trafficLightInputs[2]["wiringPin"];
    trafficLightVias.auxiliar[0].active = trafficLightInputs[5]["wiringPin"];
    trafficLightVias.principal[0].minTime = 1000;
    trafficLightVias.principal[0].maxTime = 1000;

    trafficLightVias.principal[1].active = trafficLightInputs[0]["wiringPin"];
    trafficLightVias.auxiliar[1].active = trafficLightInputs[5]["wiringPin"];
    trafficLightVias.principal[1].minTime = 10000;
    trafficLightVias.principal[1].maxTime = 20000;

    trafficLightVias.principal[2].active = trafficLightInputs[1]["wiringPin"];
    trafficLightVias.auxiliar[2].active = trafficLightInputs[5]["wiringPin"];
    trafficLightVias.principal[2].minTime = 3000;
    trafficLightVias.principal[2].maxTime = 3000;

    // vermelho total
    trafficLightVias.principal[3].active = trafficLightInputs[2]["wiringPin"];
    trafficLightVias.auxiliar[3].active = trafficLightInputs[5]["wiringPin"];
    trafficLightVias.principal[3].minTime = 1000;
    trafficLightVias.principal[3].maxTime = 1000;

    trafficLightVias.principal[4].active = trafficLightInputs[2]["wiringPin"];
    trafficLightVias.auxiliar[4].active = trafficLightInputs[3]["wiringPin"];
    trafficLightVias.principal[4].minTime = 5000;
    trafficLightVias.principal[4].maxTime = 10000;

    trafficLightVias.principal[5].active = trafficLightInputs[2]["wiringPin"];
    trafficLightVias.auxiliar[5].active = trafficLightInputs[4]["wiringPin"];
    trafficLightVias.principal[5].minTime = 5000;
    trafficLightVias.principal[5].maxTime = 10000;

    trafficLightVias.principal[6].active = trafficLightInputs[1]["wiringPin"];
    trafficLightVias.auxiliar[6].active = trafficLightInputs[4]["wiringPin"];
    trafficLightVias.principal[6].minTime = 3000;
    trafficLightVias.principal[6].maxTime = 3000;

    for (json::iterator it = trafficLightInputs.begin(); it != trafficLightInputs.end(); it++)
    {
        pinMode(it.value()["wiringPin"], OUTPUT);
        pullUpDnControl(it.value()["wiringPin"], PUD_UP);
        digitalWrite(it.value()["wiringPin"], LOW);

        std::cout << it.value()["wiringPin"] << '\n';
    }

    for (json::iterator it = buttons.begin(); it != buttons.end(); it++)
    {
        pinMode(it.value()["wiringPin"], INPUT);
        pullUpDnControl(it.value()["wiringPin"], PUD_DOWN);

        std::cout << it.value()["wiringPin"] << '\n';
    }
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
        std::cout << "PRESSED" << currentState << '\n';
        wasPressed = 1;
    }
}

int passedMinTime = 0;

void TrafficLight::start()
{

    wiringPiISR(buttonp1, INT_EDGE_FALLING, &handlePedestrianButton1);

    while (1)
    {
        std::cout << "INICIO WHILE" << '\n';
        if (currentState > 5)
            currentState = 0;

        digitalWrite(trafficLightVias.principal[currentState].active, HIGH);
        digitalWrite(trafficLightVias.auxiliar[currentState].active, HIGH);
        delay(trafficLightVias.principal[currentState].maxTime);
        digitalWrite(trafficLightVias.principal[currentState].active, LOW);
        digitalWrite(trafficLightVias.auxiliar[currentState].active, LOW);
        currentState++;
    }
}
