#define BLYNK_PRINT Serial

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <MFRC522.h> // import MFRC522 yang sudah kita instal     
#include >Servo.h>

char auth[] = "";
char ssid[] = "NamaHostpotmu";
char pass[] = "PasswordHostpotmu";

#define SDA_PIN D2 // mendefinisikan SDA Pin ke D2
#define RST_PIN D1 // mendefinisikan RST pin ke D1
#define motor D4

Servo servo;

MFRCC522 mfrcc522(SDA_PIN, RST_PIN); // setting mrfc dengan SDA dan RST

WidgetLCD lcd(V1); // setting pin virtual LCD ke V1 di aplikasi blynk

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin(); // Intiate SPI bus
  Blynk.begin(auth, ssid, pass);
  mfrc522.PCD_Init(); //Intiate Blynk bus
  pinMode(motor, OUTPUT);
  Serial.println("Approximate your card yo reader..."); // pesan untuk mentapkan kartu ke scanner
  Serial.println();



}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // menampilkan UID di serial Monitor
  Serial.print("UID adalah :");
  String content = "";
  byte letter;


  // berfungsi untuk mengubah ID dari kartu menjadi kode Hexa seperti 04 EA F0 2B
  for (byte i = 0; i < mfrcc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase(); // UID dijadikan huruf kapital semwa

  if (content.substring(1) == "04 EA F0 2B") // masukan ID kartu/ E-KTP disini
  {
    lcd.clear();
    lcd.print(0, 0, "UID for Card is"); // menampilkan UID Di Lcd blynk
    lcd.print(0, 1, content);
    delay(1000);
    buka(); //fungsi untuk menggerakan servo
  }

  else
  {
    lcd.clear();
    lcd.print(0, 0, "Invalid Card");
    lcd.print(0, 1, "Access Denied");
  }
}

void buka() // membuat fungsi untuk menggerakkan servo servo.attach(motor);
{ 
  servo.write(90);
  delay(2000);
  servo.write(0);
}
