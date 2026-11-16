#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_bsdriver.h>

/* By Daniel Morberg*/

int main(void)
{
	int looper = 0;
	int looper2 = 1;
	int looper3 = 2;
	uint8_t *secret_ptr = &secret;
	uint8_t *keyword_ptr = &keyword;
	uint8_t *goal_ptr = &goal;

	while (looper < goal && looper2 < goal && looper3 < goal)
	{
		looper = looper + inkr1;
		looper2 = looper2 + inkr2;
		looper3 = looper3 + inkr3;
	}
}