import cv2
import numpy as np
import geometry as gm
import config as conf
import math


import time

'''
port = '/dev/ttyUSB0'  
baudrate = 115200  
timeout = 1  

try:
    ser = serial.Serial(port, baudrate, timeout=timeout)
    print(f"Порт {port} открыт.")
except Exception as e:
    port = '/dev/ttyUSB1'
    ser = serial.Serial(port, baudrate, timeout=timeout)
    print(f"Ошибка открытия порта: {port }")
    exit()
    
ser.reset_input_buffer()
ser.flush()
zero_t = time.time()

ser.write(f"Can i start".encode('utf-8'))
receive =""
last_receive = receive

while " Serial start " not in receive:
    
    receive = ser.readline().decode('utf-8')
    print(f"rec: {receive}")
    
    if receive != last_receive:
        
        ser.write(receive.encode('utf-8'))
        last_receive=receive
        print(f"send: {receive}")'''

time.sleep(0.101)
#receive = ser.readline().decode('utf-8')
#dt = time.time()*1000 - float(receive)



class CVobj:
    def __init__(self, global_bound, local_bound = None,mobility = True, shape = "ball", v_sect = True, color = ( 0, 200, 200) ):
        self.mod = mobility
        self.sahpe = shape
        self.glob_bound = global_bound
        self.glob_bool_img = None
        self.glob_contour = None
        self.glob_point = gm.point(0,0)
        self.draw_color = color
        
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
        for i in range(3,len(bound)):
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
    
    def calccont(self, bimg, join = 0):
        all_contours, _ = cv2.findContours(bimg, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        '''max_area = 0
        max_contour = None
        for contour in all_contours:
            area = cv2.contourArea(contour)
            if area > max_area:
                max_area = area
                max_contour = contour'''
                
        eee = sorted(all_contours, key=cv2.contourArea, reverse=True)
        if join >0:
            max_contour = np.vstack((eee[0], eee[1]))
        else:
            max_contour = eee[0]
        max_area = cv2.contourArea(max_contour)
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
                self.loc_contour, a =  self.calccont(self.loc_bool_img, join =2)
                cv2.drawContours(img, [self.loc_contour], 0, self.draw_color, 3)
            except:
                self.loc_bool_img = self.calcbool(self.sect, self.glob_bound)
                self.loc_contour, a =  self.calccont(self.loc_bool_img)
                cv2.drawContours(img, [self.loc_contour], 0, (255, 0, 0), 3)
        
        
            xx, yy = self.cent_cont(self.loc_contour)
            self.loc_point = gm.point(xx, yy)
            self.glob_point = self.loc_point + self.sect_point
            cv2.line(img, (point_center.x, point_center.y), (self.glob_point.x, self.glob_point.y), self.draw_color, 3)
            self.convert_glob_point =  gm.point(0,0)
            self.convert_glob_point.x = (point_center.y - self.glob_point.y)
            self.convert_glob_point.y = (point_center.x - self.glob_point.x)
            
            
            self.main_vec = gm.vec(endi = self.convert_glob_point)
            
            cv2.circle(img, img_center, 5, (250,255,100), 2)
            cv2.circle(img, (self.glob_point.x, self.glob_point.y), 10, self.draw_color, 2)
        except:
            print("None ball")
        
       
        
    
    
    @property
    def sect(self, iimg = None):
        return self.sect_ 
    
    @sect.setter  
    def sect(self, iimg):
        self.glob_bool_img = self.calcbool(iimg, self.glob_bound)
        cv2.imshow(f"ee3",self.glob_bool_img)
        
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
    field_parts = cv2.inRange(hsv_img, (36, 34, 133), (91, 255, 255))
    field_parts_cont, _ = cv2.findContours(field_parts, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    contour_areas = [(contour, cv2.contourArea(contour)) for contour in field_parts_cont]
    sorted_contours = sorted(contour_areas, key=lambda x: x[1], reverse=True)
    main_parts_field = []
    for i in range(min(2,len(sorted_contours))):
        cv2.drawContours(img, sorted_contours[i][0], -1, (0, 255, 0), 3)
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
blue_g = CVobj(global_bound = ( ((90, 90, 90), (255, 255, 255)), ), color = ( 200, 200, 0) )
yell_g = CVobj(global_bound = ( ((13, 98, 46), (30, 255, 255)), ) )
gyro = 0

L_g = 180


cur_ang = 0

separators = {' ', '\t', '\n', ',', ';'}

'''
while True:
    ret, img = cap.read() 
    cv2.imshow("all", img)
    ch = cv2.waitKey(5)
    if ch == 27:
        break'''

while True:
    
    ret, img = cap.read() 
    
    if ret == False:
        print("Zero img")
        break
    #img = fieldimg(img, img_center)
    cv2.circle(img, img_center, 50, (50,255,100), -1)
    for i in range(12):
        a = gm.vec(begi = point_center)
        a.leng = 40
        a.ang = i * math.pi/6 - math.pi/2
        a.calcang()
        cv2.line(img, (point_center.x, point_center.y),(int(a.end.x), int(a.end.y)) , (0,0,255), 3)
        
    
    
    
    #img = fieldimg(img, img_center)
    blue_g.sect = img
    yell_g.sect = img
    blue_g.calcang()
    yell_g.calcang()
    
    
    lol = gm.vec(begi = yell_g.main_vec.end, endi = blue_g.main_vec.end)
    cv2.imshow("all", img)
    
    
    b_a = abs(blue_g.main_vec.ang_) - lol.ang_
    y_a = 3.1415926 - abs(yell_g.main_vec.ang_) - lol.ang_
    d_g = abs(blue_g.main_vec.ang_ - yell_g.main_vec.ang_)
    b_c = L_g * math.sin(y_a) / math.sin(d_g)
    gg_x = 90 - math.cos(b_a)*b_c
    gg_y = math.sin(b_a)*b_c
    
    print(lol.ang_, round(b_c,3), round(b_a,3),round(y_a,3))
   
    '''
    while (ser.in_waiting > 0):
        receive = ser.readline().decode('utf-8')
        
    filtered_receive = [
    s for s in receive.split() 
    if s.strip() and not any(sep in s for sep in separators)
    ]
    gyro  = float(filtered_receive[0])
    #print(receive.split())
    cur_ang = round(cur_ang + 0.1 * (round(gm.between(0, ball.main_vec.ang - gyro),3) - cur_ang), 4)
    data_to_send = f" {round(cur_ang*-1000 - 6283)}, {int(ball.main_vec.leng_)}\n"
    print(f"raw: {round(gm.between(0, ball.main_vec.ang - gyro),3)} f: {cur_ang}")
    print(f"Rec: {receive} Gyr: {gyro}, ball: {ball.main_vec.ang}, len:{int(ball.main_vec.leng_)} , sum: {cur_ang}, send: {data_to_send}")
    
        
    ser.write(data_to_send.encode('utf-8'))'''
    
    ch = cv2.waitKey(5)
    if ch == 27:
        break
    
cap.release()
cv2.destroyAllWindows()

