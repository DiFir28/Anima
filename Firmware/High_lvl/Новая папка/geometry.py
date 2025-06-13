import math

def sign(a):
    return (a > 0) * 2 - 1

class point:
    
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        return point(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        return point(self.x - other.x, self.y - other.y)
    
    def __iadd__(self, other):
        self = self + other
        return self
    
    def __isub__(self, other):
        self = self + other
        return self
    
    def set(self, x, y):
        self.x = x
        self.y = y

    def __tup__(self):
        return (self.x, self.y)
        
    def __str__(self):
        return f'{self.x}, {self.y}'
    
    def copy(self):
        return point(self.x, self.y)
    
    def __getitem_(self, ite):
        m = [self.x, self.y]
        return m[ite]
     
def tup(a: point)-> tuple: 
    return (a.x , a.y)
    
     
    
class vec():
    
    def __init__(self, begi = point(0,0), endi = point(0,0),):
        self.beg = begi
        self.end = endi
        self.leng_, self.ang_ = 1.0 , 0.0
        self.dx_ = self.end.x - self.beg.x
        self.dy_ = self.end.y - self.beg.y
        self.calcang()
        
        
    
    def calcdx(self):
        return self.end.x - self.beg.x
    
    def calcdy(self):
        return self.end.y - self.beg.y
    
    def calcdxy(self):
        return point(self.calcdx(), self.calcdy())
    
    def calcang(self):
        self.dx_ = self.calcdx()
        self.dy_ = self.calcdy()
        self.leng_ = math.hypot(self.dx_, self.dy_)
        self.ang_ = round(math.atan2(abs(self.dy_), abs(self.dx_)),4)
        if (self.dx_ <0):
            self.ang_= math.pi - self.ang_
        if (self.dy_ <0):
            self.ang_  = -self.ang_
        self.ang_  = between(0,self.ang_)
         
            
        
    def calcxy(self):
         
         self.end.x = self.beg.x + self.leng_ * math.cos(self.ang_)
         self.end.y = self.beg.y + self.leng_ * math.sin(self.ang_)
         self.dx_ = self.calcdx()
         self.dy_ = self.calcdy()
         
    
    @property
    def dx(self, val = None):
        return self.dx_      
    @dx.setter    
    def dx(self, val):        
        self.end.x = self.beg.x + val
        self.calcang()
        
    @property
    def dy(self, val = None):
        return self.dy_      
    @dx.setter    
    def dy(self, val):        
        self.end.y = self.beg.y + val
        self.calcang()
    
    @property
    def begx(self, val = None):
        return self.beg.x      
    @begx.setter    
    def begx(self, val):      
        self.beg.x = val
        self.calcang()
        
    @property
    def begy(self, val = None):
        return self.beg.y      
    @begy.setter    
    def begy(self, val):        
        self.beg.y = val
        self.calcang()    
         
    @property
    def endx(self, val = None):
        return self.end.x      
    @endx.setter    
    def endx(self, val):        
        self.end.x = val
        self.calcang()
        
    @property
    def endy(self, val = None):
        return self.end.y     
    @endy.setter    
    def endy(self, val):        
        self.end.y = val
        self.calcang()
         
    @property
    def ang(self, val = None):
        return self.ang_     
    @ang.setter    
    def ang(self, val):        
        self.ang_ = val
        self.calcxy()
        
    @property
    def leng(self, val = None):
        return self.leng_     
    @ang.setter    
    def leng(self, val):        
        self.leng_ = val
        self.calcxy()
    
        
    def __add__(self, other):
        
        ret = vec(self.beg.x, self.beg.y, self.end.x, self.end.y)
        
        ret.end.x += other.dx_
        ret.end.y += other.dy_
        ret.calcang()
        
        return  ret
    
    def __sub__(self, other):
        
        ret = vec(self.beg.x, self.beg.y, self.end.x, self.end.y)
        
        ret.end.x -= other.dx_
        ret.end.y -= other.dy_
        ret.calcang()
        
        return  ret
    
    def __iadd__(self, other):
        self = self + other
        return self
    
    def __isub__(self, other):
        self = self + other
        return self
    
    def __mul__(self, other):
        
        return (self.dx_ * other.dx_ + self.dy_ * other.dy_)
    
    def __matmul__(self, other):
        
        return (self.dx_ * other.dy_ - self.dy_ * other.dx_)
    
    def __xor__(self, other):
    
        ret = math.acos((self * other) / (self.leng_ * other.leng_))
        if other.dx_ == 0:
            ret *= sign(other.dy_)
        
        elif self.dy_ * other.dx_ / self.dx_ < other.dy_ :
            ret = -ret
        
        return ret
    
    def __str__(self):
        return f"{self.dx_} {self.dy_}"
    
    
def between(a, b):
    ret = b-a
    ret-=round(ret/(math.pi*2)) * 2 * math.pi
    return ret
    #def __init__(self):
        
    
   ###def __init__(self, *bx = 0, *by = 0, *ex = 0, *ey = 0):
###    self.beg.set(bx, by)
###        self.end.set(ex, ey)
    
      
if __name__ == "__main__":
    a = vec(endi = point(3,3))
    p = point(3,3)
    print(tup(p), a.leng, a.leng_, a.dx_, a.dy_, math.hypot(a.dx_, a.dy_))
    

