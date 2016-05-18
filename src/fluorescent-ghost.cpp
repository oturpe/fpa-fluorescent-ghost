// Fluorescent ghost
//
// Firmware for attiny2313 based ac motor controller. Detects the upright
// position of the motor by rotating shaft contacting a button and afterwards
// waits for the sand in hourglass to move, then rotates the hourglass 180
// degrees again.
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi

#include "Attiny2313Utils.h"

#include "config.h"

#include <avr/io.h>
#include <util/delay.h>

/// \brief Turns the indicator led on of off
///
/// \param lit
///    If led is turned on. Otherwise it is turned off.
void setIndicator(bool lit) {
    if (lit)
        PORTD |= BV(PORTD6);
    else
        PORTD &= ~BV(PORTD6);
}

int main() {
    // Set output pinn
    //    D6 (indicator)
    //    B0, B1 (eye relays)
    DDRD |= BV(DDD6);
    DDRB |= BV(DDB0) | BV(DDB1);

    uint16_t counter = 0;
    uint16_t leftEyeCounter = 0;
    uint16_t rightEyeCounter = 0;
    bool indicatorLit = 0;
    bool leftEyeLit = false;
    bool rightEyeLit = false;

    while(true) {
        counter += 1;
        _delay_ms(LOOP_DELAY);

        if(counter % INDICATOR_HALF_PERIOD == 0) {
            indicatorLit = !indicatorLit;
            setIndicator(indicatorLit);
        }

        if (leftEyeLit && leftEyeCounter == EYE_LEFT_ON_PERIOD) {
            PORTB |= BV(PORTB0);
            leftEyeLit = false;
            leftEyeCounter = 0;
        }
        else if (!leftEyeLit && leftEyeCounter == EYE_LEFT_OFF_PERIOD) {
            PORTB &= ~BV(PORTB0);
            leftEyeLit = true;
            leftEyeCounter = 0;
        }
        leftEyeCounter++;

        if (rightEyeLit && rightEyeCounter == EYE_RIGHT_ON_PERIOD) {
            PORTB |= BV(PORTB1);
            rightEyeLit = false;
            rightEyeCounter = 0;
        }
        else if (!rightEyeLit && rightEyeCounter == EYE_RIGHT_OFF_PERIOD) {
            PORTB &= ~BV(PORTB1);
            rightEyeLit = true;
            rightEyeCounter = 0;
        }
        rightEyeCounter++;
    }
}