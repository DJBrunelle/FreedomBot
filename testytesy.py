import RPi.GPIO as GPIO
import time 
GPIO.setmode(GPIO.BOARD)
GPIO.setup(11,GPIO.OUT)
GPIO.setup(13,GPIO.OUT)

facedetected = False

p1 = GPIO.PWM(11,50)
p2 = GPIO.PWM(13,50)

p1.start(7.5)
p2.start(7.5)

def sweep():
	try:
		while facedetected == False:
			#p1.ChangeDutyCycle(8.5)
			#p2.ChangeDutyCycle(8.5)
			#time.sleep(1)
			#p1.ChangeDutyCycle(3.5)
			#p2.ChangeDutyCycle(5.5)
			#time.sleep(1)
			#p1.ChangeDutyCycle(11)
			#p2.ChangeDutyCycle(11)
			#time.sleep(1)
			for i in range(4,11):
				p1.ChangeDutyCycle(i)
				p2.ChangeDutyCycle(i)
				time.sleep(1)
	except KeyboardInterrupt:
		p1.stop()
		p2.stop()
		GPIO.cleanup()

sweep()
