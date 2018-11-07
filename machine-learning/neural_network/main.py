import numpy as np
import csv, sys
import hardcoded as hc
import parsehelper as ph

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
def test_robot(data, target, featureNames, classOrder, num_of_times, train_percent):
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

		robot.train( (data_1, target_1), classOrder )
		
		# Test with data/target 2
		test_arr = robot.predict(data_2)
		percentages.append(calc_percentage(test_arr, target_2))
	print("Here is the network taken from the last test: ")
	robot.print_network()
	return percentages

def main():
	# Import iris from database, or CSV file.
	data, target, featureNames = [], [], []
	if sys.argv.__len__() > 1:
		data, target = ph.open_file_normalized(sys.argv[1])
	else:
		print ("You needed to provide a filename (CSV format).")
		return 1

	try:
		num_of_times = int(input("How many times do you want to test the robot? "))
	except ValueError:
		num_of_times = 10
		print("Using 10.")

	try:
		train_percent = int(input("And what percentage of the data do you want to use to train the robot? "))
	except ValueError:
		train_percent = 70
		print("Using 70%.")

	if train_percent <= 0 or train_percent > 100:
		train_percent = 70
		print("Using 70%.")

	classOrder = [x for x in set(target)]
	percentages = test_robot(data, target, featureNames, classOrder, num_of_times, train_percent)

	print("Here are the percentages of how often the machine was right each time:")

	print(["{:.2f}".format(x) for x in percentages])

	print("\nMEAN: {:.2f}, MAX: {:.2f}, MIN: {:.2f}, MEDIAN: {:.2f}".format(
		np.mean(percentages),
		max(percentages),
		min(percentages),
		np.median(percentages)
	))

if __name__ == "__main__":
	main()
