from collections import deque
import numpy as np
import math as m
import random

RAND_MIN = -1.0
RAND_MAX = 1.0

LEARNING_RATE = .01

# Contains:
# Value - The input value for a data point.
# List of nodes/weights - Each node in the list has a corresponding weight.
class Neuron(object):
	def __init__(self):
		self.value=-1
		self.connections={}
		self.deltas=[]

	def addNode(self, newNode, weight):
		self.connections[newNode] = weight

	def addDelta(self, delta):
		self.deltas.append(delta)

	def deltaSumAverage(self):
		if len(self.deltas) > 0:
			return sum(self.deltas) / len(self.deltas)
		else:
			return 0

	# Computes the each weighted input.
	def compute(self):
		return [indNode.value * weight for indNode, weight in self.connections.items()]

	def __str__(self):
		return "N(" + str(self.value) + ", " + str(self.deltaSumAverage()) + ")"

	def __repr__(self):
		return self.__str__()

# Given a list of neuron lists, attaches each column to the column left of it
# with random weights. Bias nodes are not attached, assuming those nodes are
# the first node in a layer.
def attach_neurons(network):
	# Start at the last list. And don't do the first list.
	# Because the input layer has no node children.
	for i in range(len(network) - 1, 0, -1):
		# Change the starting index based on if we are on the last layer.
		# This accounts for bias.
		startIndex = 1 if i < len(network) - 1 else 0

		# This loop goes through the current list.
		for j in range(startIndex, len(network[i])):
			# And this through the previous list. All previous lists have a bias
			# node.
			for k in range(0, len(network[i - 1])):
				# Finally add a random weight and node from the previous layer.
				randWeight = random.uniform(RAND_MIN, RAND_MAX)
				network[i][j].addNode(network[i - 1][k], randWeight)

# Input: "numOfNodesPerLayer" - An array where the first element is the number
#                               of attributes. The last is the number
#                               classifier types and the items in between are
#                               how large the hidden layers are.
#        "bias"               - A boolean, true if you want bias nodes, false
#                               otherwise.
# Given the number of nodes per layer, a deque of node lists are created. If
# bias nodes are enabled, then a bias node is placed as the first node of each
# list, except for the last one (the classifier list).
def create_neurons(numOfNodesPerLayer, bias=True):
	layers = []
	for i, x in enumerate(numOfNodesPerLayer):
		tmpBias = (i != len(numOfNodesPerLayer) - 1) and bias
		layers.append(list_to_neuron_list(x, tmpBias))
	return deque(layers)

# Creates one neuron for each feature. Used by the "create_neurons" function.
def list_to_neuron_list(numOfFeatures, bias):
	neurons = []
	if bias == True:
		neurons.append(Neuron())
	for x in range(numOfFeatures):
		neurons.append(Neuron())
	return neurons

# Works the inputs through the network, computing the sigmoid for each node. In
# addition, a table of all the computed sigmoid values is returned. Bias nodes
# are unaffected and not included in the table.
def feed_forward(network, dataPoint):
	# Store data point into inputs. The inputs get added to the saved inputs and
	# the network within the loop.
	inputs = [dataPoint[x] for x in range(len(dataPoint))]
	savedInputs = []

	for nodeIndex, nodeSet in enumerate(network):
		# Do nothing special if we are on the first item.
		if nodeIndex != 0:
			# Compute gives the array of input weight combos of the previous row.
			# So we sum up each row then perform a sigmoid function on it.
			inputs = [node.compute() for node in nodeSet]
			inputs = [sum(evalRow) for evalRow in inputs]
			inputs = [sigmoid_function(num) for num in inputs]

		# We want the bias offset to be zero on the output list.
		biasOffset = 1 if nodeIndex != len(network) - 1 else 0
		for i in range(biasOffset,len(nodeSet)):
			nodeSet[i].value = inputs[i - biasOffset]
		savedInputs.append(inputs)

	return savedInputs

def sigmoid_function(x):
	return 1 / (1 + m.e ** -x)

# Inputs are the actual output value and What It Should Have Been.
def delta_output_node(value, wishb):
	return value * (1 - value) * (value - wishb)

def delta_hidden_node(value, deltaSum):
	return value * (1 - value) * deltaSum

# Adds a new delta for each node in the network. A table of all the deltas
# added is returned as well. Bias nodes are unaffected and not included in the
# table. Input nodes are also unaffected and not included in the table.
def gen_deltas(network, targetIndex):
	savedDeltas = []
	# Go backwards, ignoring the input layer.
	for i in range(len(network) - 1, 0, -1):
		# The output layer is easier to calculate than the hidden layers.
		if i == len(network) - 1:
			for nodeIndex, node in enumerate(network[i]):
				# wishb - What It Should Have Been
				wishb = 1 if nodeIndex == targetIndex else 0
				delta = delta_output_node(node.value, wishb)
				node.addDelta(delta)

			# And save to the delta list.
			savedDeltas.append([deltaNode.deltas[-1] for deltaNode in network[i]])
		# And now for the hidden layers.
		else:
			#print("ERROR")
			# Going through each node in this list.
			for nodeIndex in range(1, len(network[i])):
				thisNode = network[i][nodeIndex]
				deltaSum = 0
				# Find the correct items in the previous list (the list to the right).
				for nextLayerNode in network[i+1]:
					if len(nextLayerNode.deltas) > 0 and len(nextLayerNode.connections) > 0:
						delta = nextLayerNode.deltas[-1]
						weight = nextLayerNode.connections[thisNode]
						deltaSum += delta * weight

				delta = delta_hidden_node(thisNode.value, deltaSum)
				thisNode.addDelta(delta)

			# And add to the saved deltas!
			deltaList = []
			for nodeIndex, node in enumerate(network[i]):
				if nodeIndex > 0:
					deltaList.append(node.deltas[-1])
			savedDeltas.append(deltaList)
	return savedDeltas

# Assuming that all the deltas have been computed, will average the deltas
# together and update the weights accordingly. Will also clear all the delta
# lists.
def updateWeights(network, learning_rate):
	for li, layer in enumerate(network):
		for ni, node in enumerate(layer):
			deltaSumAverage = node.deltaSumAverage()
			for indNode, weight in node.connections.items():
				node.connections[indNode] -= learning_rate * deltaSumAverage * indNode.value
			del node.deltas[:]

def trainIteration(network, dataPoint, targetPoint, classOrder):
	targetIndex = classOrder.index(targetPoint)
	# First, generate the input table and the output indexes.
	inputTable = feed_forward(network, dataPoint)
	#print("And network again: ", network)
	deltaTable = gen_deltas(network, targetIndex)
	#print("TAB: ", inputTable[-1], " - WISHB: ", targetIndex)

	output = [0 for x in range(len(classOrder))]
	output[targetIndex] = 1

	# Returns true if you reached the target.
	return inputTable[-1][targetIndex] == max(inputTable[-1])

# Give it a neural network as well as datapoint (1d array). This will return
# the class guessed.
def predict(network, dataPoint):
	# We only use the output inputs from the input table.
	inputs = feed_forward(network, dataPoint)[-1]

	# Then we find the max index and return that one.
	m = max(inputs)
	highIndexes = [i for i, j in enumerate(inputs) if j == m]
	return highIndexes[0]

def train(network, data, target, classOrder, learning_rate=LEARNING_RATE):
	numOfTrue, numOfFalse = 0, 0
	pastTrue = 0
	goodArr, tArr = [], []
	for it in range(100):
		for i in range(len(data)):
			output = trainIteration(network, data[i], target[i], classOrder)
			if output:
				numOfTrue += 1
			else:
				numOfFalse += 1
			updateWeights(network, learning_rate)

		if pastTrue != numOfTrue:
			#print("GOOD:", numOfTrue, "- BAD:", numOfFalse, "iter:", it)
			goodArr.append(numOfTrue / len(data))
			tArr.append(it)
			pastTrue = numOfTrue

		if numOfFalse == 0:
			break

		numOfTrue, numOfFalse = 0, 0

	print("GA:", goodArr)
	print("TA:", tArr)
