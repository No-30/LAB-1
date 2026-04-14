#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_systick.h>
#include <nrfx_uarte.h>
#include <stdlib.h>

//definierar vilka pinnar som ska användas för att skicka och ta emot data:
#define PIN_TXD 20
#define PIN_RXD 22
#define charArrLength 10
#define MAXTIME 10

//Skapar en driver instance för UARTE:
nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);

//skapar en buffer att ta emot tecken vi läser över UARTE
char uarte_buffer;
char sprintfBuffer[100];

int read_int()
{
    char charArr[charArrLength];
    int length = charArrLength;
    for(int i = 0; i < length; i++)
    {
        nrfx_uarte_rx (&instance, &uarte_buffer, sizeof(uarte_buffer));
        if (uarte_buffer != '\r')
        {
            charArr[i] = uarte_buffer;
        }
        else
        {
            charArr[i] = '\0';
            length = i;
        }
    }
    return atoi(charArr);
}

void askUser()
{
    int max = MAXTIME;
    int waitTime = -1;
    sprintf(sprintfBuffer, " \n\r Skriv en tid att vänta, max %d sekunder \n\r", max);
    nrfx_uarte_tx(&instance, sprintfBuffer, strlen(sprintfBuffer), 0);

    waitTime = read_int();
    if (waitTime <= max && waitTime >= 0)
    {
        nrfx_systick_delay_ms(waitTime*1000);

        sprintf(sprintfBuffer, "Nu har det gått %d", waitTime);
        nrfx_uarte_tx(&instance, sprintfBuffer, strlen(sprintfBuffer), 0);
    }
    else
    {
        sprintf(sprintfBuffer, "LÄS INSTRUKTIONERNA");
        nrfx_uarte_tx(&instance, sprintfBuffer, strlen(sprintfBuffer), 0);
    }
}

int main(void)
{ 
    nrfx_systick_init();
    //Vi kör med default settings och anger våra TX- och RX-pinnar:
    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);

    //Initierar UARTE:
    nrfx_err_t errr = nrfx_uarte_init(&instance, &config, NULL);
    if (errr != 0){
        //Här kan vi implementera felhantering, men för stunden håller vi tummarna att allt funkar
    }
    while(1)
    {
    askUser();
    nrfx_systick_delay_ms(100);
    }
}