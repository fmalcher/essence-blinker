#include <avr/io.h>
#include <util/delay.h>

uint8_t outL = PB0;
uint8_t outM = PB1;
uint8_t outR = PB2;

uint8_t inL = PB3;
uint8_t inR = PB4;


uint8_t leftOn = 0;
uint8_t rightOn = 0;

int main(void) {    
    DDRB |= (1 << outL);
    DDRB |= (1 << outM);
    DDRB |= (1 << outR);

    DDRB &= ~(1 << inL);
    PORTB |= (1 << inL); // pull-up
    DDRB &= ~(1 << inR);
    PORTB |= (1 << inR); // pull-up



    // middle on
    PORTB |= (1 << outM);


    while(1){
        if(!(PINB & (1 << inL))) {
            if(!leftOn) blinkerOff();
            leftOn = 1;
            rightOn = 0;
            blink(outL);
        } else if(!(PINB & (1 << inR))) {
            if(!rightOn) blinkerOff();
            leftOn = 0;
            rightOn = 1;
            blink(outR);
        } else {
            blinkerOff();
        }
    }
    
    return 0;
}

void blink(uint8_t pin) {
    int delay = 50;
    PORTB ^= (1 << pin);
    _delay_ms(delay);
}

void blinkerOff() {
    PORTB &= ~(1 << outL);
    PORTB &= ~(1 << outR);
    leftOn = 0;
    rightOn = 0;
}
