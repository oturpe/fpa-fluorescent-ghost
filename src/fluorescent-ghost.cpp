// Fluorescent ghost
//
// Firmware for controller for series of relays, with the intent to sequence
// fluorescent lights to make a ghost appear and disappear again.
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

enum MouthState {
    BIG,
    SMALL,
    TINY
};

int main() {
    // Set output pinn
    //    D6 (indicator)
    //    D0, D1 (left and right eye relays)
    //    B0, B1, B2 (tiny, small and big mouth relays)
    //    B3 (outline relay)
    DDRD |= BV(DDD0) | BV(DDD1) | BV(DDD6);
    DDRB |= BV(DDB0) | BV(DDB1) | BV(DDB2) | BV(DDB3);

    // The relay is open when relative output is high. Open all relays initially
    PORTB = 0xff;
    PORTD = 0xff;

    uint16_t counter = 0;
    uint16_t leftEyeCounter = 0;
    uint16_t rightEyeCounter = 0;
    uint16_t outlineCounter = 0;
    bool indicatorLit = 0;
    bool leftEyeLit = false;
    bool rightEyeLit = false;
    bool outlineLit = false;
    MouthState mouthState = TINY;
    uint16_t mouthCounter = 0;

    while(true) {
        counter += 1;
        _delay_ms(LOOP_DELAY);

        if(counter % INDICATOR_HALF_PERIOD == 0) {
            indicatorLit = !indicatorLit;
            setIndicator(indicatorLit);
        }

        if (leftEyeLit && leftEyeCounter == EYE_LEFT_ON_PERIOD) {
            PORTD |= BV(PORTD0);
            leftEyeLit = false;
            leftEyeCounter = 0;
        }
        else if (!leftEyeLit && leftEyeCounter == EYE_LEFT_OFF_PERIOD) {
            PORTD &= ~BV(PORTD0);
            leftEyeLit = true;
            leftEyeCounter = 0;
        }
        leftEyeCounter++;

        if (rightEyeLit && rightEyeCounter == EYE_RIGHT_ON_PERIOD) {
            PORTD |= BV(PORTD1);
            rightEyeLit = false;
            rightEyeCounter = 0;
        }
        else if (!rightEyeLit && rightEyeCounter == EYE_RIGHT_OFF_PERIOD) {
            PORTD &= ~BV(PORTD1);
            rightEyeLit = true;
            rightEyeCounter = 0;
        }
        rightEyeCounter++;

        if (outlineLit && outlineCounter == OUTLINE_ON_PERIOD) {
            PORTB |= BV(PORTB3);
            outlineLit = false;
            outlineCounter = 0;
        }
        else if (!outlineLit && outlineCounter == OUTLINE_OFF_PERIOD) {
            PORTB &= ~BV(PORTB3);
            outlineLit = true;
            outlineCounter = 0;
        }
        outlineCounter++;

        switch (mouthState) {
        case BIG:
            if (mouthCounter == MOUTH_BIG_PERIOD) {
                PORTB |= BV(PORTB2);
                PORTB &= ~BV(PORTB1);
                mouthState = SMALL;
                mouthCounter = 0;
            }
            break;
        case SMALL:
            if (mouthCounter == MOUTH_SMALL_PERIOD) {
                PORTB |= BV(PORTB1);
                PORTB &= ~BV(PORTB0);
                mouthState = TINY;
                mouthCounter = 0;
            }
            break;
        case TINY:
            if (mouthCounter == MOUTH_TINY_PERIOD) {
                PORTB |= BV(PORTB0);
                PORTB &= ~BV(PORTB2);
                mouthState = BIG;
                mouthCounter = 0;
            }
            break;
        }

        mouthCounter++;


    }
}