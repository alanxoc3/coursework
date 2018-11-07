#!/usr/bin/env Rscript
# Author: Alan Morgan

library(arules);
data(Groceries);

# itemFrequencyPlot(Groceries,topN=20,type="absolute")
rules <- apriori(Groceries, parameter = list(supp = 0.001, conf = 0.8))
options(digits=2)
inspect(rules[1:5])



# Include the SVM library
library (e1071)

# Load our old friend, the Iris data set
# Note that it is included in the default datasets library
library(datasets)

# Read the data
data_set <- read.csv("abalone.csv", head=TRUE, sep=",")

# Partition the data into training and test sets
# by getting a random 30% of the rows as the testRows
allRows = 1:nrow(data_set)
testRows <- sample(allRows, trunc(length(allRows) * 0.1))

# The test set contains all the test rows
data_set_test <- data_set[testRows,]

# The training set contains all the other rows
data_set_train <- data_set[-testRows,]

# Train an SVM model
# Tell it the attribute to predict vs the attributes to use in the prediction,
#  the training data to use, and the kernal to use, along with its hyperparameters.
#  Please note that "Species~." contains a tilde character, rather than a minus
model = svm(formula=Rings~., data = data_set_train, kernel="radial", gamma = 0.01, cost = 1900)

# Use the model to make a prediction on the test set
# Notice, we are not including the last column here (our target)
prediction = predict(model, data_set_test[,-9])

# Gotta round it!
for (i in 1:length(prediction)) {
	prediction[i] = round(prediction[i],0)
}

# Produce a confusion matrix
confusion_matrix = table(pred = prediction, true = data_set_test$Rings)

# Calculate the accuracy, by checking the cases that the targets agreed
agreement = prediction == data_set_test$Rings
accuracy = prop.table(table(agreement))

# Print our results to the screen
print(confusion_matrix)
print(accuracy)
