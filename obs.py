
from mss import mss
import torch
import cv2
import numpy as np
import time
import keyboard
import serial
import mouse

#speed = int(input("speed: "))
#monitorY   = int(input ("monitorYaxis:   "))
#monitorX  = int(input ("monitorXaxis:   "))
#fovZ       =int(input("Fov:      "))

model = torch.hub.load(r'D:\3uTools\ai val\scripts\yolov5-master\yolov5-master', 'custom', path=r"D:\3uTools\ai val\1\valorant-v9.onnx", source='local').cuda()
arduino = serial.Serial("com8", "115200", timeout = 0)




def SendCordinates(code):
    code = str(code)
    arduino.write(str.encode(code))

def CalculateDistance(x,y): ## distance : (-100,100) -> "n,100,p,100*"
    if x < 0:
        x *=-1
        x_d = "n"
    else:
        x_d = "p"
    if y < 0:
        y*=-1
        y_d = "n"
    else:
        y_d = "p"

    x_v = int(x/4)
    y_v = int(y/4)
    code = x_d + "," + str(x_v) + "," + y_d + "," + str(y_v) + "*"
    
    #print(code)
    return code

if CalculateDistance == 0: 
 
            pass 
 
else: 
 
            # Reset distances array to prevent duplicating items 
 
    distances = [] 
 
    


with mss() as sct:
    #monitor = {"top" : monitorY / 2 - fovZ /2, "left": monitorX / 2 -fovZ /2, "width": monitorX / 2 + fovZ /2, "height": monitorY / 2 + fovZ/2}
    monitor = {"top": 476, "left": 896, "width": 128, "height":128}
    screenshot_center = [int((128)/2),int((128)/2)]
    activation_range = 100
    #Monitor = ("top" : Y / 2 - Z/2, "left": X / 2 -Z/2, "width": X / 2 + Z/2, "height": Y / 2 + Z/2)

    

    

    #model.conf = 0.60
    #model.maxdet = 10
    #model.apm = True


    
    while(True):
        screenshot = np.array(sct.grab(monitor))
        results = model(screenshot, size= 128)
        df= results.pandas().xyxy[0]
        closest = 100000
        closest_part = -1
        
        

        
        model.conf = 0.60
        model.maxdet = 10
        model.apm = True
        
        if len(results.xyxy[0]) != 0:
                df= results.pandas().xyxy[0]
                for i in range(len(results.xyxy[0])):
                    xmin = int(df.iloc[i,0])
                    ymin = int(df.iloc[i,1])
                    xmax = int(df.iloc[i,2])
                    ymax = int(df.iloc[i,3])

    
        
        
        try:
            xmin = int(df.iloc[0,0])
            ymin = int(df.iloc[0,1])
            xmax = int(df.iloc[0,2])
            ymax = int(df.iloc[0,3])

            head_level = (int(xmin + (xmax - xmin) / 2), int(ymin + (ymax - ymin) / 8))
            cv2.circle(screenshot, head_level, 4, (0,255,0), thickness = -1)
            cv2.rectangle(screenshot, (xmin, ymin), (xmax, ymax), (255,0,0), 2)

            distance = (head_level[0] - 64, head_level[1] - 64)
            #100 = 50
            #120 = 60
            #150 = 75
            #200 = 100
           

            
            if closest_part != -1:
                     xmin = df.iloc[closest_part,0]
                     ymin = df.iloc[closest_part,1]
                     xmax = df.iloc[closest_part,2]
                     ymax = df.iloc[closest_part,3]

             
            
            if keyboard.is_pressed('v'):
                code = CalculateDistance(int(distance[0]), int(distance[1]))
                SendCordinates(code)
                time.sleep(0) 
                


            if  keyboard.is_pressed('shift') and screenshot_center[0] in range(int(xmin),int(xmax)) and screenshot_center[1] in range(int(ymin),int(ymax)):
                keyboard.press_and_release('k')
                time.sleep(0.5)
                 
                

                
        except:
            print("",end="")
        
       
    
 
        #cv2.imshow("frame", screenshot)
        #if(cv2.waitKey(1) == ord('q')):
            #cv2.destroyAllWindows()
            #break