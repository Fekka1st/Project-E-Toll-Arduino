#include <Servo.h>
#include<KRrfid.h>
Servo myservo;  
byte sda = 10; //data sda RF ID
byte rst = 9; // data rst RF ID
const int buzzer = 2; // data buzzer
int saldo_a = 10000; // E-tol 1
int saldo_b = 5000;  // E-tol 2
int i = 1; // sebuah data sementar
int pos = 0;  // rotasi awal servo
int led = 4;  // data lampu 1
int led2 = 5;  // data lampu 2

void setup() {
  Serial.begin(9600);
  rfidBegin();
   pinMode(buzzer, OUTPUT);
   myservo.attach(3);  
   pinMode(led, OUTPUT);
   pinMode(led2, OUTPUT);
}

void loop() {
  getTAG(); // ambil id lewat RF ID
  digitalWrite(led2, HIGH);
  // ID TOL 1
  if (TAG == "108834215102128" && saldo_a >= 2000) { //jika id terdeteksi
    Serial.println("Kode ID card anda: "+TAG);
    saldo_a = saldo_a - 2000;
    Serial.print("Saldo saat ini : ");
    Serial.println((int)saldo_a);
    tone(buzzer, 2000);
    delay(100);
    tone(buzzer, 2000); 
    noTone(buzzer); 
      for (pos = 100; pos >= 0; pos -= 1) {
        myservo.write(pos);            
        delay(1);     
        digitalWrite(led2, LOW); 
        digitalWrite(led, HIGH);   // turn the led o
      }  
    delay(5000);
    digitalWrite(led, LOW);  
      for (pos = 0; pos <= 100; pos += 1) { 
      myservo.write(pos);              
      delay(15);                       
    } 
    delay(1000);
    TAG = "";
  }else if (TAG == "108834215102128" && saldo_a < 2000){
    for(i=1 ; i<=5 ; i++){
    digitalWrite(led2, LOW);  
    tone(buzzer, 2000); 
    delay(100);  
    digitalWrite(led2, HIGH);
    noTone(buzzer);    
    delay(100);
    }
    TAG = "";
  }

  //Jika Id tidak terdaftar resmi / belum tercatat
  if (TAG != "") {   // jika id anda belum terdaftar
    for(i=1 ; i<=3 ; i++){
    digitalWrite(led2, LOW);  
    tone(buzzer, 4000); 
    delay(1000);  
    digitalWrite(led2, HIGH);
    noTone(buzzer);    
    delay(100);
    }
    TAG = "";
  } 
}
