/*
 Change the Intensity of LED using PWM on Raspberry Pi
 Updated to use pigpio library with graceful exit on Ctrl+C
 */

#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

const int PWM_pin = 21;   /* GPIO18 as per BCM */

void handle_sigint(int sig)
{
    /* Stop PWM and terminate pigpio on Ctrl+C */
    gpioPWM(PWM_pin, 0);  // Turn off PWM signal
    gpioTerminate();
    printf("\nGracefully stopped PWM and exited program.\n");
    exit(0);
}

int main (void)
{
    int intensity;

    if (gpioInitialise() < 0)  /* Initialize pigpio library */
    {
        fprintf(stderr, "pigpio initialization failed\n");
        return 1;
    }

    /* Set up signal handler for Ctrl+C */
    signal(SIGINT, handle_sigint);

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

    /* Cleanup and exit on completion, although the program runs indefinitely */
    gpioTerminate();
    return 0;
}

