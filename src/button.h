#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SHORT_PRESS_TIME_MS (10)
#define LONG_PRESS_TIME_MS  (2000)
#define PRESS_TIMEOUT_MS    (10000)

typedef enum{
    PRESSED = 0,
    RELEASED,
    /* */
    BUTTON_STATE_MAX
} button_state_t;


typedef struct
{
    void (*ShortPressCallback)(void);
    void (*LongPressCallback)(void);
    button_state_t (*Read)(void);
    uint32_t pressCount;
    button_state_t lastState;
    button_state_t currentState;
}button_base;

void Button_Scan(button_base *button); //should be called every 1ms


#ifdef __cplusplus
}
#endif


#endif // BUTTON_H
