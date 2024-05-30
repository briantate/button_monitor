#ifdef TEST

#include "unity.h"

#include "button.h"

bool shortPress = false;
bool longPress = false;
button_state_t pressVal = RELEASED;

button_base myButton;

void ShortPressCallback(void){
    shortPress = true;
    printf("shortPress\r\n");
}

void LongPressCallback(void){
    longPress = true;
    printf("longPress\r\n");
}

button_state_t buttonRead(void){
    return pressVal;
}

void setUp(void)
{
    myButton.ShortPressCallback = ShortPressCallback;
    myButton.LongPressCallback = LongPressCallback;
    myButton.Read = buttonRead;
    myButton.pressCount = 0;
    myButton.lastState = RELEASED;
    myButton.currentState = RELEASED;
    shortPress = false;
    longPress = false;
}

void tearDown(void)
{
    myButton.ShortPressCallback = NULL;
    myButton.LongPressCallback = NULL;
    myButton.Read = NULL;
    myButton.pressCount = 0;
    myButton.lastState = RELEASED;
    myButton.currentState = RELEASED;
    shortPress = false;
    longPress = false;
}

void test_Button_Scan_should_DoNothingIfButtonPressedLessThanShortTime(void)
{
    pressVal = PRESSED;

    for(uint32_t i=0; i<(SHORT_PRESS_TIME_MS-2); i++) 
    {
        Button_Scan(&myButton);
        TEST_ASSERT_FALSE(shortPress);
        TEST_ASSERT_FALSE(longPress);
    }
    
    pressVal = RELEASED;
    Button_Scan(&myButton);// one more press to go over the threshold
    TEST_ASSERT_FALSE(shortPress);     
    TEST_ASSERT_FALSE(longPress);
}

void test_Button_Scan_should_CallShortCallbackIfButtonShortPressed(void)
{
    pressVal = PRESSED;

    for(uint32_t i=0; i<SHORT_PRESS_TIME_MS; i++) 
    {
        Button_Scan(&myButton);
        TEST_ASSERT_FALSE(shortPress);
        TEST_ASSERT_FALSE(longPress);
    }
    
    pressVal = RELEASED;

    Button_Scan(&myButton);// one more press to go over the threshold
    TEST_ASSERT_TRUE(shortPress);
    TEST_ASSERT_FALSE(longPress);
}

void test_Button_Scan_should_CallLongCallbackIfButtonLongPressed(void)
{
    pressVal = PRESSED;

    for(uint32_t i=0; i<LONG_PRESS_TIME_MS; i++) 
    {
        Button_Scan(&myButton);
        TEST_ASSERT_FALSE(shortPress);
        TEST_ASSERT_FALSE(longPress);
    }
    
    pressVal = RELEASED;

    Button_Scan(&myButton); // one more press to go over the threshold
    TEST_ASSERT_FALSE(shortPress);
    TEST_ASSERT_TRUE(longPress);
}

void test_Button_Scan_should_DoNothingIfButtonPressedMoreThanTimeoutTime(void)
{
    pressVal = PRESSED;

    for(uint32_t i=0; i<(PRESS_TIMEOUT_MS); i++) 
    {
        Button_Scan(&myButton);
        TEST_ASSERT_FALSE(shortPress);
        TEST_ASSERT_FALSE(longPress);
    }
    
    pressVal = RELEASED;
    Button_Scan(&myButton);// one more press to go over the threshold
    TEST_ASSERT_FALSE(shortPress);     
    TEST_ASSERT_FALSE(longPress);
}


#endif // TEST

