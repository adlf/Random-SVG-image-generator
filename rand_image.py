#!/usr/bin/env python

from random import randrange as r

IMAGE_WIDTH=500
IMAGE_HEIGHT=500
STROKE=2
MAX_SHAPES=16
OPACITY=1.0

rand_color = lambda: '#'+''.join(['abcdef1234567890'[r(15)] for _ in range(6)])

BACKGROUND=rand_color()

def write(filename):
	txt = "<?xml version='1.0'?>"
	txt += "<svg width='%s' height='%s'>" % (IMAGE_WIDTH,IMAGE_HEIGHT)
	txt += "<rect height='%s' width='%s' fill='%s'/>" % (\
		IMAGE_HEIGHT, IMAGE_WIDTH, BACKGROUND)

	txt += ''.join("%s" % rand_shapes() for _ in range(MAX_SHAPES))

	open(filename,"w").write(txt+"</svg>")

def rand_shapes():
	shape = r(4)
	text = ""
	if not shape:
		text += "<rect x='%s'" % (r(IMAGE_WIDTH))
		text += " y='%s'" % (r(IMAGE_HEIGHT))
		text += " width='%s'" % (r(IMAGE_WIDTH/2))
		text += " height='%s'" % (r(IMAGE_WIDTH/2))
	elif shape == 1:
		text += "<circle cx='%s'" % (r(IMAGE_WIDTH))
		text += " cy='%s'" % (r(IMAGE_HEIGHT))
		text += " r='%s'" % (r(min(IMAGE_WIDTH, IMAGE_HEIGHT)/4))
	elif shape == 2:
		text += "<ellipse cx='%s'" % (r(IMAGE_WIDTH))
		text += " cy='%s'" % (r(IMAGE_HEIGHT))
		text += " rx='%s'" % (r(IMAGE_WIDTH/2))
		text += " ry='%s'" % (r(IMAGE_WIDTH/2))
	else:
		text += "<polyline points='"
		for _ in range(1,r(6)+3):
			text += "%s %s, " % (r(IMAGE_WIDTH),r(IMAGE_WIDTH))
		text += "'"

	if (r(2) == 0 and shape != 3):
		text += " fill='%s' fill-opacity='%s'/>" % (rand_color(), OPACITY) 
	else:
		text += " fill='none' stroke-width='%s'" % (STROKE)
		text += " stroke='%s' stroke-opacity='%s'/>" % (rand_color(), OPACITY)
		
	return text

if __name__ == '__main__':
	write("image.svg")