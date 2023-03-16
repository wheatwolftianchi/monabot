import cv2
import numpy as np
import serial

#open camera and have live stream
cap = cv2.VideoCapture(0)
#show live stream
while True:
    ret, frame = cap.read()
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
#detect if the bot is going srtight and calculate its angle



# start serial communication
ser = serial.Serial('COM3', 9600)
ser.write(b'1')
