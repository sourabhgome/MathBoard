import cv2
import numpy as np
import pyautogui
from PIL import Image
import keyboard

screen_size=pyautogui.size()

fourcc=cv2.VideoWriter_fourcc(*"XVID")
out=cv2.VideoWriter("C:\\qteg\\Painter\\Recordings\\temp\\output.avi",fourcc,20,(screen_size))
cursor=Image.open("C:\\qteg\\Painter\\images\\pencil_cursor1.png")
cursor=cursor.resize((32,32))

while True:
 #img=pyautogui.screenshot()
 img=pyautogui.screenshot()
 x,y=pyautogui.position()
 img.paste(cursor,(x,y),cursor.convert("RGBA"))
 frame=np.array(img)
 frame=cv2.cvtColor(frame,cv2.COLOR_BGR2RGB)
 out.write(frame)
 #cv2.imshow("screenshot",frame)
 #if cv2.waitKey(1) == ord("q"): break
 if keyboard.is_pressed('q'): break
 
cv2.destroyAllWindows()
out.release()