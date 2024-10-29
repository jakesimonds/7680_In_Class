/*
 Change the Intensity of LED using PWM on Raspberry Pi
 Updated to use pigpio library
 */
#include <signal.h>
#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
const int LED_pin = 12;
const int PWM_pin = 21;   /* GPIO18 as per BCM */
volatile sig_atomic_t signal_received = 0;

void sigint_handler(int signal){
	signal_received=signal;
}

int main (void)
{
    if(gpioInitialise()==PI_INIT_FAILED){
	printf("FAILURE");
	return 1;
}

    int intensity;

    if (gpioInitialise() < 0)  /* Initialize pigpio library */
    {
        fprintf(stderr, "pigpio initialization failed\n");
        return 1;
    }

    gpioSetMode(PWM_pin, PI_OUTPUT); /* set PWM pin as output */
    signal(SIGINT, sigint_handler);
    gpioSetPWMrange(PWM_pin, 255);   /* Set PWM range to 0-255 for smooth fading */
    gpioSetMode(LED_pin, PI_OUTPUT);
    while (!signal_received)
    {
        for (intensity = 0; intensity < 256; ++intensity)
        {
            gpioPWM(PWM_pin, intensity); /* set PWM duty cycle */
            gpioDelay(10000);             /* delay of 1 ms */
	    if(intensity>0){
		gpioWrite(LED_pin, PI_HIGH);
	    } else {gpioWrite(LED_pin, PI_LOW);}
        }

        for (intensity = 255; intensity >= 0; --intensity)
        {
		if(intensity>0){
                	gpioWrite(LED_pin, PI_HIGH);
            } else {gpioWrite(LED_pin, PI_LOW);}

            gpioPWM(PWM_pin, intensity);
            gpioDelay(10000);             /* delay of 1 ms */
        }
	time_sleep(2);
    }
    gpioSetMode(PWM_pin, PI_INPUT);
    gpioSetMode(LED_pin, PI_INPUT);
    gpioTerminate();  /* Clean up on exit */
    return 0;
}

