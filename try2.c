/*
 Change the Intensity of LED using PWM on Raspberry Pi
 Updated to use pigpio library
 */

#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>

const int PWM_pin = 18;   /* GPIO18 as per BCM */

int main (void)
{
    int intensity;

    if (gpioInitialise() < 0)  /* Initialize pigpio library */
    {
        fprintf(stderr, "pigpio initialization failed\n");
        return 1;
    }

    gpioSetMode(PWM_pin, PI_OUTPUT); /* set PWM pin as output */
    gpioSetPWMrange(PWM_pin, 255);   /* Set PWM range to 0-255 for smooth fading */

    while (1)
    {
        for (intensity = 0; intensity < 256; ++intensity)
        {
            gpioPWM(PWM_pin, intensity); /* set PWM duty cycle */
            gpioDelay(1000);             /* delay of 1 ms */
        }

        for (intensity = 255; intensity >= 0; --intensity)
        {
            gpioPWM(PWM_pin, intensity);
            gpioDelay(1000);             /* delay of 1 ms */
        }
    }

    gpioTerminate();  /* Clean up on exit */
    return 0;
}

