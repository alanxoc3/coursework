import numpy as np
import csv, sys
import hardcoded as hc

# Splits a list into two, based on the percent
def split_by_percent(arr, percent):
	l = arr.__len__()
	split_ind = int(np.floor(l*percent/100))
	return np.split(arr, [split_ind])

# The percent of the items that match between the two arrays.
def calc_percentage(arr1, arr2):
	assert arr1.__len__() == arr2.__len__()
	l = arr1.__len__()
	num = np.sum(arr1 == arr2)
	return num / l * 100.0

# Runs a test on the robot multiple times.
def test_robot(data, target, featureNames, num_of_times, train_percent):
	percentages = []
	for x in range(num_of_times):
		# Shuffle the items!
		np_rand_state = np.random.get_state()
		np.random.shuffle(data)
		np.random.set_state(np_rand_state)
		np.random.shuffle(target)
		
		# Split data sets!
		data_1, data_2     = split_by_percent(data,   train_percent)
		target_1, target_2 = split_by_percent(target, train_percent)
	
		# Train with data/target 1
		robot = hc.HardCodedClassifier()
		robot.train( (data_1, target_1), featureNames )
		
		# Test with data/target 2
		test_arr = robot.predict(data_2)
		percentages.append(calc_percentage(test_arr, target_2))
	return percentages

def main():
	# Import iris from database, or CSV file.
	data, target, featureNames = [], [], []
	if sys.argv.__len__() > 1:
		data, target = open_file_discretized(sys.argv[1])
		featureNames = data.pop(0)
		target.pop(0)
	else:
		print ("You needed to provide a filename (CSV format).")
		return 1

	for x in range(0, len(data)):
		val1, val2, val3, val4 = 0, 0, 0, 0
		if data[x][0] >= 6.3:
			val1 = 6.3
		elif data[x][0] >= 5.4:
			val1 = 5.4
		else:
			val1 = 4.3

		if data[x][0] >= 3.2:
			val2 = 3.2
		elif data[x][0] >= 2.9:
			val2 = 2.9
		else:
			val2 = 2.0

		if data[x][0] >= 4.9:
			val3 = 4.9
		elif data[x][0] >= 3.0:
			val3 = 3.0
		else:
			val3 = 1.0

		if data[x][0] >= 1.6:
			val4 = 1.6
		elif data[x][0] >= 1.0:
			val4 = 1.0
		else:
			val4 = 0.1
		print("%.1f,%.1f,%.1f,%.1f,%d" % (val1, val2, val3, val4, target[x]))

	# list1 = []
	# for x in data:
		# list1.append(x[3])
# 
	# list1.sort()
# 
	# out = int(len(list1) / 3)
	# sub1 = list1[0:out]
	# sub2 = list1[out:out * 2]
	# sub3 = list1[out * 2:len(list1)]
# 
	# val1 = sub1[0]
	# val2 = sub2[0]
	# val3 = sub3[0]
# 
	# print ("The items are: ", val1, " and ", val2, " and ", val3)

# Opens the file, returns the data array and the target array.
def open_file_discretized(filename):
	data, target = [], []
	with open(filename, newline='') as csvfile:
		spamreader = csv.reader(csvfile, delimiter=',')
		for row in spamreader:
			data_elem, target_elem = np.split(row, [-1])
			data.append([float(elem) for elem in data_elem])
			target.append(int(target_elem[0]))
	return data, target

if __name__ == "__main__":
	main()
