import os
import cv2

path = 'c:\\qteg\\Painter\\images\\png1\\'

files = []
for r, d, f in os.walk(path):
 for file in f:
  if '.png' in file:
   files.append(os.path.join(r, file))

i=0
for f in files:
 i=i+1
 img=cv2.imread(f,cv2.IMREAD_UNCHANGED);
 for x in img:
  for y in x:
   if(y[3]!=0):
    y[0]=221
    y[1]=221
    y[2]=221
 s="c:\\qteg\\Painter\\images\\png\\"+str(i)+".png"
 cv2.imwrite(s,img)
 print(s)
