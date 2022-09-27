
#define LDR_Sensor  A0  //LDR Sensor Pin
#define relay_bulb 8 // Out for light
#define fan 6 // Out for fan 
#define trigPin 10 //Define the HC-SE04 triger on pin 6 on the arduino
#define echPin 9 //Define the HC-SE04 echo on pin 5 on the arduino
#define TempPin A2



#define FlameSensor 2 // the number of the flame sensor pin
#define ledPin 13 // the number of the LED pin



int read_ADC =0;
int Brightness;
float temp = 0;
int TempValue;

void setup()
{
    pinMode(LDR_Sensor, INPUT);
    pinMode(relay_bulb, OUTPUT);
    pinMode(fan, OUTPUT);


    
 pinMode (FlameSensor, INPUT); //initialize the flame sensor sensor pin as an input:
  pinMode (ledPin, OUTPUT); //



    Serial.begin (9600); //Start the serial monitor
    pinMode(trigPin, OUTPUT); //set the trigpin to output
    pinMode(echPin, INPUT); //set the echopin to input
}

void loop()
{   
    read_ADC = analogRead(LDR_Sensor); // read analogue to digital value 0 to 1023
    Brightness = read_ADC /10.23; // Maximum value analogue to digital 1023 / 10.23

    int duration, distance; //Define two intregers duration and distance to be used to save data
    
    digitalWrite(trigPin, HIGH); //write a digital high to the trigpin to send out the pulse
    delayMicroseconds(100); //wait half a millisecond
    digitalWrite(trigPin, LOW); //turn off the trigpin
    
    duration = pulseIn(echPin, HIGH); //measure the time using pulsein when the echo receives a signal set it to high
    distance = (duration/2) / 29.1; //distance is the duration devided by 2 becasue the signal traveled from the trigpin then back to the echo pin, then divide by 29.1 to convert to centimeters

    TempValue = analogRead(TempPin); // Getting LM35 value and saving it in variable
    temp = ( TempValue/1024.0)*500; // Getting the celsius value from 10 bit analog value









    int sensorState = digitalRead (FlameSensor); //read the state of the flame sensor sensor value:
  
  if (sensorState == HIGH) //If the flame sensor detect flame, then sensorState is HIGH:
  {
    digitalWrite(ledPin, HIGH); //Turn LED ON
  }
  
  else  //If the flame sensor not detect flame, then sensorState state is LOW:
  {
    digitalWrite(ledPin, LOW); //Turn LED OFF
  } 








  
    
    if (distance < 350 and Brightness<50) //if the distance is less than 350 CM
    {
        digitalWrite(relay_bulb,HIGH);
    }
    else if(Brightness>70 or distance > 350)
    {
        digitalWrite(relay_bulb,LOW); 
    }

    if(distance < 350 and temp > 26)
    {
        digitalWrite(fan,HIGH);
    }
    else{
        digitalWrite(fan,LOW);
    }
    
    
}
