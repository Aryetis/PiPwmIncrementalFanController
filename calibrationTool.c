/**************************************************************************************

        COMPILE USING : gcc -Wall -o fanControl fanControl.c -lwiringPi -lpthread
              Use this to program to test mulitple speed value for your fan
              Spot the ones with the less resonance, and use them in fanControl.c

***************************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>

int main()
{
      // check if wiringPi loaded correctly
      if (wiringPiSetup () == -1)
         {
           fprintf (stderr, "Unable to setup GPIO: %s\n", strerror (errno)) ;
           return 1 ;
         }

      pinMode (1, PWM_OUTPUT) ;



        int fanspeed=1024;
        pwmWrite(1, fanspeed);
        printf("Fan now spinning at %i \n", fanspeed);

        while(1)
        {
                scanf("%i", &fanspeed);
                if ( fanspeed >= 0 && fanspeed <= 1024 )
                {
                        pwmWrite(1, fanspeed);
                        printf("Fan now spinning at %i \n", fanspeed);
                }
        }

        return 0;
}
