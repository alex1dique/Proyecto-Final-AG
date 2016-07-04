#include <Ultrasonic.h>//libreria para el ultrasonido

#include <DHT.h>//libreria para usar el dth22 o dth11 (dth22 en nuestro caso)

#include <Bridge.h>//libreria bridge que nos servira para el control por medio de web

#include <YunServer.h>// el servidor de la yun el cual nosotros utilizamos

#include <YunClient.h>// incluimos la libreria de yun cliente para su utiliancion

//-----------------------
int dac = 0;
int DigitalPin[] = {10,11, 12, 13,7,8};
//declarando variables LDR
  int LEDPinLDR= 12;
  int sensorPin = A0; // select the input pin for ldr
  int sensorValue = 0; // variable to store the value coming from the sensor
  int ledLDR=0;
//declarando variables ultrasonido
 #define TRIGGER_PIN  3
 #define ECHO_PIN     2
 Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
 
 //declarando variables relay shield
 int foco = 5;    // Digital Arduino Pin para encender el foco
 int ventilador = 4;//Digital Arduino Pin para encender el ventilador
 int bombita = 6;//Digital Arduino Pin para encender la bomba
 int secadora= 7;//Digital Arduino Pin para encender la secadora

 
 //declarando variables para el sensor dth22
 int SENSOR = 8;
 int temp;//temperatura 
 int humedad;//humedad 
 
 DHT dht (SENSOR, DHT22);
 
 //declarando variables PIR
 int LEDPin= 13;
 int PIRPin= 9;
 int ledPir=LOW;

 YunServer server; //declaramos el nombre del servidor
 
// the setup routine runs once when you press reset:
void setup()  {
    
//    dht.begin();
    Serial.begin(9600);
    
    //declarar pid 4 al 6 como  output:
    pinMode(foco, OUTPUT);
    pinMode(ventilador, OUTPUT);
    pinMode(bombita, OUTPUT);
    pinMode(secadora, OUTPUT);
    //pin led output
    pinMode(LEDPin, OUTPUT);
    //pin pir IMPUT
    pinMode(PIRPin, INPUT);
    Bridge.begin();//iniciamos bridge 
    server.listenOnLocalhost();
}



// the loop routine runs over and over again forever:
void loop()  {

  YunClient client = server.accept();
if (client) {
process(client);//procesamos la actividad que se realiza 
client.stop();
}

   ultrasonido();
   dth22();
   ledPir = digitalRead(LEDPin);
   if(ledPir=HIGH){
    pir();
    }
   ledLDR = digitalRead(LEDPinLDR);
   if(ledLDR=HIGH){
    LDR();
    }
}

void dth22()
    {
   Serial.print("");
   pir(); 
    //sensor de temperatura y humedad
    humedad = dht.readHumidity();
    temp = dht.readTemperature();
   
    if(temp>=30.00){
      digitalWrite(ventilador,HIGH);
      }
      
    else {
      digitalWrite(ventilador,LOW);
      }  
    if(temp<15.00){
      digitalWrite(secadora,HIGH);
      }  
    else {
      digitalWrite(secadora,LOW);
      }  
     if(humedad>70.00){
      digitalWrite(secadora,HIGH);
      }     
    else {
      digitalWrite(secadora,LOW);
      }  
    //imprimiendo temperatura
    Serial.print("Temperatura:");
    Serial.println(temp);
    //Serial.println("C");
    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.println("%");
    delay(1500);
}

void ultrasonido()
  {

   float cmMsec;

  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  if(cmMsec>=25.00){
    
    digitalWrite(bombita, LOW);
    
    }
  
  Serial.print("CM: ");

  Serial.println(cmMsec);
  
  delay(1000);

  }   
  void pir()
{
  int value= digitalRead(PIRPin);
 
  if (value == HIGH)
  {
    Serial.println("Alerta humano detectado");
  }
  
}
void LDR(){
sensorValue = analogRead(sensorPin); // read the value from the sensor
if (sensorValue>=960){
  digitalWrite(foco, HIGH);
  }
else{
  digitalWrite(foco, LOW);
  }  
Serial.println(sensorValue); //prints the values coming from the sensor on the screen
delay(100);
}

 
 void process(YunClient client)
{
String command = client.readStringUntil('/');
if (command == "digital") {
digitalCommand(client);
}
if (command == "dac") {
dacCommand(client);
}
if (command == "status") {
statusCommand(client);
}
}
//funciones donde se declara que hacer dependiendo si es dac(es decir analogico) o digital el pin que 

void digitalCommand(YunClient client) {
int pin, value;
pin = client.parseInt();
if (client.read() == '/') {
value = client.parseInt();
digitalWrite(pin, value);
}
else {
value = digitalRead(pin);
}
client.print(F("digital,"));
client.print(pin);
client.print(F(","));
client.println(value);
}
void dacCommand(YunClient client) {
int pin, value;
pin = client.parseInt();
if (client.read() == '/') {
value = client.parseInt();
dac = value;
analogWrite(pin, value);
}
else {
value = dac;
}
client.print(F("dac,"));
client.print(pin);
client.print(F(","));
client.println(value);
}

void statusCommand(YunClient client) {
int pin, value;
client.print(F("status"));
for (int thisPin = 0; thisPin < 5; thisPin++) {
pin = DigitalPin[thisPin];
value = digitalRead(pin);
client.print(F("#"));
client.print(pin);
client.print(F("="));
client.print(value);
}

{
  

float temperature = dht.readTemperature();
client.print(F("#Temperatura"));
client.print(F("="));
 client.print(temperature);
}
client.println("");
}

