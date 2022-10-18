#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(10, 9);
int MQ5_Gas_Pin = 6;
int MQ5_Gas_Value;
int buzzerPin = 4;
int ledPin=7;


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  pinMode(MQ5_Gas_Pin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin,OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("LPG Gas Leakage");
  lcd.setCursor(0, 1);
  lcd.print("   Monitoring");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("      and");
  lcd.setCursor(0, 1);
  lcd.print("  Alert System");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("     Done By");
  lcd.setCursor(0, 1);
  lcd.print("Kunle and Sodiq");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Getting the LPG");
  lcd.setCursor(0, 1);
  lcd.print("Gas Conc....");
  delay(1000);
}

void loop() {
  lcd.clear();
  MQ5_Gas_Value = digitalRead(MQ5_Gas_Pin);
  Serial.print("MQ5_Gas_Value:");

  Serial.println(MQ5_Gas_Value);
  gasConc();
  delay(1000);
}

void gasConc() {
  lcd.setCursor(0, 0);
  lcd.print(" Scanning...");
  MQ5_Gas_Value = digitalRead(MQ5_Gas_Pin); //reads the output of gas sensor
  if (MQ5_Gas_Value == LOW)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gas Leaking!");
    lcd.setCursor(0, 1);
    lcd.print("Alert!");
    analogWrite(ledPin,200);
    sendSMS();
//    analogWrite(buzzerPin,200);
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("No Gas Leaking");
    analogWrite(ledPin,0);
//    analogWrite(buzzerPin,0);
  }
}

void sendSMS(){
mySerial.println("AT+CMGF=1");
delay(1000);
mySerial.println("AT+CMGS=\"+2347054184069\"\r");
delay(1000);
mySerial.println("Gas Leaking!");//message content
delay(200);
mySerial.println((char)26); //the stopping character
delay(1000);
mySerial.println("AT+CMGS=\"+2347081319857\"\r");
delay(1000);
mySerial.println("Gas Leaking!");//message content//message content
delay(200);
mySerial.println((char)26); //the stopping character
delay(1000);
}
