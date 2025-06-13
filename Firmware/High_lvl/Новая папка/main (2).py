import CVobj
import cv2
import config as conf
import DF_ser as ser

cap = cv2.VideoCapture(0)
ret, img = cap.read()
while ret == False:
    pritn("None img")
    ret, img = cap.read()
    
img_h, img_w, chan = map(int,img.shape)
img_center = (img_w // 2 + conf.center_dx,img_h // 2 + conf.center_dy)

while True:
    
    ret, img = cap.read() 
    
    if ret == False:
        print("Zero img")
        break
    
    img = CVobj.fieldimg(img, img_center)
    cv2.imshow("Field", img)
    
    ball =  CVobj.CVobj(global_bound = conf.GbB)
    ball.sect =img
    cv2.imshow("gbool", ball.glob_bool_img)
   
    
    
    
    ch = cv2.waitKey(5)
    if ch == 27:
        break
    
cap.release()
cv2.destroyAllWindows()


'''
    
    

    hsv_img = cv2.cvtColor(img, cv2.COLOR_BGR2HSV )
    boo = cv2.inRange(hsv_img, (55, 93, 102), (89, 255, 255))
    
    
    
    contours, _ = cv2.findContours(boo, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    contour_areas = [(contour, cv2.contourArea(contour)) for contour in contours]
    sorted_contours = sorted(contour_areas, key=lambda x: x[1], reverse=True)
    fd = []
    for i in range(4):
        fd.append(sorted_contours[i][0])
    for i in fd:    
        cv2.drawContours(img, [i], -1, (255,0,255), 3)
    
    ball = CVobj(global_bound = conf._BL_bound, local_bound = conf._BL_)
    ball.sect = img
    all_points = np.vstack([cnt for cnt in fd])

    hull = cv2.convexHull(all_points)
    mask = np.zeros_like(img[:,:,0])
    
    # Закрашиваем контур белым цветом (255)
    cv2.drawContours(mask, [hull], -1, 255, -1)
    
    # Применяем маску к изображению
    img = cv2.bitwise_and(img, img, mask=mask)
    cv2.drawContours(img, [hull], -1, (200,200, 200), 3)
    
    
    bbb = ball.calcbool(ball.sect, ball.loc_bound)
    
    cv2.imshow("bool", bbb)
    cv2.imshow("gbool", ball.glob_bool_img)
    cv2.imshow("go", img)'''