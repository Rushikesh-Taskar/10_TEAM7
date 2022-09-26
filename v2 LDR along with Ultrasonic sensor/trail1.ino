#include <LiquidCrystal.h>// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define LDR_Sensor  A0  //LDR Sensor Pin
#define relay 8 // Out for light 
#define trigPin 10 //Define the HC-SE04 triger on pin 6 on the arduino
#define echPin 9 //Define the HC-SE04 echo on pin 5 on the arduino

int read_ADC =0;
int Brightness;

void setup()
{
    pinMode(LDR_Sensor, INPUT);
    pinMode(relay, OUTPUT);

    Serial.begin (9600); //Start the serial monitor
    pinMode(trigPin, OUTPUT); //set the trigpin to output
    pinMode(echPin, INPUT); //set the echopin to input
  
    lcd.begin(16,2);  
    lcd.setCursor(0,0);
    lcd.print(" WELCOME TO Our ADE Project ");
    lcd.setCursor(0,1);
    lcd.print(" Automatic Light Control ");
    delay(500); // Waiting for a while
    lcd.clear();
    }

void loop()
{   
    read_ADC = analogRead(LDR_Sensor); // read analogue to digital value 0 to 1023
    Brightness = read_ADC /10.23; // Maximum value analogue to digital 1023 / 10.23

    int duration, distance; //Define two intregers duration and distance to be used to save data
    digitalWrite(trigPin, HIGH); //write a digital high to the trigpin to send out the pulse
    delayMicroseconds(500); //wait half a millisecond
    digitalWrite(trigPin, LOW); //turn off the trigpin
    duration = pulseIn(echPin, HIGH); //measure the time using pulsein when the echo receives a signal set it to high
    distance = (duration/2) / 29.1; //distance is the duration devided by 2 becasue the signal traveled from the trigpin then back to the echo pin, then divide by 29.1 to convert to centimeters

    lcd.setCursor(0, 0);
//    lcd.print("Brightness: ");
//    lcd.print(Brightness);
//    lcd.print("%  ");
    lcd.print("Distance:  ");
    lcd.print(distance);
    lcd.setCursor(0,1); 
    lcd.print("  Light is ");
    
    if (distance < 350 and Brightness<40) //if the distance is less than 13 CM
    {
        digitalWrite(relay,HIGH);
        lcd.print(" On");
    }
    else if(Brightness>70 or distance > 350)
        {
            digitalWrite(relay,LOW); 
            lcd.print("Off");
        }
    delay(100); //delay half a second
    
}
