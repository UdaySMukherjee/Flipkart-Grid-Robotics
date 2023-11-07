#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_TEMPLATE_ID "TMPL3YBm-gldz"
#define BLYNK_TEMPLATE_NAME "ARM"
#define BLYNK_AUTH_TOKEN "NzdyjwRgaYX-o4ZsIMRvgjaZ_C6bISmB"
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Airtel_Zerotouch";
char pass[] = "Airtel@123";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth,ssid,pass,"blynk.cloud",80);
  pinMode(23, OUTPUT);//vo
  pinMode(22, OUTPUT);//v1
  pinMode(21, OUTPUT);//v2
  pinMode(19, OUTPUT);//v3
  pinMode(18, OUTPUT);//v4
  pinMode(5, OUTPUT);//v5
  pinMode(4, OUTPUT);//v6
  pinMode(2, OUTPUT);//v7
  pinMode(26, OUTPUT);//v8
  pinMode(27, OUTPUT);//v9
  pinMode(32, OUTPUT);//v10
  pinMode(33, OUTPUT);//v11
  pinMode(25, OUTPUT);//v12
  digitalWrite(23,HIGH);
  digitalWrite(22,HIGH);
  digitalWrite(21,HIGH);
  digitalWrite(19,HIGH);
  digitalWrite(18,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(27,HIGH);
  digitalWrite(26 ,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(33,HIGH);
  digitalWrite(25,HIGH);
  
}
  BLYNK_WRITE(V0){
  if(param.asInt() == 1){
    digitalWrite(23,LOW);  
  }
  else{
    digitalWrite(23,HIGH);  
  }
  }
  BLYNK_WRITE(V1){
  if(param.asInt() == 1){
    digitalWrite(22,LOW);  
  }
  else{
    digitalWrite(22,HIGH);  
  }
  }BLYNK_WRITE(V2){
  if(param.asInt() == 1){
    digitalWrite(21,LOW);  
  }
  else{
    digitalWrite(21,HIGH);  
  }
  }BLYNK_WRITE(V3){
  if(param.asInt() == 1){
    digitalWrite(19,LOW);
  }
  else{
    digitalWrite(19,HIGH);  
  }
  }BLYNK_WRITE(V4){
  if(param.asInt() == 1){
    digitalWrite(18,LOW); 
  }
  else{
    digitalWrite(18,HIGH);  
  }
  }BLYNK_WRITE(V5){
  if(param.asInt() == 1){
    digitalWrite(5,LOW); 
  }
  else{
    digitalWrite(5,HIGH);  
  }
  }BLYNK_WRITE(V6){
  if(param.asInt() == 1){
    digitalWrite(4,LOW);  
  }
  else{
    digitalWrite(4,HIGH);  
  }
  }BLYNK_WRITE(V7){
  if(param.asInt() == 1){
    digitalWrite(2,LOW);  
  }
  else{
    digitalWrite(2,HIGH);  
  }
  }BLYNK_WRITE(V8){
  if(param.asInt() == 1){
    digitalWrite(25,LOW);  
  }
  else{
    digitalWrite(25,HIGH);  
  }
  }BLYNK_WRITE(V9){
  if(param.asInt() == 1){
    digitalWrite(26,LOW);  
  }
  else{
    digitalWrite(26,HIGH);  
  }
  }
  BLYNK_WRITE(V10){
  if(param.asInt() == 1){
    digitalWrite(32,LOW);  
  }
  else{
    digitalWrite(32,HIGH);  
  }
  }
  BLYNK_WRITE(V11){
  if(param.asInt() == 1){
    digitalWrite(33,LOW);  
  }
  else{
    digitalWrite(33,HIGH);  
  }
  }BLYNK_WRITE(V12){
  if(param.asInt() == 1){
    digitalWrite(27,LOW); 
  }
  else{
    digitalWrite(27,HIGH);  
  }
  }
void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();

}
