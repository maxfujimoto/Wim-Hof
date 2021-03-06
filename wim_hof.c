#include <stdio.h>
#include <stdbool.h>
#include <alsa/asoundlib.h>
#include <time.h>

// Define Sound Card
#define PCM_DEVICE "default"

// Prompt for breathing metronome, metronome speed, hyperventilation length and output file target.
// Returns options[0] true for on
bool *metro_setup(bool *options)
{
  char usrin[24];
  char sound = 0;
  
  
  while( sound == 0) {
    
    printf("Sound on? [Y/n] ");
    fgets(usrin, 23, stdin);

    if( strlen(usrin) > 2 ||
	sscanf(usrin, "%c", &sound) != 1) {
      sound = 0;
      continue;
    }
    else if ( sound == 'y' ||
	      sound == 'Y' ||
	      sound == '\n') {
      options[0] = 1;
    }
    else if ( sound == 'n' ||
	      sound == 'N') {
      options[0] = 0;
    }
    else {
      sound = 0;
      continue;
    }
  }
  return options;
}

// Prompts for metronome speed
// Stores speed in binary in 2nd and 3rd bit of options bitmap
bool *metro_speed(bool *options)
{
  char usrin[24];
  char speed = 0;
  
  while( speed == 0) {
    
    printf("Metronome speed? [s/M/f] ");
    fgets(usrin, 23, stdin);

    if( strlen(usrin) > 2 ||
	sscanf(usrin, "%c", &speed) != 1) {
      speed = 0;
      continue;
    }
    else if( speed == 'm' ||
	      speed == 'M' ||
	      speed == '\n') {
      options[2] = 1;
    }
    else if( speed == 's' ||
	      speed == 'S') {
    }
    else if( speed == 'f' ||
	     speed == 'F') {
      options[1] = 1;
    }
    else {
      speed = 0;
      continue;
    }
  }
  return options;
}


// Prompt for metro length, default 30 and return MetroLength
int metro_length()
{
  char usrin[24];
  int length = 0;
  int MetroLength;
  
  while( length == 0) {
    
    printf("Hyperventilation duration? [30] ");
    fgets(usrin, 23, stdin);


    if( usrin[0] == '\n'){
      return 30;
    }	
    if( strlen(usrin) > 3 ||
	sscanf(usrin, "%d", &length) != 1) {
      length = 0;
      continue;
    }
    if( length <= 60 &&
	     length >= 15) {
      MetroLength = length;
    }
    else {
      length = 0;
      continue;
    }
  }
  return MetroLength;
}

// Detect a key-press
int key_press()
{
  char usrin[3];

  fgets(usrin, 2, stdin);
  if(usrin[0] == '\n') {
    return 0;
  }
  else if (usrin[0] == 'q' ) {
    return 1;
  }
  return 1;
}

// Stopwatch that returns second value or 0 for failure.
unsigned int timer()
{
  unsigned int timediff = 0;
  time_t start;
  time_t stop;
  
  time(&start);
  printf("press [RETURN] to stop or [q - RETURN] to quit.");
  if(!key_press()) {
    time(&stop);
    timediff = difftime(stop, start);
  }
  return timediff;
}


int main ()
{ 
  bool options[3] = {0,0,0};
  int MetroLength = 0;
  unsigned int BreathHoldVals[10];
  int BreathHolds = 0;

  printf("\n\nWelcome to a terminal based Wim Hof breathing guide.\n\n");

  metro_setup(options);

  if( options[0]) {
    metro_speed(options);
    MetroLength = metro_length();
  }
  else {
    int i;
    for(i = 0; i < 10; ++i, ++BreathHolds) {
      printf("Press [RETURN] to begin the timer or [q - RETURN] to quit.");
      if( !key_press()){
	BreathHoldVals[i] = timer();
      }
      else {
	break;
      }
    }
    for(i = 0; i < BreathHolds; ++i) {
      printf("Breath Hold %d: %d\n", i+1, BreathHoldVals[i]); 
    }
  }
} 
