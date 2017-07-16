CC=gcc
FLAGS=-Wall -lwiringPi -lpthread
EXEC=fanControl
TOOL=calibrationFanTool

all: $(EXEC) $(TOOL)

fanControl: fanControl.c
        $(CC) -o $(EXEC) fanControl.c $(FLAGS)

calibrationFanTool : calibrationFanTool.c
        $(CC) -o $(TOOL) calibrationFanTool.c  $(FLAGS)

clean:
        rm -rf $(EXEC) $(TOOL)

