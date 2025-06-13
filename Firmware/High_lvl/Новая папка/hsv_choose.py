import cv2
import numpy as np

if __name__ == '__main__':
    def nothing(*arg):
        pass
cv2.namedWindow( "img" )
cv2.namedWindow( "result" ) # создаем главное окно
cv2.namedWindow( "settings" ) # создаем окно настроек
camera = cv2.VideoCapture(0)
cv2.createTrackbar('h1', 'settings', 0, 255, nothing)
cv2.createTrackbar('s1', 'settings', 0, 255, nothing)
cv2.createTrackbar('v1', 'settings', 0, 255, nothing)
cv2.createTrackbar('h2', 'settings', 255, 255, nothing)
cv2.createTrackbar('s2', 'settings', 255, 255, nothing)
cv2.createTrackbar('v2', 'settings', 255, 255, nothing)
crange = [0,0,0, 0,0,0]
_, img = camera.read()
while True:
    '''ch = cv2.waitKey(5)
    if ch == 49:
        _, img = camera.read()'''
    _, img = camera.read()
    #img = cv2.imread('/home/pi/Desktop/anemo/korea.png', cv2.IMREAD_COLOR)
    img = cv2.resize(img, (640, 480))
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV) # считываем значения бегунков
    h1 = cv2.getTrackbarPos('h1', 'settings')
    s1 = cv2.getTrackbarPos('s1', 'settings')
    v1 = cv2.getTrackbarPos('v1', 'settings')
    h2 = cv2.getTrackbarPos('h2', 'settings')
    s2 = cv2.getTrackbarPos('s2', 'settings')
    v2 = cv2.getTrackbarPos('v2', 'settings') # формируем начальный и конечный цвет фильтра
    h_min = np.array((h1, s1, v1), np.uint8)
    h_max = np.array((h2, s2, v2), np.uint8) # накладываем фильтр на кадр в модели

    thresh = cv2.inRange(hsv, (h1, s1, v1), (h2, s2, v2))
    res = cv2.bitwise_and(img, img, mask=thresh)
    '''contours2 = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    contours2 = sorted(contours2, key=cv2.contourArea, reverse=True)
    if (len(contours2)):
        print(cv2.contourArea(contours2[0]))'''
    cv2.imshow('result', res)
    cv2.imshow('img', img)
    ch = cv2.waitKey(5)
    if ch == 27:
        print(f'({h1}, {s1}, {v1}), ({h2}, {s2}, {v2})')
        break
#camera.release()
cv2.destroyAllWindows()