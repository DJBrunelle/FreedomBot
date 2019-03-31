import serial  # Importing the serial library to communicate with Arduino
import RPi.GPIO as GPIO # Importing the GPIO library to use the GPIO pins of Raspberry pi
from time import sleep # Importing the time library to provide the delays in program
led_pin = 21  # Initializing pin 21 for led
button_pin = 20 # Initializing pin 20 for button
GPIO.setmode(GPIO.BCM) # Using BCM numbering
GPIO.setup(led_pin, GPIO.OUT) # Declaring the led pin as output pin
GPIO.setup(button_pin, GPIO.IN) # Declaring the button pin as input pin
# Defined the port and the baudrate at which we will communicate with Arduino.
# It should be same on the Arduino side.
# If you don't know the port at which Arduino is connected. Read the step 2 of the first example.
ser = serial.Serial('/dev/ttyACM1', 9600) 
while True:
    try:
        # Reading and storing the data coming from Arduino
        incoming_data = ser.read() 
        
        # Light up or light down the led depending on the incoming data
        if incoming_data == '1':
            GPIO.output(led_pin, 1)
        elif incoming_data == '0':
            GPIO.output(led_pin, 0)
        
        # Reading the button state
        button_state = GPIO.input(button_pin)
        if button_state == 1:
            ser.write('1') # Sending data to the Arduino
        elif button_state == 0:
            ser.write('0')
        
    except KeyboardInterrupt:
        GPIO.cleanup()