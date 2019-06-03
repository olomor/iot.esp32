#include <pthread.h>

// ----------------------------------------------------------------------
// globals
// ----------------------------------------------------------------------

int LED_RED = 0;
int LED_YELLOW = 1;
int LED_GREEN = 2;
int LED_WHITE = 3;
int LED_BLUE = 4;
String LED_COLOR[] = { "red", "yellow", "green", "white", "blue" };
int LED_PINOUT[] = { 15, 4, 16, 17, LED_BUILTIN };

pthread_t threads[5];
int thread_count = 0; 

void *threadBlinkLed(void *LED) ;
void blink( int LED ) ;
void ledOff( int LED, int MSEC ) ;
void ledOn( int LED, int MSEC ) ;

// ----------------------------------------------------------------------
// main code
// ----------------------------------------------------------------------
void setup(void) {
  Serial.begin(115200);
  blink( LED_RED );
  blink( LED_YELLOW );
  blink( LED_GREEN );
  blink( LED_WHITE );
  blink( LED_BLUE );
}

void loop(void) {
}

// ----------------------------------------------------------------------
// functions body
// ----------------------------------------------------------------------

void ledOn( int LED, int MSEC ) {
    digitalWrite( LED_PINOUT[LED], HIGH );
    delay(MSEC);
}

void ledOff( int LED, int MSEC ) {
    digitalWrite( LED_PINOUT[LED], LOW );
    delay(MSEC);            
}

void *threadBlinkLed(void *LED){
  int interval;
  pinMode( LED_PINOUT[ (int) LED ], OUTPUT);
  while ( 1==1 ) {
    ledOn( (int) LED, random(10,500) );  
    ledOff( (int) LED, random(10,500) );  
  }
}

void blink( int LED ) {
  String message;
  message = message + "thread " + thread_count + " for blink led " + LED_COLOR[LED] ;
  if ( pthread_create(&threads[thread_count], NULL, threadBlinkLed, (void *) LED )  ) {
    Serial.println( message + " failed");
  } else {
    Serial.println( message + " ok");
    thread_count++;
  }
}
