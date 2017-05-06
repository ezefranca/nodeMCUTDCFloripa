#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "Sua URL do FIrebase"
#define FIREBASE_AUTH "Chave Secreta do Banco"
#define WIFI_SSID "NOME DO WIFI"
#define WIFI_PASSWORD "SENHA"

int buttonState = 0;

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(0, INPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conectando...");
   
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("conectado a rede: ");
  Serial.println(WiFi.localIP());
  
  // Conecta ao Firebase 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(1000);
  Firebase.set("ledStatus", 0);
  if (Firebase.failed()) {
    Serial.print(">>> ERRO ao criar ledStatus >>> ");
    Serial.println(Firebase.error());
  }
}

void setButtonStatus() {

  buttonState = digitalRead(0);
  Firebase.setInt("buttonStatus", buttonState);

  if (Firebase.failed()) {
    Serial.print(">>> Erro ao setar buttonStatus >>> ");
    Serial.println(Firebase.error());
  } else {
    Serial.println(buttonState);
  }
}

void getButtonStatus() {

  int status = Firebase.getInt("buttonStatus");

  if (Firebase.failed()) {
    Serial.print(">>> Erro ao obter buttonStatus >>> ");
    Serial.println(Firebase.error());
  } else {
    digitalWrite(13, status);
    Serial.println(status);
  }

}

void loop() {
  setButtonStatus();
  getButtonStatus();
  delay(50);
}
