import math


class Point:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y
        self.angle = self.arg()
        self.length = self.mag()
    
    def __add__(self, p: "Point") -> "Point":
        if p is None:
            return self
        return Point(self.x + p.x, self.y + p.y)
    
    def __neg__(self) -> "Point":
        return Point(-self.x, -self.y)
    
    def __sub__(self, p: "Point") -> "Point":
        return self + -p
    
    def __mul__(self, n: float) -> "Point":
        return Point(self.x * n, self.y * n)
    
    def __truediv__(self, n: float) -> "Point":
        return self * (1 / n)

    def __pow__(self, n: float) -> "Point":
        return Point(self.x ** n, self.y ** n)
    
    def __eq__(self, p: "Point") -> bool:
        if isinstance(p, Point):
            return False
        return self.x == p.x and self.y == p.y

    def __str__(self) -> str:
        return f"x = {self.x:.2f}, y = {self.y:.2f}"
    
    
    def mag(self) -> float:
        # length
        return math.hypot(self.x, self.y)
    
    def arg(self) -> float:
        # angle to ox -> ! rad !
        return math.atan2(self.y, self.x)
    
    def unity(self) -> "Point":
        # collinear unit vector
        if self.mag() == 0:
            return self
        return self / self.mag()

    def dist2line(p: "Point", p1: "Point", p2: "Point") -> float:
        # dist from p to (p1, p2)
        return abs(Point.mult_vec((p2 - p1).unity(), p - p1))
    
    def dist(a: "Point", b: "Point") -> float:
        # distance between points
        return math.hypot(a.x - b.x, a.y - b.y)
    
    def mult_vec(a: "Point", b: "Point") -> float:
        # vector multiplication
        return a.x * b.y - a.y * b.x
    
    def mult_scal(a: "Point", b: "Point") -> float:
        # scalar multiplication
        return a.x * b.x + a.y * b.y
    
    def rotate(p: "Point", alpha: float) -> "Point":
        # vector rotation
        return Point(p.x * math.cos(alpha) - p.y * math.sin(alpha), p.y * math.cos(alpha) + p.x * math.sin(alpha))
    
    def normalize_angle(alpha: float) -> float:  # alpha - deg
        # angle [-pi, pi]
        alpha = alpha % (2 * math.pi)
        if alpha > math.pi:
            alpha -= 2 * math.pi
        return alpha
    
    def angle_2points(p1: "Point", p2: "Point") -> float:  # angle vec [point2 to point1] to ox
        return (p2 - p1).arg()
    
    def point_on_line(fromm: "Point", too: "Point", dist: float) -> "Point":
        # point on line (fromm, too) from p.fromm on dist
        angle_vec = math.atan2(too.y - fromm.y, too.x - fromm.x)
        new_x = fromm.x + dist * math.cos(angle_vec)
        new_y = fromm.y + dist * math.sin(angle_vec)
        return Point(new_x, new_y)
