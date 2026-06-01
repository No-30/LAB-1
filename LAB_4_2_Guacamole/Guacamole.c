#include "Guacamole.h"
#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>
#include <stdlib.h>
#include <nrfx_rtc.h>
#include <nrfx_systick.h>
#include <nrf_gpio.h>
#include <stdio.h>
#include <nrfx_gpiote.h>
#include <nrf_gpiote.h>
#include <math.h>

// Instans för UART
nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);
// Instans för RTC
const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);
// Array med LED-pin-nummer
int LEDArr[ARR_LENGTH] = { LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN };
// Array med knapp-pin-nummer
int ButtonArr[ARR_LENGTH] = { BUTTON1_PIN, BUTTON2_PIN, BUTTON3_PIN, BUTTON4_PIN };
// Håller nuvarande tillstånd för varje LED (0/1)
int LEDState[ARR_LENGTH] = { LED_OFF, LED_OFF, LED_OFF, LED_OFF };

// Spelstatistik
int lives = 5;   // Antal liv
int hits = 0;    // Antal träffar
int score = 0;   // Poäng

// Buffrar för UART/strängformattering
char uarteBuffer;
char sprintfBuffer[STRING_LENGTH];
char string[STRING_LENGTH];
int rtcTime; // Värde från RTC som används som seed

// Volatila flaggor (kan ändras i ISR eller andra samtidiga sammanhang)
volatile int lastButtonPressed = -1;
volatile bool buttonEventFlag = false;
volatile bool hitsEvent = false;  // Sätts när en träff inträffat
volatile bool livesEvent = false; // Sätts när liv ändrats

// Skriver en sträng till UART
void uarte_write(char* data)
{
    nrfx_uarte_tx(&instance, data, strlen(data), 0);  // Skicka data via UART
}

// Växla ett LED:s tillstånd och uppdatera fysisk pinne
void toggleLED(int led)
{
    LEDState[led] = (LEDState[led] + 1) % 2;  // Växla mellan 0 och 1
    nrf_gpio_pin_write(LEDArr[led], LEDState[led]);  // Sätt pinnen enligt nytt tillstånd
}

// Huvudloopen för spelet. Körs så länge "alive" är sant
void game(int alive) 
{
    float booster;
    int lit, rngNum, rngTime;
    int counter = 0;
    int waittime;
    int consHit = 0; // Antal på varandra följande träffar

    while (alive)
    {
        // Beräkna aktuell booster och hur länge LED ska lysa
        booster = boost(consHit, &lives);
        lit = timeLit(hits);

        // Beräkna en waittime som varierar något med counter för dynamik
        if(counter < 60)
            waittime = cos((float)counter/40.0)*1000;
        else
            waittime = 60;
        // Slumpa vilken LED som tänds
        rngNum = rand() % 4;
        // Beräkna en slumpad väntetid med viss spridning
        rngTime = rand() % waittime*1/4 + waittime*3/4;

        // Tänd vald LED
        nrf_gpio_pin_write(LEDArr[rngNum], LED_ON);
        counter++;

        // Vänta på knapptryck upp till "lit" millisekunder
        int buttonId = timedButtonPress(lit);

        // CASE 1: Korrekt knapp
        if (buttonId == rngNum)
        {
            hits++;
            consHit++;
            hitsEvent = true; 
            score += (int)(10 * booster); // Lägg till poäng med booster
        }
        // CASE 2: Fel knapp
        else if (buttonId != -1 && buttonId != rngNum)
        {
            lives--;
            livesEvent = true;
            consHit = 0;    // Återställ combo
            booster = 1;    // Återställ booster lokalt
        }
        // CASE 3: Ingen knapp trycktes i tid
        else if (buttonId == -1)
        {
            lives--;
            livesEvent = true;
            consHit = 0;
            booster = 1;
        }

        // Släck LED efter försöket
        nrf_gpio_pin_write(LEDArr[rngNum], LED_OFF);

        // Avsluta spelet om inga liv kvar
        if (lives <= 0)
            alive = 0;

        // Vänta en stund innan nästa runda
        delay(rngTime, 'm');
    }
}

// RTC-interrupt handler: körs när compare0 inträffar
void rtc_handler(nrfx_rtc_int_type_t type)
{
    if (type == NRFX_RTC_INT_COMPARE0)
    {
        uarte_write("\n\r[RTC] interrupt fired\n\r");  // Debugutskrift

        // Om poäng eller liv har ändrats, skriv ut status via UART
        if (hitsEvent || livesEvent)
        {
            status(score, hits, lives);
            hitsEvent = false;
            livesEvent = false;
        }

        // Ställ in nästa jämförelseintervall (32 ticks framåt)
        uint32_t now = nrfx_rtc_counter_get(&rtc_instance);
        nrfx_rtc_cc_set(&rtc_instance, 0, now + 32, true);
    }
}

// Beräkna hur många millisekunder en LED ska lysa baserat på antal träffar
int timeLit(int hits)
{
    int lit = 1000 - (hits * 15); // Kortare tid ju fler träffar

    if(lit <= 75)
    {
        lit = 75; // Minimigräns
        return lit;
    }
    return lit;
}

// Beräkna booster (poängmultiplikator). Om booster når max kan spelaren få extra liv.
float boost(int hits, int *lives)
{
    float booster = 1 + (hits * 0.25);

    if(booster > 5)
    {
        booster = 5;
        if(lives < 5)
            (*lives)++; // Ge extra liv om möjligt
    }
    return booster;  
}

// Skriv ut aktuell status via UART (färger används om terminal stöder det)
void status(int score, int hits, int lives)
{
    sprintf(sprintfBuffer, "\n\r"COLOR_GREEN"Score: %d"COLOR_RESET, score);
    uarte_write(sprintfBuffer);
    sprintf(sprintfBuffer, "\n\r"COLOR_YELLOW"Hits: %d"COLOR_RESET, hits);
    uarte_write(sprintfBuffer); 
    sprintf(sprintfBuffer, "\n\r"COLOR_RED"Lives: %d\n\r"COLOR_RESET, lives);
    uarte_write(sprintfBuffer);
}

// Initiera systick för fördröjningar
void initSystick()
{
    nrfx_systick_init();  // Initiera systick
}

// Initiera RTC: default-konfiguration och aktivera compare-interrupt
void initRTC()
{
    nrfx_rtc_config_t config = NRFX_RTC_DEFAULT_CONFIG;

    nrfx_err_t err = nrfx_rtc_init(&rtc_instance, &config, rtc_handler);

    NVIC_EnableIRQ(RTC0_IRQn); // Aktivera RTC0-IRQ i NVIC

    uint32_t now = nrfx_rtc_counter_get(&rtc_instance);
    nrfx_rtc_cc_set(&rtc_instance, 0, now + 32, true); // Sätt första compare

    nrfx_rtc_enable(&rtc_instance); // Starta RTC
}

// Initiera UART med standardinställningar
void initUART()
{
    const nrfx_uarte_config_t configu = NRFX_UARTE_DEFAULT_CONFIG(UART_TX, UART_RX);
    nrfx_err_t erru = nrfx_uarte_init(&instance, &configu, NULL);  // Initiera UART
    if (erru != 0){
        // Här kan felhantering implementeras vid behov
    }
}

// Konfigurera alla knappar som ingångar med pullup
void confButtons()
{
    for(int i = 0; i < ARR_LENGTH; i++)
    {
        nrf_gpio_cfg_input(ButtonArr[i], NRF_GPIO_PIN_PULLUP);  // Pullup så knapp läser aktiv låg
    }
}

// Konfigurera LED-pinnar som utgångar och sätt initialt tillstånd
void confLEDs()
{
    for(int i = 0; i < ARR_LENGTH; i++)
    {
        nrf_gpio_cfg_output(LEDArr[i]);  // Sätt som utgång
        nrf_gpio_pin_write(LEDArr[i], LEDState[i]);  // Sätt initialt värde
    }
}

// Enkel delay-funktion som tar tid och en enhetskod ('s','t','m')
void delay(int time, char unit)//case för ms s
{
    switch (unit)
    {
    case 's': // sekunder
        time *= 1000;  // Konvertera till millisekunder
        break;
    
    case 't': // tiondels sekund
        time *= 100;  // Konvertera till millisekunder
        break;
    
    
    case 'm': // millisekund
        time *= 1;  // Redan millisekunder
        break;
    
    default:
        break;
    }
    nrfx_systick_delay_ms(time);  // Fördröj med angiven tid
}

// Polling-funktion som väntar upp till timeout_ms på knapptryck
// Returnerar index på knapp eller -1 om timeout
int timedButtonPress(int timeout_ms)
{
    int elapsed = 0;

    while (elapsed < timeout_ms)
    {
        for (int i = 0; i < ARR_LENGTH; i++)
        {
            if (!nrf_gpio_pin_read(ButtonArr[i])) // Aktiv låg
            {
                // Vänta tills knapp släpps (enkel debouncing)
                while (!nrf_gpio_pin_read(ButtonArr[i]))
                    nrfx_systick_delay_ms(20);

                return i;  // knapp tryckt
            }
        }

        nrfx_systick_delay_ms(10);
        elapsed += 10;
    }

    return -1;  // ingen knapp tryckt
}

// Blocking: vänta tills en specifik knapp trycks ned och släpps
void waitForButton(int button)
{
    int whileloop = 1;
    while (whileloop)
    {
        if (!nrf_gpio_pin_read(ButtonArr[button]))  // Om knapp nedtryckt
        {
            while (!nrf_gpio_pin_read(ButtonArr[button]))  // Vänta tills den släpps
            {
                delay(50, 'm');
                whileloop = 0;  // Avsluta yttre loop efter släpp
            }
        }
        delay(50, 'm');  // Kort paus för att undvika busy-wait
    }
}

// Initiera all hårdvara och skriv ut startmeddelanden, vänta på startknapp
void initAll_Mod()
{
    confButtons();
    initSystick();
    initUART();
    initRTC();

    sprintf(string,
        "\n\r"COLOR_PURPLE"==============================================================\n\r"
        " Press the buttons glowing purple to add to your total score\n\r"
        " Avoid pressing non glowing buttons to avoid losing lives\n\r"
        "=============================================================="COLOR_RESET);
    uarte_write(string);
    
    sprintf(sprintfBuffer, "\n\rPress button 1 to start");
    uarte_write(sprintfBuffer);

    // Vänta på användaren att trycka på knapp 1 för att starta
    waitForButton(BUTTON1);

    // Använd RTC-värde som seed för rand()
    rtcTime = nrfx_rtc_counter_get(&rtc_instance);
    srand(rtcTime);

    confLEDs();

    // Startup LED-animation (två varv över alla LED)
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < ARR_LENGTH; j++)
        {
            toggleLED(j);
            delay(50, 'm');
        }
    }

    sprintf(sprintfBuffer, "\n\rGame Started\n\r");
    uarte_write(sprintfBuffer);
}

// Huvudentré för spelet: initiera och kör game
void guacamole(void)
{
    initAll_Mod();

    int alive = 1;
    game(alive);

    sprintf(sprintfBuffer, "\n\rGame Over :(");
    uarte_write(sprintfBuffer);
}