#!/usr/bin/env Rscript
# Author: Alan Morgan

library(datasets);

pdf(file="agglom.pdf")

# First no pre-process.
data = state.x77
distance = dist(as.matrix(data))
hc = hclust(distance)
plot(hc, main="No pre-process")

# Now pre-process.
data = na.omit(state.x77)
data = scale(data)
distance = dist(as.matrix(data))
hc = hclust(distance)
plot(hc, main="Pre-process")

# Now remove area.
data = data[,-8]
distance = dist(as.matrix(data))
hc = hclust(distance)
plot(hc, main="No Area")

# Now remove area.
data = data[,-8]
distance = dist(as.matrix(data))
hc = hclust(distance)
plot(hc, main="No Area")

# Now only frost.
data = data[,7]
distance = dist(as.matrix(data))
hc = hclust(distance)
plot(hc, main="Only Frost")

dev.off()
