#!/usr/bin/env Rscript
# Author: Alan Morgan

library(datasets);
library(cluster)

# Send the output to a pdf!
pdf(file="clustering.pdf")

# We want to delete duplicates and scale.
data = na.omit(state.x77)
data = scale(data)

myClusters = kmeans(data, 3)
clusplot(data, myClusters$cluster,
	color=TRUE, shade=TRUE, labels=2, lines=0, main="3 cluster try")

# Determine number of clusters
wss <- (nrow(data)-1)*sum(apply(data,2,var))
for (i in 2:25) wss[i] <- sum(kmeans(data, 
  	centers=i)$withinss)
plot(1:25, wss, type="b", xlab="Number of Clusters",
  ylab="Within groups sum of squares")

myClusters = kmeans(data, 5)
myClusters
clusplot(data, myClusters$cluster,
	color=TRUE, shade=TRUE, labels=2, lines=0, main="3 cluster try")

dev.off()
