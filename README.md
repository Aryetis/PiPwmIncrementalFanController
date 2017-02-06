# PiPwmIncrementalFanController
Yet another simple c program to control the fan of your raspberry pi

Just wanted to make a quick program to control the speed of my raspberry pi's fan using incremental steps instead of a simple on and off switch or a "dynamic method". Not that the dynamic solution provided by @Enchufa2 at https://gist.github.com/Enchufa2/4bde3bab84eebedcc88e is bad or anything. It just doesn't suit my needs because the little WINGONEER DC 5V 0,2A fan I'm using is not quite happy with this method. It produced Lots of bad resonance, vibrations and such. 

So that's why I encourage everyone to try both the dynamic method and this incremental method, find the right values for your fan using calibrationTool.c (mine were 930/964/980/1024) and have fun (silently). Tweak the code to your convenience, it shouldn't be that hard to understand even for non developers. 
