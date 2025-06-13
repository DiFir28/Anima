import cv2
import numpy as np
import geometry as gm
import config as conf
import struct

import DF_ser as ser
import time

try:
    main_atm = ser.SerialTransmitter(port='/dev/ttyUSB0')
except:
    main_atm = ser.SerialTransmitter(port='/dev/ttyUSB1')




class CVobj:
    def __init__(self, global_bound, local_bound = None,mobility = True, shape = "ball", v_sect = True ):
        self.mod = mobility
        self.sahpe = shape
        self.glob_bound = global_bound
        self.glob_bool_img = None
        self.glob_contour = None
        self.glob_point = gm.point(0,0)
        
        self.sect_ = None
        self.ret = False
        self.sect_point = gm.point(0,0)
        self.sect_dx, self.sect_dy = 0, 0
        
        self.loc_bound = local_bound
        if local_bound == None:
            self.loc_bound = global_bound
        self.loc_bool_img = None
        self.loc_contour = None
        self.loc_point = gm.point(0,0)
        
        self.main_vec = gm.vec()
        
        for name, value in globals().items():
            if value is self:
                self.name_ = name
        else:
            self.name_="33"
    
    def calcbool(self, simg, bound):
        simg = cv2.cvtColor(simg, cv2.COLOR_BGR2HSV )
        res = cv2.inRange(simg,bound[0][0], bound[0][1])
        for i in range(1,len(bound)):
            res += res + cv2.inRange(simg,bound[i][0], bound[i][1])
        res[res>255]=255                
        return res
    
    def cent_cont(self, cont):
        moment = cv2.moments(cont)
        area = moment['m00']
        xm = moment['m01']
        ym =  moment['m10']
        y = int( xm/ area)
        x = int( ym/ area)
        return x , y
    
    def calccont(self, bimg):
        all_contours, _ = cv2.findContours(bimg, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        max_area = 0
        max_contour = None
        for contour in all_contours:
            area = cv2.contourArea(contour)
            if area > max_area:
                max_area = area
                max_contour = contour
        return max_contour, max_area
    
    def calcsection(self, contour, area):        
        if area <= 2:
            M = cv2.moments(contour)
            
            if M["m00"] != 0: 
                c_x = int(M["m10"] / M["m00"])
                c_y = int(M["m01"] / M["m00"])
            else:
                return 0, 0, img_w, img_h
        #else:
        #        return 0, 0, img_w, img_h
        x, y, w, h = cv2.boundingRect(contour)
        
        return max(x - 0.5 * w,0), max(y - 0.5 * h,0), min(x + 1.5 * w, img_w-1), min(y + 1.5 * h,img_h-1)
        
        #(center_x, center_y), radius = cv2.minEnclosingCircle(contour)
        
        #rotated_rect = cv2.minAreaRect(self.glob_contour)
        #box_points = np.int0(cv2.boxPoints(rotated_rect))  # Получаем координаты углов прямоуг
        #cropped_image = image[y1:y2, x1:x2]
    
    def calcang(self):
        
        try:
            try:
                self.loc_bool_img = self.calcbool(self.sect, self.loc_bound)
                self.loc_contour, a =  self.calccont(self.loc_bool_img)
                cv2.drawContours(img, [self.loc_contour], 0, (255, 0, 0), 3)
            except:
                self.loc_bool_img = self.calcbool(self.sect, self.glob_bound)
                self.loc_contour, a =  self.calccont(self.loc_bool_img)
                cv2.drawContours(img, [self.loc_contour], 0, (255, 0, 0), 3)
        
        
            xx, yy = self.cent_cont(self.loc_contour)
            self.loc_point = gm.point(xx, yy)
            self.glob_point = self.loc_point + self.sect_point
            self.convert_glob_point =  gm.point(0,0)
            self.convert_glob_point.x = (point_center.y - self.glob_point.y)
            self.convert_glob_point.y = (point_center.x - self.glob_point.x)
            
            
            self.main_vec = gm.vec(endi = self.convert_glob_point)
            
            cv2.circle(img, img_center, 5, (0,255,255), 2)
            cv2.circle(img, (self.glob_point.x, self.glob_point.y), 10, (0,0,255), 2)
        except:
            print("None ball")
        
       
        
    
    
    @property
    def sect(self, iimg = None):
        return self.sect_ 
    
    @sect.setter  
    def sect(self, iimg):
        self.glob_bool_img = self.calcbool(iimg, self.glob_bound)
        
        self.glob_contour , self.glob_contour_area = self.calccont(self.glob_bool_img)
        x1, y1, x2, y2 = map(int, self.calcsection(self.glob_contour, self.glob_contour_area))
        self.sect_point = gm.point(x1,y1)
        self.sect_= iimg[y1:y2,x1:x2].copy()
        
        try:
            
            cv2.imshow(f"ee",self.sect_)
        except:
            print(x1, y1, x2, y2)
            print("None of sect")
            
    
        
             
def fieldimg(img, img_center):
    
    cv2.circle(img, img_center, 5, (255,255,255), 1)
    cv2.circle(img, img_center, 338, (255,255,255), 200)
    #cv2.circle(img, img_center, 50, (255,255,255), -1)
    
    hsv_img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV )
    field_parts = cv2.inRange(hsv_img, (0, 40, 33), (91, 255, 255))
    field_parts_cont, _ = cv2.findContours(field_parts, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    contour_areas = [(contour, cv2.contourArea(contour)) for contour in field_parts_cont]
    sorted_contours = sorted(contour_areas, key=lambda x: x[1], reverse=True)
    main_parts_field = []
    for i in range(min(4,len(sorted_contours))):
        main_parts_field.append(sorted_contours[i][0])

    main_field_points = np.vstack([cnt for cnt in main_parts_field])

    field_hull = cv2.convexHull(main_field_points)
    mask = np.zeros_like(img[:,:,0])    
    cv2.drawContours(mask, [field_hull], -1, 255, -1)
    
    img = cv2.bitwise_and(img, img, mask=mask)
    return img

       
cap = cv2.VideoCapture(0)
ret, img = cap.read()
while ret == False:
    print("None img")
    ret, img = cap.read()
    
img_h, img_w, chan = map(int,img.shape)
point_center = gm.point(img_w // 2 + conf.center_dx,img_h // 2 + conf.center_dy)
img_center = (img_w // 2 + conf.center_dx,img_h // 2 + conf.center_dy)
ball = CVobj(global_bound = ( ((0, 71, 115), (44, 255, 255)), ), local_bound = ( ((0, 127, 72), (25, 255, 255)),) )
gyro = 0

cur_ang = 0

time.sleep(2)

while True:
    
    ret, img = cap.read() 
    
    if ret == False:
        print("Zero img")
        break
    
    cv2.circle(img, img_center, 50, (255,255,255), -1)
    
    #img = fieldimg(img, img_center)
    ball.sect = img
    b_ang = ball.calcang()
    
    
    cv2.imshow("all", img)

    data_to_send = f" {1}\n"  
        

    
   
    
    rets, receive = main_atm.read()
    print(receive)
    if (rets):
        gyro  = float(receive.split()[1])
    #print(receive.split())
    cur_ang = round(cur_ang + 0.1 * (round(gm.between(0, ball.main_vec.ang - gyro),3) - cur_ang), 4)
    data_to_send =  " "+f"{round(cur_ang*-1000 - 6283)}\n"
    print(f"raw: {round(gm.between(0, ball.main_vec.ang - gyro),3)} f: {cur_ang}")
    print(f"Rec: {receive} Gyr: {gyro}, ball: {ball.main_vec.ang}, sum: {cur_ang}, send: {round(cur_ang*-1000)}")
    main_atm.send(round(cur_ang*-1000),110,0)
        
    #ser.write(data_to_send.encode('utf-8'))
    
    ch = cv2.waitKey(5)
    if ch == 27:
        break
    
cap.release()
cv2.destroyAllWindows()

