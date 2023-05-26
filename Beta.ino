#include <Servo.h>
#include <Keypad.h>
#include <Adafruit_LiquidCrystal.h>

#define potentiometer A0
#define servo_pin 5
Servo servo;

char key;
int currentValue = 0;
int previousValue = 0;
int position;
const byte ROWS = 4;  
const byte COLS = 4;  

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPins[ROWS] = { 13, 12, 11, 10 };  
byte colPins[COLS] = { 9, 8, 7, 6 };      
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Adafruit_LiquidCrystal lcd(0);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  lcd.print("Select Mode: ");
  servo.attach(5);
  servo.write(0);
}

void loop() {

  key = keypad.getKey();
  if (key) {

    if (key == 'A') {
      lcd.clear();
      lcd.print("pot mode");
      delay(1000);
      while (key == 'A') potentiometer_mode();
    }

    if (key == 'B') {
      lcd.clear();
      lcd.print("Keypad mode");
      delay(1000);
      lcd.clear();
      lcd.print("Angle: ");
      while (key == 'B') keypad_mode();
    }
  }

  delay(100);
}



void potentiometer_mode() {
  currentValue = analogRead(potentiometer);
  position = map(currentValue, 0, 1023, 0, 180);
  servo.write(position);
  // If the value has changed, update the LCD display
  if (currentValue != previousValue) {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Pot: ");
    lcd.print(currentValue);

    lcd.setCursor(0, 1);
    lcd.print("Servo: ");
    lcd.print(position);

    previousValue = currentValue;
  }
}


void keypad_mode() {

  char key = keypad.getKey();  // Read the keypad input

  if (key) {             // If a key is pressed
    if (isdigit(key)) {  // Check if the pressed key is a digit
      lcd.print(key);
      static int count = 0;
      static int number = 0;

      number = (number * 10) + (key - '0');  // Build the three-digit number

      count++;

      if (count == 3) {  // Once three digits are entered
        Serial.println("Three-digit number entered: " + String(number));
        count = 0;
        servo.write(number);
      }
    }
  }
}
