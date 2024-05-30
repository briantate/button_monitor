#include "button.h"
#include <stdint.h>
#include <string.h>

void Button_Scan(button_base *button){
    button->currentState = button->Read();

    if(button->currentState == PRESSED){
        button->pressCount++;
        if(button->pressCount >= PRESS_TIMEOUT_MS){
            button->pressCount = 0;
        }
    }
    else if(button->currentState == RELEASED){
        if(button->lastState == PRESSED){
            if(button->pressCount < SHORT_PRESS_TIME_MS){
                //debounce - do nothing
            }
            else if (button->pressCount < LONG_PRESS_TIME_MS){
                if(button->ShortPressCallback){
                    button->ShortPressCallback();
                }
            }
            else if (button->pressCount < PRESS_TIMEOUT_MS){
                if(button->LongPressCallback){
                    button->LongPressCallback();
                }
            }
            else{
                //timeout do nothing
            }
        }
        button->pressCount = 0;
    }
    button->lastState = button->currentState;
}