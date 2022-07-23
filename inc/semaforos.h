#define SEMAFORO_1_VERDE(cruzamento) (cruzamento == 1 ? 31 : 8)     // GPIO 1 & GPIO 2
#define SEMAFORO_1_AMARELO(cruzamento) (cruzamento == 1 ? 25 : 9)   // GPIO 26 & GPIO 3
#define SEMAFORO_1_VERMELHO(cruzamento) (cruzamento == 1 ? 29 : 14) // GPIO 21 & GPIO 11

void start_semaforo();