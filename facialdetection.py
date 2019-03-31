import numpy as np
import cv2
import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BOARD)
GPIO.setup(11,GPIO.OUT)
GPIO.setup(13,GPIO.OUT)
faceCascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
cap = cv2.VideoCapture(0)
faceexists = False
p1 = GPIO.PWM(11,50)
p2 = GPIO.PWM(13,50)

cap.set(3,640) # set Width
cap.set(4,480) # set Height

p1.start(7.5)
p2.start(7.5)

def sweep():
	try:
		while faceexists == False:
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



while True:
	sweep()
    ret, img = cap.read()
    img = cv2.flip(img, -1)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale(
        gray,     
        scaleFactor=1.2,
        minNeighbors=5,     
        minSize=(20, 20)
    )
    for (x,y,w,h) in faces:
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
        faceexists = True
        cv2.circle(img,(320,220),3,(255,0,0),3)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]  
        print(x,y)
    cv2.imshow('video',img)
    k = cv2.waitKey(1) & 0xff
    if k == 27: # press 'ESC' to quit
        break
        
        

        
cap.release()
cv2.destroyAllWindows()
