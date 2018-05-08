#ifndef TIME_H
#define TIME_H

/* Enables timer tick interrupt */
void enableTickInter();

/* Disables timer tick interrupt */
void disableTickInter();

/* Displays current time */
void printTime();

/* Returns current seconds */
unsigned int seconds();

/* Returns current minutes */
unsigned int minutes();

/* Returns current hour */
unsigned int hour();

#endif
