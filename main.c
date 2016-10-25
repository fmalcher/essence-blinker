#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << PB4);
    while(1){
        blink(PB4);
    } 
    
    return 0;
}

void blink(uint8_t pin) {
    int delay = 50;
    PORTB ^= (1 << pin);
    _delay_ms(delay);
}
