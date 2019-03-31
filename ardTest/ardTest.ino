int led_pin = LED_BUILTIN; //Initializing pin 8 of Arduino as the led pin
int button_pin = 7;  //Initializing pin 7 of Arduino as the button pin
int button_state = 0;  //Initializes a variable for storing the button state
int incoming_state = 0;  //Initializes a variable for storing the incoming data from Arduino
void setup(){
  Serial.begin(9600);  //Started the serial communication at 9600 baudrate
  pinMode(led_pin, OUTPUT); //Declaring led pin as output pin
  digitalWrite(led_pin, LOW);  //Making the LED light up or down
}
void loop(){
  if (Serial.available() > 0){  //Looking for incoming data
    incoming_state = Serial.read();  //Reading the data
    Serial.println(incoming_state);
    if (incoming_state == '1') {
        digitalWrite(led_pin, HIGH);  //Making the LED light up or down
        delay(1000);
    } else {
        digitalWrite(led_pin, LOW);  //Making the LED light up or down
    }
  }
}
