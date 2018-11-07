import numpy as np
import math
import operator

def euclideanDistance(thing1, thing2, length):
	distance = 0
	for x in range(length):
		distance += pow((thing1[x] - thing2[x]), 2)
	return math.sqrt(distance)

# trainSet     = items to use.
# testInstance = item to try.
# k            = number of neighbors.
# Try it with the testInstance not in the trainSet.
def getNeighbors(trainSet, testInstance, k):
	distances = []
	length = len(testInstance) - 1
	for x in range(len(trainSet)):
		dist = euclideanDistance(testInstance, trainSet[x], length)
		distances.append((trainSet[x], dist))
	distances.sort(key=operator.itemgetter(1))
	neighbors = []
	for x in range(k):
		neighbors.append(distances[x][0])
	return neighbors

# Explanation:
# Assuming that the testInstance doesn't contain the classification and the
# train set does, figure out the distance for each item in the training set.
# Sort all those distances and add only the smallest ones to the return list of
# nearest neighbors.

def getMajority(neighbors):
	dic = {}
	for x in neighbors:
		i = x[-1]
		if dic.get(i) != None:
			dic[i] += 1
		else:
			dic[i] = 1
	
	majority = 0
	
	for x in dic.items():
		if majority < x[1]:
			majority = x[1]
			item = x[0]
	return item

# The machine learning class
class HardCodedClassifier(object):
	def __init__(self):
		pass
	
	# Takes a tuple of a data array, then a target array
	def train(self, trainSet):
		trainSet[1].reshape((-1,1))
		self.trainSet = np.concatenate( (trainSet[0], trainSet[1].reshape((-1,1))), axis=1 )
	
	def predict(self, instance, k):
		return [getMajority(getNeighbors(self.trainSet, x, k)) for x in instance]
