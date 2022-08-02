#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP

#include <string>
#include <json.hpp>

class TrafficLight
{
    using json = nlohmann::json;

public:
    TrafficLight(json trafficLightInputs, json buttons);
    std::string getName();
    std::string getVia();
    int getWiringPin();
    void startTrafficLights();
    json trafficLightInputs_;
    int button_pedrestre_1;
    int button_pedrestre_2;
    void start();
    void resetLights();
    int currentState = 0;
    void setNightMode();

private:
    std::string name;
    std::string via;
    int wiringPin;
};

#endif