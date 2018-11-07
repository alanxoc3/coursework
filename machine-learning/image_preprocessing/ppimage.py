#!/usr/bin/env python2.7
# Author: Alan Morgan

import sys, os, tarfile, shutil
from PIL import Image

PREPEND_NAME = ".ppimage."
SIZE = 200

# Extracts all the images to the /tmp directory, and returns a list of the
# filepaths for each one.
def untar(tarFileName):
	dirName = "/tmp/" + PREPEND_NAME + tarFileName + "/"
	tf = tarfile.open(name=tarFileName)

	if os.path.exists(dirName):
		shutil.rmtree(dirName)

	os.makedirs(dirName)
	tf.extractall(dirName)

	return (dirName, tf.getnames())

# Takes a file name, new width and new height.
# This takes a file name and combines scaling and cropping of the image to
# resize the image. The file is replaced by the transformation.
# Returns true if the size was good, false if the size was too small.
def preprocess(fileName, wh):
	img = Image.open(fileName)
	iW = img.size[0]
	iH = img.size[1]
	minDim = min(iW, iH)

	if minDim < wh:
		return False
	else:
		if iW == minDim:
			# Crop along Y
			offset = (iH - minDim) / 2
			img = img.crop( (0, offset, minDim, offset + minDim) )
		elif iH == minDim:
			# Crop along X
			offset = (iW - minDim) / 2
			img = img.crop( (offset, 0, offset + minDim, minDim) )
		else:
			print fileName, "is already Square, just scaling."

	img.thumbnail( (wh, wh), Image.ANTIALIAS )
	assert(img.size[0] == wh and img.size[1] == wh)
	img.save(fileName, 'JPEG')
	return True

# Returns how many images were too small, and how many images there were total
# (good images + too small images).
def loop_images(dirName, fileNames, outTar, size=SIZE):
	smallCount = 1.0
	totalCount = 1.0
	for fn in fileNames:
		totalCount += 1
		goodSize = preprocess(dirName + fn, size)
		if not goodSize:
			smallCount += 1
			#print "Image", fn, "is too small, removing it from the dataset."
			os.remove(dirName + fn)

	tf = tarfile.open(outTar, "w")
	try:
		for x in os.listdir(dirName):
			print x
			tf.add(dirName + x, arcname=x)
	finally:
		tf.close()
	return (smallCount, totalCount)

def run():
	if len(sys.argv) > 2:
		# Check if directory exists.
		outDirName = sys.argv[-1] + '/'
		if not os.path.exists(outDirName):
			print "Error: The directory", outDirName, "doesn't exist."
			return

		allSmallCount = 0.0
		allCount = 0.0
		for i in xrange(1,len(sys.argv) - 1):
			print "Converting", sys.argv[i]
			dirName, fileNames = untar(sys.argv[i])

			smallCount, totalCount = loop_images(dirName, fileNames, outDirName + sys.argv[i])
			allSmallCount += smallCount
			allCount += totalCount
			print smallCount / totalCount, " percent of images were too small"
			
			if os.path.exists(dirName):
				shutil.rmtree(dirName)

		print "And the total percent of images that were too small is:", allSmallCount / allCount
	else:
		print "Usage: ppimage [files.tar] [output_directory]"

if __name__=='__main__':
	run()
