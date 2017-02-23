#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
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
