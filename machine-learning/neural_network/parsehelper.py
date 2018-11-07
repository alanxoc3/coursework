import numpy as np
import math as m
import csv, sys

# Returns a new dataset that normalizes all the data based on Z-scores.
def normalize_data(data):
	# Transposed for ease and possibly better spacial locality.
	newData = np.transpose(data)
	normalizedData = []
	for dataPoint in newData:
		mean = calc_mean(dataPoint)
		deviation = calc_standard_deviation(dataPoint)
		normalizedData.append([(x - mean) / deviation for x in dataPoint])
	return np.transpose(normalizedData)

def calc_mean(data):
	return sum(data) / len(data)

# Returns the standard deviation for a 1-D array.
def calc_standard_deviation(data):
	mean = calc_mean(data)
	standard_deviation = m.sqrt(sum([(x - mean) ** 2 for x in data]) / (len(data) - 1))
	return standard_deviation

# Opens the file, returns the data array and the target array.
def open_file_discretized(filename):
	data, target = [], []
	with open(filename, newline='') as csvfile:
		spamreader = csv.reader(csvfile, delimiter=',')
		for row in spamreader:
			data_elem, target_elem = np.split(row, [-1])
			data.append(data_elem)
			target.append(target_elem[0])
	return data, target

# Opens the file, returns the data array and the target array.
def open_file_normalized(filename):
	data, target = [], []
	with open(filename, newline='') as csvfile:
		spamreader = csv.reader(csvfile, delimiter=',')
		for row in spamreader:
			data_elem, target_elem = np.split(row, [-1])
			data.append([float(elem) for elem in data_elem])
			target.append(target_elem[0])
	data = normalize_data(data)
	return data, target
