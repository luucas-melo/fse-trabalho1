#include <string>
#include <json.hpp>

#define SEMAFORO_1_VERDE(cruzamento) (cruzamento == 1 ? 31 : 8)     // GPIO 1 & GPIO 2
#define SEMAFORO_1_AMARELO(cruzamento) (cruzamento == 1 ? 25 : 9)   // GPIO 26 & GPIO 3
#define SEMAFORO_1_VERMELHO(cruzamento) (cruzamento == 1 ? 29 : 14) // GPIO 21 & GPIO 11
#define SEMAFORO_2_VERDE(cruzamento) (cruzamento == 1 ? 28 : 30)    // GPIO 20 & GPIO 0
#define SEMAFORO_2_AMARELO(cruzamento) (cruzamento == 1 ? 27 : 21)  // GPIO 16 & GPIO 05
#define SEMAFORO_2_VERMELHO(cruzamento) (cruzamento == 1 ? 26 : 22) // GPIO 12 & GPIO 06

typedef struct TrafficLightState
{
    int minTime;
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
    TrafficLight(json inputs);
    std::string getName();
    std::string getVia();
    int getWiringPin();
    void startTrafficLights();
    int getTrafficLightState[6][2];

private:
    std::string name;
    std::string via;
    int wiringPin;
    int trafficLightState[6][2];
};
