import numpy as np
import math
import operator
import neuralalg as na

i = 1

# A wrapper for various machine learning algorithms.
class HardCodedClassifier(object):
	def __init__(self):
		self.network = None
		self.classOrder = []
	
	# Train the data. Previous trains will be overwritten.
	def train(self, info, classOrder):
		global i
		# Check if there is info
		if len(info[0]) > 0:
			self.featureLen = len(info[0][0])
		else:
			return None

		# Get one array of the class names (so we have an order).
		self.classOrder = classOrder

		print('------------ hidden size of', i, '---------------------')
		self.network = na.create_neurons([self.featureLen, i, len(self.classOrder)])
		na.attach_neurons(self.network)
		print(self.network)
		na.train(self.network, info[0], info[1], self.classOrder, learning_rate=.01)

		i += 1

		return self.network

	# Predict the data
	def predict(self, instances):
		target = []
		for row in instances:
			ind = na.predict(self.network, row)
			target.append(self.classOrder[ind] if ind != None else None)
		return target

	def print_network(self):
		#print(self.network)
		pass
