/**************************************************************************************

        COMPILE USING : gcc -Wall -o fanControl fanControl.c -lwiringPi -lpthread
                (and add the program to the super user crontab to avoid
                running it manually everytime you reboot your pi)

***************************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>

#include <wiringPi.h>

typedef struct fanMode
{
        int temp;
        int speed;
} fanMode;



// Temperature variables
FILE* tempfile; // file containing tmp value (refreshed by system)
int curTemp; // current Temperature of the rpi in °C
// Refresh rate in second
int refreshRate = 5;
// fan Speed
bool fanStatus = true; // determine is fan is on or off
// fanMode settings (temperature and according speed fan)
fanMode fanModeList[] = {
        {.temp=0, .speed=0},            // don't turn on the fan until temperature hits 70°C
        {.temp=70000, .speed=930},
        {.temp=73000, .speed=964},
        {.temp=75000, .speed=980},
        {.temp=79000, .speed=1024}         // go fullSpeed if we're hitting 79,000°C
                         };
int curFM = 4; // start at fm4, fullspeed



int actualizeTemp()
{
        tempfile = fopen ("/sys/class/thermal/thermal_zone0/temp", "r");
        fscanf (tempfile, "%d", &curTemp);
        fclose (tempfile);
        return curTemp;
}

void displayInfo()
{
        // Display informations (for debug purproses)
        printf("current FanMode: %i \n", curFM);
        printf("Temperature: %i \n", curTemp);
        printf("Fan Speed: %i \n", fanModeList[curFM].speed);
        printf("------------------------ \n");
}



int main()
{
        /**** INIT ****/
        // check if wiringPi loaded correctly
        if (wiringPiSetup () == -1)
        {
                fprintf (stderr, "Unable to setup GPIO: %s\n", strerror (errno)) ;
                return 1 ;
        }
        // set pin control mode for pin 1/pwm/gpio18/fan
        pinMode (1, PWM_OUTPUT) ;
        // set fan at fullspeed by default during the initialization
        pwmWrite(1, 1024);

        /**** MAIN LOOP ****/
        while(1)
        {
                // Actualize the temperature
                actualizeTemp();

                /**********************************
                 *             MAGIKU             *
                 **********************************/

                // Increasing Fan mode (if fan is not already at max && temp reached next FanMode temperature)
                if ( curFM < 4 && curTemp > fanModeList[curFM+1].temp )
                {
                        curFM++;

                        // if fan was off give it a little burst to kick in and change flag status
                        if( !fanStatus )
                        {
                                pwmWrite(1, 1024);
                                fanStatus = true;
                                sleep(1);
                        }
                        // speed up fan accordingly accordingly to new FanMode
                        pwmWrite(1, fanModeList[curFM].speed);
                }
                // Decreasing Fan mode (if fan is not already at min && temp is below current FanMode temperature)
                else if ( curFM > 0 && curTemp < fanModeList[curFM].temp )
                {
                        curFM--;

                        // if fan needs to turn off shutit down and change the fanStatus flag
                        if( curFM <= 0 )
                        { // turn off fan
                                pwmWrite(1, 0);
                                fanStatus = false;
                        }
                        else
                        { // slow down fan accordingly to new FanMode
                                pwmWrite(1, fanModeList[curFM].speed);
                        }
                }

                // Display informations about current fan setting (FanMode, Temperature, FanSpeed)
                // Debug Purposes only
                // displayInfo();

                // Go back to sleep
                sleep(refreshRate);
        }

        /**** SHUTDOWN ****/
        return 0;
}



