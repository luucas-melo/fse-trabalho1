#include <string>
#include <json.hpp>

typedef struct TrafficLightState
{
    int minTime;
    int maxTime;
    int active;
} TrafficLightState;

typedef struct TrafficLightVias
{
    TrafficLightState principal[7];
    TrafficLightState auxiliar[7];
} TrafficLightVias;

class TrafficLight
{

    using json = nlohmann::json;

public:
    TrafficLight(json trafficLightInputs, json buttons);
    std::string getName();
    std::string getVia();
    int getWiringPin();
    void startTrafficLights();
    TrafficLightVias trafficLightVias;
    int button_pedrestre_1;
    int button_pedrestre_2;
    void start();

private:
    std::string name;
    std::string via;
    int wiringPin;
};
