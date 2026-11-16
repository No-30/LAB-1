#ifndef STD_HEADER_H
#define STD_HEADER_H
#define BUTTON_PIN 4
#define BUTTON1_PIN 23
#define BUTTON2_PIN 24
#define BUTTON3_PIN 8
#define BUTTON4_PIN 9
#define BUTTON5_PIN
#define BUTTON6_PIN
#define BUTTON7_PIN
#define BUTTON8_PIN
#define BUTTON9_PIN
#define BUTTON1 0
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3
#define BUTTON5 4
#define BUTTON6 5
#define BUTTON7 6
#define BUTTON8 7
#define BUTTON9 8
#define LED1_PIN 28
#define LED2_PIN 29
#define LED3_PIN 30
#define LED4_PIN 31
#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 4
#define LED6 5
#define LED7 6
#define LED8 7
#define LED9 8
#define UART_TX 20
#define UART_RX 22
#define LED_ON 0
#define LED_OFF 1
#define ARR_LENGTH 4
#define STRING_LENGTH 300

/* --- Color & Strings --- */
#define CLEAR_SCREEN "\033[2J\033[H"
#define COLOR_RED    "\033[31m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_CYAN   "\033[36m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_PURPLE "\033[35m"
#define COLOR_LIGHTBLUE "\033[96m"
#define COLOR_RESET  "\033[0m"
#define BOLD         "\033[1m"

#include <nrfx_gpiote.h>
#include <nrf_gpiote.h>
#include <nrfx_rtc.h>

extern int LEDArr[ARR_LENGTH];
extern int ButtonArr[ARR_LENGTH];
extern int LEDState[ARR_LENGTH];
extern char sprintfBuffer[STRING_LENGTH];
extern char uarteBuffer;
extern char string[STRING_LENGTH];
extern int rtcTime;

void uarte_write(char* data);
void toggleLED(int led);
void game(int alive);
void gpio_button_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
void rtc_handler(nrfx_rtc_int_type_t type);
int timeLit(int hits);
float boost(int hits, int* lives);
void status(int score, int hits, int lives);
void initSystick(void);
void initRTC(void);
void initUART(void);
void confButtons(void);
void confLEDs(void);
void delay(int time, char unit);
int timedButtonPress(int timeout_ms);
void initAll_Mod(void);
void guacamole(void);


#endif //↑ ↑ ↓ ↓ ← → ← → B A (Start)