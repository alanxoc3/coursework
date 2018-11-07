import numpy as np
import math
import operator
import decision_algorithm as da

# The machine learning class
class HardCodedClassifier(object):
	def __init__(self):
		pass
	
	# Takes a tuple of a data array, then a target array
	def train(self, trainSet, featureNames):
		self.tree = da.make_tree(trainSet[0], trainSet[1], featureNames)
		return self.tree
	
	def predict(self, instances):
		return [da.traverse(self.tree, list(row)) for row in instances]

	def print_tree(self):
		da.print_traverse(self.tree, 0)
		
