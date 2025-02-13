import cv2
import numpy as np


import config as const
import auxl as aux


class Base:
    # cam = cv2.VideoCapture(0)
    min_s = 0
    dx, dy = 5, 5

    def __init__(self, mask: [tuple, tuple]):
        self.min_v = mask[0]  # -> tuple
        self.max_v = mask[1]  # -> tuple
        self.frame_pos = aux.Point(0, 0)
        self.frame_center_pos = aux.Point(0, 0)
        self.field_pos = aux.Point(0, 0)

    def convert_coords(curr_pos) -> aux.Point:
        # convert px distance to real in meters
        # TODO : write this down
        return aux.Point(0, 0)

    def update(self, img) -> None:
        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        thresh1 = cv2.inRange(hsv, self.min_v, self.max_v)
        contours1 = cv2.findContours(thresh1, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)[1]
        if not contours1:
            self.frame_pos = aux.Point(1e9, 1e9)
        else:
            contours1 = sorted(contours1, key=lambda cc: -cv2.moments(cc)['m00'])
            (x, y, w, h) = cv2.boundingRect(contours1[0])
            nx, ny = max(0, x - self.dx), max(0, y - self.dy)  # moved
            xx = (nx, min(nx + w + 2 * self.dx, const.IMG_DIMENSIONS[0]) + 1)  # crop x range
            yy = (ny, min(ny + h + 2 * self.dy, const.IMG_DIMENSIONS[1]) + 1)  # crop y range
            w, h = xx[1] - xx[0], yy[1] - yy[0]

            hsv_crop = hsv[yy[0]: yy[1], xx[0]: xx[1]]
            thresh2 = cv2.inRange(hsv_crop, self.min_v, self.max_v)
            contours2 = cv2.findContours(thresh2, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)[-2]
            if not contours2:
                self.frame_pos = aux.Point(min(x + w // 2, const.IMG_DIMENSIONS[0]), min(y + h // 2, const.IMG_DIMENSIONS[1]))  # ??
            else:
                contours2 = sorted(contours2, key=lambda cc: -cv2.moments(cc)['m00'])
                (x2, y2, w2, h2) = cv2.boundingRect(contours2[0])
                self.frame_pos = aux.Point(x + w // 2, y + h // 2)
        self.frame_center_pos = aux.Point(self.frame_pos.x - const.IMG_DIMENSIONS[0], const.IMG_DIMENSIONS[1] - self.frame_pos.y)
        # self.field_pos = self.convert_coords(self.frame_center_pos)

    '''def ball_inside(self) -> bool:
        r1, r2 = 470, 620
        if r1 ** 2 >= ((self.frame_center_pos.x - const.IMG_DIMENSIONS[0]) ** 2 + (self.frame_center_pos.y - const.IMG_DIMENSIONS[1]) ** 2) >= r2 ** 2:
            return True
        return False'''


cam = cv2.VideoCapture(0)

ball = Base(const.MASK_BALL)
blue = Base(const.MASK_BLUE)

while True:
    img = cam.read()
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    ball.update(img)
    # blue.update(img)
    print(ball.frame_center_pos.mag())

    cv2.imshow('img', img)

    ch = cv2.waitKey(5)
    if ch == 27:
        break
# camera.release()
cv2.destroyAllWindows()