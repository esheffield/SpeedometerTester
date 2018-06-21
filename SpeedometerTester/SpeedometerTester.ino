#include <FlexiTimer2.h>
#include <LiquidCrystal.h>
#include <LCDKeypad.h>

// enum ePins { LCD_RS=8, LCD_EN=9, LCD_D4=4, LCD_D5=5, LCD_D6=6, LCD_D7=7, LCD_BL=10 }; // define LCD pins
LCDKeypad lcd;

#define COLS 16
#define ROWS 2

// Pulses per mile
#define PPM 16000.0
#define MIN_MPH 5
#define MAX_MPH 120
#define SEC_PER_HOUR 3600.0

#define OUTPIN 2

double mphToHz(int mph) {
  return ((double)mph * PPM) / SEC_PER_HOUR;
}

int fudge = 0;
int mph = 5;
double resolution = 1.0 / 50000.0;

void pulse() {
  static boolean output = HIGH;
  digitalWrite(OUTPIN, output);
  output = !output;
}

void setup() {
  pinMode(OUTPIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Starting...");
  lcd.begin(COLS, ROWS);
  lcd.setCursor((COLS - 11) / 2, 0);
  lcd.print("Speedometer");
  lcd.setCursor((COLS - 6) / 2, 1);
  lcd.print("Tester");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MPH: ");
  lcd.setCursor(0,1);
  lcd.print("Freq: ");

  double freq = mphToHz(mph);

  lcd.setCursor(5, 0);
  lcd.print(mph);
  lcd.print("  ");
  lcd.setCursor(6, 1);
  lcd.print(freq);
  lcd.print(" Hz  ");

  double units = 1.0 /(freq * 2 * resolution);
  FlexiTimer2::set(units, resolution, pulse);
  FlexiTimer2::start();
  
  Serial.println("Running...");
}

void loop() {
  int oldMph = mph;
  switch(lcd.buttonBlocking()) {
    case KEYPAD_UP:
    if(mph < MAX_MPH) {
      mph += 5;
    }
    break;
    case KEYPAD_DOWN:
    if(mph > MIN_MPH) {
      mph -= 5;
    }
    break;
  }

  if(oldMph != mph) {
    double freq = mphToHz(mph);
    lcd.setCursor(5, 0);
    lcd.print(mph);
    lcd.print("  ");
    lcd.setCursor(6, 1);
    lcd.print(freq);
    lcd.print(" Hz  ");

    double units = 1.0 /(freq * 2 * resolution);
    Serial.print("Units: ");
    Serial.println(units);
    
    FlexiTimer2::stop();
    FlexiTimer2::set(units, resolution, pulse);
    FlexiTimer2::start();
  }
}
