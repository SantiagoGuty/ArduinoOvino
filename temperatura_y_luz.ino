int LIGHT_PIN = A4; //photoresistor
float DARK_THRESHOLD = 1.5; //creates variable for how dark room is to be dark
int greenLED = 13; //greenLED
int blueLED = 7; //blueLED
int redLED = 10; //redLED
int tempPin = A0; //temperature sensor

void setup() {

Serial.begin(9600); //exchanges 9600 bits per second with serial monitor
pinMode(blueLED, OUTPUT);
pinMode(redLED, OUTPUT); 

int reading = analogRead(tempPin);
float voltage = reading / 1023.0 * 5.0;
float tempC = (voltage - 0.5) * 100;
float tempF = (tempC * 9.0/5.0) + 32.0;
float origtemp = tempF;
}

void loop() {

int lightADC = analogRead(LIGHT_PIN); //gives integer variable to photoresistor output
float lightV = lightADC * 5.0 / 1023.0; //converts reading to a voltage

delay(2000);

int reading = analogRead(tempPin);
float origvoltage = reading / 1023.0 * 5.0;
float origtempC = (origvoltage - 0.5) * 100;
float origtempF = (origtempC * 9.0/5.0) + 32.0;
float origtemp = origtempF; //reads temperature sensor again and converts to original temperature

Serial.print("The current temperature in Fahrenheit is "); Serial.print(origtempF); Serial.print("\n");
Serial.print("The photoresistor voltage is "); Serial.print(origvoltage); Serial.print("V \n");

if (origtempF < 70){
   digitalWrite(blueLED, HIGH);
   delay(333);
   digitalWrite(blueLED, LOW);
}

lightV = lightADC * 5.0 / 1023.0;

if (lightV <= DARK_THRESHOLD) {
  digitalWrite(redLED, LOW);
  Serial.print("It is day\n");  
}
else {
  if (lightV >= 3.0) {
    Serial.print("It is completely dark\n");
     digitalWrite(redLED,HIGH);
    delay(100);
  }
    else {
      digitalWrite(redLED, HIGH);
      Serial.print("It is dark\n");
    }
  }
  lightV = lightADC * 5.0 / 1023.0;
  delay (2000); 
  int newreading = analogRead(tempPin);
  float newvoltage = newreading / 1023.0 * 5.0;
  float newtempC = (newvoltage - 0.5) * 100;
  float newtempF = (newtempC * 9.0/5.0) + 32.0;
  //once again converts photoresistor reading to temp
  //temp is then converted to new temperature fahrenheit

  if (newtempF > origtemp + 5 || newtempF < origtemp - 5) {
      Serial.print("Temp has changed more than five degrees\n");
      digitalWrite(blueLED,HIGH);
      delay(2000);
      //if new temp higher than 5 degrees compared to original temp
      //blueLED is turned on and stays on for 2 seconds
      //temp changed more than 5 degrees message printed
  }
  else {
    digitalWrite(blueLED,LOW);
  }
}
