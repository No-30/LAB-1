#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>


//definierar vilka pinnar som ska användas för att skicka och ta emot data:
#define PIN_TXD 20
#define PIN_RXD 22

//Skapar en driver instance för UARTE:
nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);

//skapar en buffer att ta emot tecken vi läser över UARTE
char uarte_buffer;
#define charArrLength 100

void read_string(char charArr[])
{
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
        nrfx_uarte_tx(&instance, charArr, length, 0);
}

int main(void)
{ 
    char charArr[charArrLength];
    //Vi kör med default settings och anger våra TX- och RX-pinnar:
    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);

    //Initierar UARTE:
    nrfx_err_t errr = nrfx_uarte_init(&instance, &config, NULL);
    if (errr != 0){
        //Här kan vi implementera felhantering, men för stunden håller vi tummarna att allt funkar
    }

    char msg1[] = " \n\r Skriv tecken och tryck sedan enter \n\r";
    nrfx_uarte_tx(&instance, msg1, sizeof(msg1), 0);

    read_string(charArr);
}