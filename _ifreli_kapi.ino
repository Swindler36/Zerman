
#include <Servo.h>// servoyu çalıştırmak için servo kütüphanesi çağırılıyor

#define sifre "code-forever.com" // şifre değişkeni define(değiştirilemez) olarak ayarlanıyor.
Servo kapi; // kullanılacak servonun adı kapı olarak ayarlanıyor.
int redled = 2; /* şifre yanlış yazıldığında yanması için Redled adında
                  kırmızı bir red tanımlanıyor ve dijital 2 pinine bağlanıyor.*/

void setup() {
  pinMode(redled, OUTPUT); // pinmode Output olarak ayarlanıyor.
  Serial.begin(9600); // Serial port başlatılıyor
  kapi.attach(9); // servonun bağlanacağı pin dijital 9 olarak belirleniyor
}

void loop() {
  int durum = Serial.available(); //Serial porta girişi olup olmadığını kontrol edip durum değişkenine atıyor.

  kapi.write(90); // servo 90 dereceye dönüyor

  if (durum) {
   
    if (Serial.find(sifre)) { //girilen veride Code-Forever.com yazıp yazmadığını kontrol ediyor eğer doğru ise else'e kadar olan kodları çalıştırıyor.
      Serial.println("başarılı"); // Serial porta başarılı yazıyor.
      kapi.write(0); // servo 0 dereceye dönüyor
      Serial.end();// Serial portu durduruyor.
      delay(1000); // 1000 milisaniye bekliyor
      

    } else { // eğer girilen veride Code-Forever.com yazmıyorsa burdaki kodlar çalışıyor
      
      Serial.println("başarısız"); // Serial porta başarısız yazıyor.
      Serial.println("tekrar denemek için lütfen bekleyiniz..."); // Serial porta tekrar denemek için lütfen bekleyiniz... yazıyor.
      kapi.write(90); // servo 90 dereceye dönüyor
      digitalWrite(redled, HIGH); // ledi yakıyor
      delay(500); // 500 milisaniye bkliyor
      digitalWrite(redled,LOW); // ledi söndürüyor
      Serial.println("tekrar deneyiniz"); // Serial porta tekrar deneyiniz yazıyor.
      Serial.end(); // Serial portu durduruyor.   
       
    }

    Serial.begin(9600); // tekrar giriş olabilmesi için serial portu tekrar açıyor.
  }

}
