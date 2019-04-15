import numpy as np
import math
file = open("/home/pi/caffe/models/face_id/features/pool6.txt","r")

a=file.read().split(" ")
b=a[:-1]
print(len(b))
#b is the features
file2 = open("/home/pi/caffe/models/face_id/features_3/pool6.txt","r")

c=file2.read().split(" ")
d=c[:-1]
print(len(d))



print(b[100])
print(d[100])

b=np.asarray(b,"float")
d=np.asarray(d,"float")


print(b.shape)
print(d.shape)


sumb=0
for i in range(len(b)):
    sumb=sumb+b[i]*b[i];
#sumb = math.sqrt(sumb)

sumd=0
for j in range(len(d)):
    sumd=sumd+d[j]*d[j];
#sumd = math.sqrt(sumd)

sumbd=0
for k in range(len(d)):
    sumbd=sumbd+b[j]*d[j];
    

l2=math.sqrt(abs(sumb-sumd))
print(l2)

