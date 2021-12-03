import math

def dist(x1, y1, x2, y2):
    return math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)

def make_circle(tiles, cx, cy, r):
    for x in range(cx - r, cx + r):
        for y in range(cy - r, cy + r):
            if dist(cx, cy, x, y) <= r:
                tiles[x][y] = 1

width = 50
height = 50

cx = width // 2
cy = height // 2
r = 23

tiles = [[0 for _ in range(height)] for _ in range(width)]

make_circle(tiles, cx, cy, r)

print("\n".join("".join(map(str, i)) for i in tiles))
