#include <Arduino.h>

// Common Cathode 7 segment display segment and pin combinations. Check LDD004 7 segment display datasheet for more details.
#define a 7
#define b 6
#define c 4
#define d 2
#define e 1
#define f 9
#define g 10

// Segments to light up for each number.
const int *numbers[10] = {(int[]) {a, b, c, d, e, f}, (int[]) {b, c}, (int[]) {a, b, d, e, g}, (int[]) {a, b, c, d, g}, (int[]) {b, c, f, g}, (int[]) {a, c, d, f, g}, (int[]) {a, c, d, e, f, g}, (int[]) {a, b, c}, (int[]) {a, b, c, d, e, f, g}, (int[]) {a, b, c, f, g}};
const int numberSizes[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};
const int cathodePoints[4] = {11, 12, 3, 0}; // Pins controlling the common cathode in order from left to right.

const unsigned long interval = 60000; // 60000ms = 1 minute.

void setup() {
  for (size_t i = 0; i <= 12; i++) {
    pinMode(i, OUTPUT);
  }
}

void flashNumber(const int *number, const int cathode, const int length) {
  digitalWrite(cathode, LOW);

  for (int i = 0; i < length; i++) {
    digitalWrite(number[i], HIGH);
  }

  delay(1);

  for (int i = 0; i < length; i++) {
    digitalWrite(number[i], LOW);
  }

  digitalWrite(cathode, HIGH);
}

void display(int time) {
  flashNumber(numbers[(time % 10000) / 1000], cathodePoints[0], numberSizes[(time % 10000) / 1000]);
  flashNumber(numbers[(time % 1000) / 100], cathodePoints[1], numberSizes[(time % 1000) / 100]);
  flashNumber(numbers[(time % 100) / 10], cathodePoints[2], numberSizes[(time % 100) / 10]);
  flashNumber(numbers[time % 10], cathodePoints[3], numberSizes[time % 10]);
}

void loop() {
  unsigned long previousMillis = 0;
  int time = 0; // Set the time of day in minutes.

  while (time < 1440) {
    display(((time / 60) * 100) + (time - ((time / 60) * 60)));

    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      time++;
    }
  }
}