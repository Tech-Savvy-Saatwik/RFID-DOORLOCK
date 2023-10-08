#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

 
#define SS_PIN 10
#define RST_PIN 9

#define SERVO_PIN 3
Servo myservo;

#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   
 
void setup() 
{
  Serial.begin(9600);   
  SPI.begin();          
  mfrc522.PCD_Init();   

  myservo.attach(SERVO_PIN);
  myservo.write( 70 );
  delay(7500);
  myservo.write( 0 );
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "E1 E5 3E 1E") 
  {
    Serial.println("Authorized access");
    Serial.println();
   myservo.write( 70 );
 delay(7500);
  myservo.write( 0 );

  }
 
 else   {
    Serial.println(" Access denied");
 

    delay(DENIED_DELAY);

 
  }
}


