import numpy as np
def getborder(srart):
    res = []
    i = borders.index(srart)+1
    while(":" not in borders[i+1]):
        if "(" in borders[i]:
            bd =borders[i].split(")") 
            res.append( [list(map(int, bd[0][1:].split(", ")))])
        i+=1
    return res

#CV config



center_dx = 14
center_dy = -15

#Serial config

