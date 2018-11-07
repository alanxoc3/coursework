import numpy as np
import csv, sys
import hardcoded as hc
from sklearn.neighbors import KNeighborsClassifier

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
def test_robot(data, target, num_of_times, train_percent, k):
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
	
		# Train and run the robot
		classifier = KNeighborsClassifier(n_neighbors=k)
		classifier.fit(data_1, target_1)
		test_arr = classifier.predict(data_2)

		percentages.append(calc_percentage(test_arr, target_2))
	return percentages

def main():
	# Import iris from database, or CSV file.
	data, target = [], []
	if sys.argv.__len__() > 1:
		data, target = open_file(sys.argv[1])
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

	try:
		k = int(input("What will you want k to be? (Default is 3) "))
	except ValueError:
		k = 3
		print("Using 3.")

	if train_percent <= 0 or train_percent > 100:
		train_percent = 70
		print("Using 70%.")

	percentages = test_robot(data, target, num_of_times, train_percent, k)

	print("Here are the percentages of how often the machine was right each time:")

	print(["{:.2f}".format(x) for x in percentages])

	print("\nMEAN: {:.2f}, MAX: {:.2f}, MIN: {:.2f}, MEDIAN: {:.2f}".format(
		np.mean(percentages),
		max(percentages),
		min(percentages),
		np.median(percentages)
	))

# Opens the file, returns the data array and the target array.
def open_file(filename):
	data, target = [], []
	with open(filename, newline='') as csvfile:
		spamreader = csv.reader(csvfile, delimiter=',')
		for row in spamreader:
			data_elem, target_elem = np.split(row, [-1])
			data.append(list(map(float, data_elem)))
			target.append(int(target_elem[0]))
	return data, target

if __name__ == "__main__":
	main()
