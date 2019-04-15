# Face-identification-Raspberry-pi


## Approach 

Using the caffe engine to extract the feature.

Combined with the c++ in order to implement an application on Raspberry-pi identify the face.

It is able to switch the model to increase the performance. e.g. Resnet, Mobilenet.

Here is the flow chart.

   <img src="https://raw.githubusercontent.com/yoyotv/Raspberry/master/pictures/flow_chart.jpg" >
  
## GET started

You have to install

1. [Opencv](https://opencv.org/)  for read image and detect face, I use 2.4.9

2.  [Caffe](https://caffe.berkeleyvision.org/) for extracting the feature. There is a good step by step [tutorial](https://github.com/leo2105/Caffe-installation-Raspberry-Pi-3)  to install caffe on Raspberry by leo2105

## Installation

1. Clone the repository
  ```Shell
  # Make sure to clone with --recursive
  git clone --recursive https://github.com/yoyotv/Raspberry.git
  ```
2. Replace the original caffe/tools/extract_feature.cpp with the new extract_feature.cpp file

3. Add the face_id fold under caffe/models

4. Place fold "Face_identification_Raspberry_pi" under Desktop

5. Finished!

## Tutorial

#### We can enjoy the face identification system in just one command!

1. First of all, run

```
sh run.sh
```
2. Shell will compile evaluate.cpp and detect.cpp, after that it will create two folders named Record and Current, respectively.

3. Shell then enable the detect application, the detected face will be store at folder "Current".

4. Caffe engine reads the face and extracts the feature then store it at caffe/models/face_id/features.

5. Evaluate application compare the L2 distance between the database and the feature.

6. If the system identified the face successfully, the log in information and the face will be recorded into log.txt and fold "Record", respectively.

7. Whether the system identified the face successfully or not, the system will go back to 3.


## Switch the extraction model 

1. Place the caffemodel under caffe/models/face_id/

2. Change the command in "run.sh"
```
e.g.  change
./build/tools/extract_features.bin /home/pi/caffe/models/face_id/caffe_mobilenet_without_mirror_train_iter_220000.caffemodel /home/pi/caffe/models/face_id/val.prototxt pool6 /home/pi/caffe/models/face_id/features 1 txt
```
```
into
 ./build/tools/extract_features.bin /home/pi/caffe/models/face_id/name_of_model.caffemodel /home/pi/caffe/models/face_id/val.prototxt pool6 /home/pi/caffe/models/face_id/features 1 txt
```

* If you change the model, remember the dimension of feature might be changed. In this repository, the model is mobilenet_v1 with alpha=0.25, so the dimension will be 256.

* Open evaluate.cpp and modify the variable "feature_dim" at line 14.


## Add new data into database

1. 

## Results




