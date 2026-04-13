#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_uarte.h>
#include <stdlib.h>


//definierar vilka pinnar som ska användas för att skicka och ta emot data:
#define PIN_TXD 20
#define PIN_RXD 22
#define charArrLength 100

//Skapar en driver instance för UARTE:
nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);

//skapar en buffer att ta emot tecken vi läser över UARTE
char uarte_buffer;
int num;

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
int read_int(char charArr[]){
    read_string(charArr);
    return atoi(charArr);
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
    char msg2[] = " \n\r atoi \n\r";
    nrfx_uarte_tx(&instance, msg2, sizeof(msg2), 0);
    num = read_int(charArr);
    nrfx_uarte_tx(&instance, num, sizeof(num), 0);

}