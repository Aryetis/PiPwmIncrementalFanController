# PiPwmIncrementalFanController
Yet another simple c program to control the fan of your raspberry pi

Just wanted to make a quick program to control the speed of my raspberry pi's fan using incremental steps instead of a simple on and off switch or a "dynamic method". Not that the dynamic solution provided by @Enchufa2 at https://gist.github.com/Enchufa2/4bde3bab84eebedcc88e is bad or anything. It just doesn't suit my needs because the little WINGONEER DC 5V 0,2A fan I'm using is not quite happy with this method. It produced Lots of bad resonance, vibrations and such. 

So that's why I encourage everyone to try both the dynamic method and this incremental method, find the right values for your fan using calibrationTool.c (mine were 930/964/980/1024) and have fun (silently). Tweak the code to your convenience, it shouldn't be that hard to understand even for non developers. 

Short tutorial on how to use the program:

1/ wire the PNP transistor as told by one of the many tutorial out there

2/ get the files from the git

3/ Compile calibrationTool.c using : gcc -Wall -o fanControl fanControl.c -lwiringPi -lpthread calibrationTool.c

4/ then you use the calibrationTool executable to determine what speed settings are best suited for your fan (speeds range from 0 to 1024, no point going higher than than, and mine won't even start below 880),

5/ then you modify the fanModeList[] array in fanControl.c accordingly to your desired speeds and temperature settings.

6/ Compile fanControl.c : gcc -Wall -o fanControl fanControl.c -lwiringPi -lpthread fanControl.c

7/ Login as su, and edit its crontab so everytime the raspberry will boot it will automatically launch the fanControl program. To do so, type "crontab -e" in a bash and then at the bottom of the file, add : @reboot [PATH_TO_SOME_FANCONTROL_PROGRAM_FOLDER]/fanControl
