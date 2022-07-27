#include <wiringPi.h>
#include <stdlib.h>
#include <TrafficLight.hpp>
#include <vector>
#include <json.hpp>
#include <iostream>

using json = nlohmann::json;

TrafficLight::TrafficLight(json trafficLightInputs)
{

    TrafficLightVias trafficLightVias;
    int numStates = 6;

    // vermelho total
    trafficLightVias.principal[0].active = trafficLightInputs[2]["wiringPin"];
    trafficLightVias.auxiliar[0].active = trafficLightInputs[5]["wiringPin"];
    trafficLightVias.principal[0].minTime = 1000;

    trafficLightVias.principal[1].active = trafficLightInputs[0]["wiringPin"];
    trafficLightVias.auxiliar[1].active = trafficLightInputs[5]["wiringPin"];
    trafficLightVias.principal[1].minTime = 20000;

    trafficLightVias.principal[2].active = trafficLightInputs[1]["wiringPin"];
    trafficLightVias.auxiliar[2].active = trafficLightInputs[5]["wiringPin"];
    trafficLightVias.principal[2].minTime = 3000;

    // vermelho total
    trafficLightVias.principal[3].active = trafficLightInputs[2]["wiringPin"];
    trafficLightVias.auxiliar[3].active = trafficLightInputs[5]["wiringPin"];
    trafficLightVias.principal[3].minTime = 1000;

    trafficLightVias.principal[4].active = trafficLightInputs[2]["wiringPin"];
    trafficLightVias.auxiliar[4].active = trafficLightInputs[3]["wiringPin"];
    trafficLightVias.principal[4].minTime = 5000;

    trafficLightVias.principal[5].active = trafficLightInputs[2]["wiringPin"];
    trafficLightVias.auxiliar[5].active = trafficLightInputs[4]["wiringPin"];
    trafficLightVias.principal[5].minTime = 5000;

    trafficLightVias.principal[6].active = trafficLightInputs[1]["wiringPin"];
    trafficLightVias.auxiliar[6].active = trafficLightInputs[4]["wiringPin"];
    trafficLightVias.principal[6].minTime = 3000;

    if (wiringPiSetup() == -1)
        exit(1);

    for (json::iterator it = trafficLightInputs.begin(); it != trafficLightInputs.end(); it++)
    {
        pinMode(it.value()["wiringPin"], OUTPUT);
        digitalWrite(it.value()["wiringPin"], LOW);

        std::cout << it.value()["wiringPin"] << '\n';
    }

    int i = 0;
    while (1)
    {

        if (i > 6)
            i = 0;
        digitalWrite(trafficLightVias.principal[i % numStates].active, HIGH);
        digitalWrite(trafficLightVias.auxiliar[i % numStates].active, HIGH);
        delay(trafficLightVias.principal[i % numStates].minTime);
        digitalWrite(trafficLightVias.principal[i % numStates].active, LOW);
        digitalWrite(trafficLightVias.auxiliar[i % numStates].active, LOW);
        printf("blink");
        i++;
    }
}
