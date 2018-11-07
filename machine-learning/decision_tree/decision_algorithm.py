import numpy as np
from collections import Counter

# Inputs are:
# data, a 2D array (matrix) of each data point as a row.
# classes are a list that contains each data point's class.
# feature is the column index of which index.
def calc_entropy(data, classes, feature):
	possibleValues = []
	entropy = 0
	# Get possible values for "feature" first
	for datapoint in data:
		if datapoint[feature] not in possibleValues:
			possibleValues.append(datapoint[feature])
	# calculate weighted entropy for each possible value.
	for value in possibleValues:
		weightNumerator = 0
		dataInd = 0
		classDict = {}
		# loop to find the probability and the class count for this value.
		for datapoint in data:
			if datapoint[feature] == value:
				# add to numerator of probability.
				weightNumerator += 1
				# add to classes and the class number.
				if classes[dataInd] not in classDict:
					classDict[classes[dataInd]] = 1
				else:
					classDict[classes[dataInd]] += 1
			# increment the index, needed to calculate class stuff above.
			dataInd += 1
		# now generate a list of all the probabilities.
		weight = weightNumerator / len(data)
		classDenominator = weightNumerator
		probs = []
		probs = [dicVal / classDenominator for dicVal in classDict.values()]
		entropy += calc_weighted_entropy(weight, probs)
	return entropy

# Inputs are the weight (a decimal) and probabilities (an array of
# probabilities that all add up to one).
def calc_weighted_entropy(weight, probs):
	prob_sum = 0
	for p in probs:
		prob_sum += calc_entropy_of_probability(p)
	return weight * prob_sum

# Returns the entropy, given the probability of a given class being positive.
def calc_entropy_of_probability(p):
	if p > 0:
		return -p * np.log2(p)
	else:
		return 0

def make_tree(data, classes, featureNames):
	featureIndexes = [x for x in range(0, len(featureNames))]
	if len(data) == 0:
		return {}
	else:
		return make_tree_rec(data, classes, featureIndexes)

# Now we are onto the tree construction algorithm.
def make_tree_rec(data, classes, featureIndexes):
	entropyVals = [calc_entropy(data, classes, feature) for feature in range(0, len(featureIndexes))]
	entropyTotal = 0

	for x in entropyVals:
		entropyTotal += x

	# Should only test this the first time. Return the mode.
	if not featureIndexes or entropyTotal == 0:
		counter = Counter(classes)
		return counter.most_common(1)[0][0]
		#return max(set(list(classes)), key=list.count)

	# Next, find the index of the minimum entropy for the features.
	featureIndex = 0
	curEntropy = entropyTotal
	for x in range(0, len(featureIndexes)):
		entropy = calc_entropy(data, classes, x)
		if entropy < curEntropy:
			featureIndex = x

	# And delete that spot.
	del featureIndexes[featureIndex]

	# Create a tree
	newTree = {}
	possibleValues = []

	for dataPoint in data:
		if dataPoint[featureIndex] not in possibleValues:
			possibleValues.append(dataPoint[featureIndex])

	for value in possibleValues:
		dataSubset = []
		classSubset = []
		for x in range(0, len(data)):
			if data[x][featureIndex] == value:
				dataSubset.append(data[x])
				classSubset.append(classes[x])
		# Create a branch
		branch = make_tree_rec(dataSubset, classSubset, featureIndexes)
		newTree[value] = branch
	return (featureIndex, newTree)

def traverse(node, dataPoint):
	if type(node) is tuple:
		if dataPoint[node[0]] in node[1]:
			return traverse(node[1][dataPoint[node[0]]], dataPoint)
		else:
			print("You see this, because a foreign input was entered. This will skew your results.")
			return -1
	else:
		return node

def print_traverse(node, num_of_spaces):
	if type(node) is tuple:
		print(" " * num_of_spaces, "Question Number:", node[0])
		num_of_spaces += 1
		
		for x in range(0, len(node[1].keys())):
			print(" " * num_of_spaces, "Answer:", list(node[1].keys())[x])
			num_of_spaces += 1
			print_traverse(node[1][list(node[1].keys())[x]], num_of_spaces)
			num_of_spaces -= 1
	else:
		print(" " * num_of_spaces, "Value: ", node)
