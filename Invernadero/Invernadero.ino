#include <Ultrasonic.h>

#include <DHT.h>

//VARIABLES DE PRUEVA
int estado = LOW;
//-----------------------

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
 
// the setup routine runs once when you press reset:
void setup()  {
    
    dht.begin();
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
}
 
// the loop routine runs over and over again forever:
void loop()  {
   ultrasonido();
   Serial.print(""); 
   dth22(); 
   Serial.print("");
   pir();   
}


void luz()
{
   //foco
    
    digitalWrite(foco,HIGH);// NO3 and COM3 Connected 
    delay(10000); // wait 10000 milliseconds (1 second)
    digitalWrite(foco,LOW);// NO3 and COM3 Disconnected 
    delay(10000); // wait 10000 milliseconds (1 second)
    
}

void vent()
{

     //ventilador
    
    digitalWrite(ventilador,HIGH);// NO4 and COM4 Connected 
    delay(10000); // wait 10000 milliseconds (1 second)
    digitalWrite(ventilador,LOW);// NO4 and COM4 Disconnected 
    delay(10000); // wait 10000 milliseconds (1 second)
    
}

void seca()
{

     //secadora
    
    digitalWrite(secadora,HIGH);// NO1 and COM1 Connected 
    delay(10000); // wait 10000 milliseconds (1 second)
    digitalWrite(secadora,LOW);// NO1 and COM1 Disconnected 
    delay(10000); // wait 10000 milliseconds (1 second)
    
}

void bomba()
{
  
      //bombita

}

void dth22()
    {
    //sensor de temperatura y humedad
    humedad = dht.readHumidity();
    temp = dht.readTemperature();
    if(temp)
    /*lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperatura:");
    lcd.print(temp,DEC);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humedad:");
    lcd.print(humedad,DEC);
    lcd.print("%");*/
    //
    Serial.print("Temperatura:");
    Serial.print(temp,DEC);
    Serial.println("C");
    Serial.print("Humedad: ");
    Serial.print(humedad,DEC);
    Serial.println("%");
    delay(1500);
}

void ultrasonido()
  {

   float cmMsec;

  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  if(cmMsec>=15.00){
    digitalWrite(LEDPin, LOW); 
    }
  else{
    digitalWrite(LEDPin, HIGH); 
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
    Serial.print("Alerta humano detectado")
    digitalWrite(LEDPin, HIGH);
    delay(50);
    digitalWrite(LEDPin, LOW);
    delay(50);
  }
  else
  {
    digitalWrite(LEDPin, LOW);
  }
}

 
 

