#include <LiquidCrystal.h>

// Połączenia dla DFRobot LCD Keypad Shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Podłączenia ultradźwiękowego czujnika odległości US-015
#define TRIGGER_PIN    0
#define ECHO_PIN       1

// Podłączenie Buzzera
#define SPEAKER_OUT 11
#define FREQUENCY   100

long delay_in_ms;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Sonar (range 4m)");
  delay_in_ms = 1000;
}

void loop() {
  long distance = distance_in_cm();
  lcd.setCursor(0, 1);
  if(distance <= 400) 
  {
    lcd.print(distance);
    lcd.print("cm  ");
    delay_in_ms = 3 * distance;
    sound(50);
    delay(delay_in_ms);
  }
  else
    lcd.print("      ");
}

void sound(int duration) {
  analogWrite(SPEAKER_OUT, FREQUENCY);
  delay(duration);
  analogWrite(SPEAKER_OUT, 0);
}

long distance_in_cm() {

  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  pinMode(ECHO_PIN, INPUT);
  
  return  pulseIn(ECHO_PIN, HIGH) / 29 / 2 ;
}

