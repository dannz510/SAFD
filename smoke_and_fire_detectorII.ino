#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int green = 2;
int yellow = 3;
int red = 4;

int buzzer = 5; 

int sensor = A3; // This stays as A3
int Value = 0;

int baselineTemp = 0;
int celsius = 0;
int fahrenheit = 0;

void setup()
{
 
  pinMode(A0, INPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop()
{
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  digitalWrite(buzzer, LOW);
  
  Value = analogRead(sensor); //Storing the Methane gas value
  Serial.println(Value); //Serial printing the gas value
  Value = map(Value, 306, 750, 0, 100); // Mapping the value to 0-100
  baselineTemp = 40;
  
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  
   fahrenheit = ((celsius * 9) / 5 + 32);
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F");
  
  //Color change with gas level
  if (Value >= 50) {
    digitalWrite(green, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, HIGH);
    tone(buzzer,1000);      
    delay(200);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DANGEROUS");
    delay(500);
    lcd.clear();
  }

  else if (Value >= 20 && Value <50) {
    digitalWrite(green, HIGH);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
    tone(buzzer,18000);    
    delay(200);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("POISONOUS!!!");
    delay(500);
    lcd.clear();
  }

  else if (Value <20) {
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
  }
  
  else {
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
  }
  //Color change with temperature 
   if (celsius < baselineTemp && celsius) {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);            
   
  }
  if (celsius >= baselineTemp && celsius < baselineTemp + 10) {
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  }
  if (celsius >= baselineTemp + 10 && celsius < baselineTemp + 20) {
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    tone(buzzer,500);             
    delay(200);
    noTone(buzzer);
  }
  if (celsius >= baselineTemp + 20 && celsius < baselineTemp + 30) {
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    tone(buzzer,18000);             
    delay(200);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DANGEROUS");
    delay(500);
    lcd.clear();
  }
  if (celsius >= baselineTemp + 30) {
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    tone(buzzer,18000);
    delay(200);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("FIRE!!!");
    delay(500);
    lcd.clear();
  }
}
