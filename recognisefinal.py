import cv2
import os
import numpy as np
import time
import serial  

# Check if trainer file exists before loading recognizer
trainer_file = 'trainer/trainer.yml'

if os.path.exists(trainer_file):
    recognizer = cv2.face.LBPHFaceRecognizer_create()
    recognizer.read(trainer_file)
else:
    print(f"Error: Trainer file '{trainer_file}' not found.")
    exit()

# Load the Haar Cascade for face detection
cascadePath = "haarcascade_frontalface_default.xml"
if os.path.exists(cascadePath):
    faceCascade = cv2.CascadeClassifier(cascadePath)
else:
    print(f"Error: Cascade file '{cascadePath}' not found.")
    exit()

# Set up serial communication with Arduino
arduino = serial.Serial('COM6', 9600)  # Replace 'COM3' with your Arduino port

# Set font for displaying ID on the image
font = cv2.FONT_HERSHEY_SIMPLEX

# Initialize camera
cam = cv2.VideoCapture(0)

if not cam.isOpened():
    print("Error: Unable to access the camera.")
    exit()
laststate = 0

while True:
    ret, im = cam.read()

    if not ret:
        print("Error: Failed to capture image.")
        break

    gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale(gray, 1.2, 5)

    for (x, y, w, h) in faces:
        cv2.rectangle(im, (x-20, y-20), (x+w+20, y+h+20), (0, 255, 0), 4)

        # Predict the face using recognizer
        Id, confidence = recognizer.predict(gray[y:y+h, x:x+w])
        print(f"Confidence: {confidence}")

        # If face is recognized (confidence < 60), send unlock signal to Arduino
        if laststate != Id:
            if confidence < 60:
                print("Trained face detected!")
                arduino.write(b'FACE_UNLOCK')
            else:
                print("No trained face detected!")

        cv2.putText(im, str(Id), (x, y-40), font, 2, (255, 255, 255), 3)

    if len(faces) == 0:
        Id = 0

    laststate = Id

    cv2.imshow('Face Recognition', im)

    if cv2.waitKey(10) & 0xFF == ord('q'):
        break

cam.release()
cv2.destroyAllWindows()