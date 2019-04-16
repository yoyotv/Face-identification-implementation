#!/bin/bash

SPACE='          '
DASH='-------------'

echo "Program start" 
echo "${SPACE}"$(date)

echo "Now compiling..."
echo "${SPACE}"$(date)

g++ -o /home/pi/Desktop/Face_identification_Raspberry_pi/detect /home/pi/Desktop/Face_identification_Raspberry_pi/detect.cpp `pkg-config --cflags --libs opencv` -I /home/pi/caffe/include -lboost_system
g++ -o /home/pi/Desktop/Face_identification_Raspberry_pi/evaluate /home/pi/Desktop/Face_identification_Raspberry_pi/evaluate.cpp


echo "Compile finished"
echo "Activate the application"
echo "${SPACE}"
echo "${SPACE}"


cd Desktop/Face_identification_Raspberry_pi
mkdir Record
mkdir Current

INDEX=1
while [ $INDEX -le $INDEX ]
do
  echo "Waiting for the face..."
  ./detect
  echo "Face detected..."


  echo "Face identifying..."


  cd
  cd caffe
  ./build/tools/extract_features.bin /home/pi/caffe/models/face_id/caffe_mobilenet_256_train_iter_240000.caffemodel /home/pi/caffe/models/face_id/mobilenet_val_256.prototxt pool6 /home/pi/caffe/models/face_id/features 1 txt
  cd
  cd Desktop/Face_identification_Raspberry_pi

 
  ./evaluate /home/pi/caffe/models/face_id/features/pool6.txt


  cd Record
  DATE1=`date +%Y%m%d_%H%M%S`
  mkdir $DATE1
  

  cp /home/pi/caffe/models/face_id/features/pool6.txt /home/pi/Desktop/Face_identification_Raspberry_pi/Record/$DATE1
  cp -R /home/pi/Desktop/Face_identification_Raspberry_pi/Current /home/pi/Desktop/Face_identification_Raspberry_pi/Record/$DATE1
  
  cd ..
  
  #echo "Welcome, Neil"
  #echo "Neil access at" >> log.txt
  #echo "${SPACE}"$(date) >> log.txt
  #echo "${DASH}"
  #echo "${SPACE}"
  #echo "${SPACE}"
  #echo "${DASH}" >> log.txt
  #echo "${SPACE}" >> log.txt
  #echo "${SPACE}" >> log.txt


done

cd
