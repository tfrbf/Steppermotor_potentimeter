#include <Servo.h>
#include <Keypad.h>
#include <Adafruit_LiquidCrystal.h>

#define potentiometer A0
#define servo_pin 5
char key_values[3];
char key;
int currentValue =0 ;
int previousValue =0 ;
int position;
const byte ROWS = 4; //تعداد ردیف
const byte COLS = 4; //تعداد ستون
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //اتصال پایه های ردیف
byte colPins[COLS] = {9, 8, 7, 6}; //پین های مربوط به ستون ها
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

Adafruit_LiquidCrystal lcd(0);
Servo servo;

void setup()
{
  lcd.begin(16, 2);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  servo.attach(servo_pin);
  servo.write(0);
  lcd.print("Select Mode: ");
}

void loop()
{
  key = keypad.getKey();
  if(key)
  {
    
    if(key == 'A') 
    { lcd.clear();
      lcd.print("potentiometer mode");
     delay(100);
     while(key == 'A') potentiometer_mode();
    }
    
    if(key == 'B') 
    { lcd.clear();
      lcd.print("Keypad mode");
     delay(100);
     while(key == 'B') keypad_mode;
    }
    
  }


  
  delay(100);
}



void potentiometer_mode()
{
  currentValue = analogRead(potentiometer);
  position = map(currentValue,0,1023,0,180);
  servo.write(position);
  // If the value has changed, update the LCD display
  if (currentValue != previousValue) {
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Pot: ");
    lcd.print(currentValue);
    
	lcd.setCursor(0,1);
    lcd.print("Servo: ");
    lcd.print(position);
    
    previousValue = currentValue;
  }
}


void keypad_mode()
{
  
  key_values[2] = keypad.getKey();
  key_values[1] = keypad.getKey();
  key_values[0] = keypad.getKey();
  position = key_values[2]*100 + key_values[1]*10 + key_values[0];
  servo.write(position);
  
  lcd.setCursor(0,0);
    lcd.print("kaypad: ");
    lcd.print(currentValue);
    
	lcd.setCursor(0,1);
    lcd.print("Servo: ");
    lcd.print(position);
  
}
