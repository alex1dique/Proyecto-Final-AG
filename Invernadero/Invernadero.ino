//#include <Ultrasonic.h>

//#include <DHT.h>

//VARIABLES DE PRUEVA
int estado = LOW;
//-----------------------

//declarando variables LDR
  int sensorPin = A0; // select the input pin for ldr
  int sensorValue = 0; // variable to store the value coming from the sensor
  
//declarando variables ultrasonido
 #define TRIGGER_PIN  3
 #define ECHO_PIN     2
 //Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
 
 //declarando variables relay shield
 int foco = 5;    // Digital Arduino Pin para encender el foco
 int ventilador = 4;//Digital Arduino Pin para encender el ventilador
 int bombita = 6;//Digital Arduino Pin para encender la bomba
 int secadora= 7;//Digital Arduino Pin para encender la secadora
 
 //declarando variables para el sensor dth22
 int SENSOR = 8;
 int temp;//temperatura 
 int humedad;//humedad 
 
// DHT dht (SENSOR, DHT22);
 
 //declarando variables PIR
 int LEDPin= 13;
 int PIRPin= 9;

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
}
 
// the loop routine runs over and over again forever:
void loop()  {
   ultrasonido();
   Serial.print(""); 
   dth22(); 
   Serial.print(""); 
   LDR();  
   Serial.print("");
   pir(); 
}

void dth22()
    {
    //sensor de temperatura y humedad
    humedad = dht.readHumidity();
    temp = dht.readTemperature();
    if(temp>30){
      digitalWrite(ventilador,HIGH);
      }
    if else(temp<15){
      digitalWrite(secadora,HIGH);
      
      }  
    if else(humedad<60){
      digitalWrite(bombita,HIGH);
      } 
      if else(humedad>70){
      digitalWrite(secadora,HIGH);
      
      }     
    else {
      digitalWrite(ventilador,LOW);
      digitalWrite(secadora,LOW);
      }  
    //imprimiendo temperatura
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

  if(cmMsec>=25.00){
    digitalWrite(LEDPin, HIGH);
    
    digitalWrite(bombita, LOW);
    }
  else{
    digitalWrite(LEDPin, LOW);  
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
    digitalWrite(LEDPin, HIGH);
    delay(100);
    digitalWrite(LEDPin, LOW);
    delay(100);
  }
  else
  {
    digitalWrite(LEDPin, LOW);
  }
}
void LDR(){
sensorValue = analogRead(sensorPin); // read the value from the sensor
if (sensorValue>=980){
  digitalWrite(foco, HIGH);
  }
else{
  digitalWrite(foco, LOW);
  }  
Serial.println(sensorValue); //prints the values coming from the sensor on the screen
delay(100);
}

 
 

