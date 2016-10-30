#include <avr/io.h>
#include <util/delay.h>

int const blinkDelay = 400; // blinker speed

/**************************/

uint8_t leftOn = 0;
uint8_t rightOn = 0;
uint8_t hazardOn = 0;

int main(void) {
    // outputs    
    DDRA |= (1 << PA0);
    DDRA |= (1 << PA1);
    DDRA |= (1 << PA2);
    DDRA |= (1 << PA3);
    DDRA |= (1 << PA4);
    DDRA |= (1 << PA5);
    DDRA |= (1 << PA6);
    DDRA |= (1 << PA7);

    // inputs
    DDRB &= ~(1 << PB4);
    PORTB |= (1 << PB4); // pull-up
    DDRB &= ~(1 << PB5);
    PORTB |= (1 << PB5); // pull-up
    DDRB &= ~(1 << PB6);
    PORTB |= (1 << PB6); // pull-up


    onM();
    offBlinker();

    // self check
    PORTA |= (1 << PA4);
    _delay_ms(100);
    PORTA &= ~(1 << PA4);
    PORTA |= (1 << PA6);
    _delay_ms(100);
    PORTA &= ~(1 << PA6);
    PORTA |= (1 << PA7);
    _delay_ms(100);
    PORTA &= ~(1 << PA7);

    // beep
    int i;
    for(i = 0; i < 20; i++) {
        PORTA |= (1 << PA3);
        _delay_ms(5);
        PORTA &= ~(1 << PA3);
        _delay_ms(5);
     }
    
     for(i = 0; i < 60; i++) {
        PORTA |= (1 << PA3);
        _delay_ms(2);
        PORTA &= ~(1 << PA3);
        _delay_ms(2);
     }

     for(i = 0; i < 110; i++) {
        PORTA |= (1 << PA3);
        _delay_ms(1);
        PORTA &= ~(1 << PA3);
        _delay_ms(1);
     }

     



    while(1){
        if(!(PINB & (1 << PB6))) {
            if(!hazardOn) offBlinker();
            leftOn = 0;
            rightOn = 0;
            hazardOn = 1;
            toggleH();
            _delay_ms(blinkDelay);
            continue;

        } else if(!(PINB & (1 << PB4))) {
            if(!rightOn) offBlinker();
            leftOn = 0;
            rightOn = 1;
            hazardOn = 0;
            toggleR();
            _delay_ms(blinkDelay);

        } else if(!(PINB & (1 << PB5))) {
            if(!leftOn) offBlinker();
            leftOn = 1;
            rightOn = 0;
            hazardOn = 0;            
            toggleL();
            _delay_ms(blinkDelay);

        } else {
            offBlinker();
            _delay_ms(50);
        }
    }

    return 0;
}



// both blinkers off
void offBlinker() {
    PORTA &= ~(1 << PA0);
    PORTA &= ~(1 << PA2);
    PORTA &= ~(1 << PA4);
    PORTA &= ~(1 << PA6);
    PORTA &= ~(1 << PA7);

    leftOn = 0;
    rightOn = 0;
    hazardOn = 0;
}

void onM() {
    PORTA |= (1 << PA1);
    PORTA |= (1 << PA5);
}

void toggleL() {
    PORTA ^= (1 << PA0);
    PORTA ^= (1 << PA4);
}

void toggleR() {
    PORTA ^= (1 << PA2);
    PORTA ^= (1 << PA6);
}

void toggleH() {
    PORTA ^= (1 << PA7);
    PORTA ^= (1 << PA2);
    PORTA ^= (1 << PA0);
    
}



