#include "gpio.hpp"
#include "led.hpp"

int main() {
    led<gpio_a, 5> led;
    
    while(true) {
        led.turn_on();
        led.turn_off();
    }

    return 0;
}
