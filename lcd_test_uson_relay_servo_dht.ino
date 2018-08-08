#include <DHT.h>

#include <Servo.h>

#include <LiquidCrystal.h>

#define DHTPIN 8  //menggunakan pin 1 untuk pemasangan sensornya
#define DHTTYPE DHT11 //memilih tipe DHT11, bisa diubah menjadi DHT22, DHT21

DHT dht(DHTPIN,DHTTYPE);

// Setting LCD RS E D4 D5 D6 D7
LiquidCrystal lcd(6, 7, 9, 10, 11, 12);
const int TRIG_PIN = 4;// pin triger sensor ultrasonic di koneksikan ke pin 12 pada arduino 
const int ECHO_PIN = 5;// pin echo sensor ultrasonic di koneksikan ke pin 11 pada arduino
const int buzzer = 13;
const int relayA= 2;
Servo myservo;
//int pos=00;

void setup(){
// pilih LCD 16 x 2
Serial.begin(9600);
pinMode(TRIG_PIN,OUTPUT);
pinMode(ECHO_PIN,INPUT);
pinMode(buzzer,OUTPUT);
pinMode(relayA,OUTPUT);
myservo.attach(3);
lcd.begin(16,2);
lcd.setCursor(2,0);
lcd.print("Deny Pradana");
lcd.setCursor(3,1);
lcd.print("TES SENSOR");

delay(3000);
tone(buzzer, 3000);
delay(100);
tone(buzzer, 2000);
delay(100);
tone(buzzer, 1000);
delay(100);

noTone(buzzer);
}

void loop(){
 long duration, distanceCm;

  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN,HIGH);

  // convert the time into a distance
  // 340 m/s--> dalam satu detik jarak tempuh adalah 340 meter, 
  //1/10 detik untuk 34 meter, 
  //1/100 detik (10 /1000 detik (baca 10 mili detik))untuk 3,4 meter 
  // 1/1000 detik baca 1 mili detik untuk jarak 0,34 meter (34cm)
  
 // jadi untuk menempuh jarak 1 cm --> (1/100 meter) diperlukan waktu sebanyak : 
  //29.1 ųs/cm
  distanceCm = duration / 29.41 / 2 ;

  if (distanceCm <= 0){
    Serial.println("Out of range");
    tone(buzzer, 1000);
    delay(3000);
  }
  else {
    noTone(buzzer);
    Serial.print(distanceCm);
    Serial.println("CM");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarak : ");
  //lcd.setCursor(0, 1);
  lcd.print(distanceCm);
  lcd.print(" Cm ");
  int kelembaban = dht.readHumidity(); //menyimpan nilai Humidity pada variabel kelembaban
  int suhu = dht.readTemperature(); //menyimpan nilai Temperature pada variabel suhu
  lcd.setCursor(0, 1);
  lcd.print("K:");
  lcd.print(kelembaban);
  lcd.print(" T:");
  lcd.print(suhu);
  }
  if (distanceCm <250){
    Serial.println("MAX RANGE");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("W!: ");
    //lcd.setCursor(0, 1);
    lcd.print(distanceCm);
    lcd.print(" Cm ");
    myservo.write(00);
    myservo.write(180);
    digitalWrite(relayA,LOW);
    tone(buzzer, 2000);
    delay(1000);
  }
  else {
    noTone(buzzer);
    Serial.print(distanceCm);
    Serial.println("CM");
    myservo.write(00);
    //myservo.write(90);
    digitalWrite(relayA,HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarak : ");
  //lcd.setCursor(0, 1);
  lcd.print(distanceCm);
  lcd.print(" Cm ");
  int kelembaban = dht.readHumidity(); //menyimpan nilai Humidity pada variabel kelembaban
  int suhu = dht.readTemperature(); //menyimpan nilai Temperature pada variabel suhu
  lcd.setCursor(0, 1);
  lcd.print("K:");
  lcd.print(kelembaban);
  lcd.print(" T:");
  lcd.print(suhu);
  
  }
  delay(1000);
}
