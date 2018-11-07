#!/usr/bin/env Rscript
# Alan Morgan - Machine Learning

# Include the SVM library
library (e1071)

# Load our old friend, the Iris data set
# Note that it is included in the default datasets library
library(datasets)

# Read the data
data_set <- read.csv("vowel.csv", head=TRUE, sep=",")

# Partition the data into training and test sets
# by getting a random 30% of the rows as the testRows
allRows = 1:nrow(data_set)
testRows <- sample(allRows, trunc(length(allRows) * 0.3))

# The test set contains all the test rows
data_set_test <- data_set[testRows,]

# The training set contains all the other rows
data_set_train <- data_set[-testRows,]

# Train an SVM model
# Tell it the attribute to predict vs the attributes to use in the prediction,
#  the training data to use, and the kernal to use, along with its hyperparameters.
#  Please note that "Species~." contains a tilde character, rather than a minus
model = svm(formula=Class~., data = data_set_train, kernel="radial", gamma = 0.001, cost = 1500)

# Use the model to make a prediction on the test set
# Notice, we are not including the last column here (our target)
prediction = predict(model, data_set_test[,-13])

# Produce a confusion matrix
confusion_matrix = table(pred = prediction, true = data_set_test$Class)

# Calculate the accuracy, by checking the cases that the targets agreed
agreement = prediction == data_set_test$Class
accuracy = prop.table(table(agreement))

# Print our results to the screen
print(confusion_matrix)
print(accuracy)
