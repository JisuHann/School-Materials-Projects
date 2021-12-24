rm(list = ls())

library(randomForest)
library(rpart) 

data(stagec)	 
str(stagec)

stagec1<- subset(stagec, !is.na(g2))
stagec2<- subset(stagec1, !is.na(gleason))
stagec3<- subset(stagec2, !is.na(eet))
str(stagec3)

set.seed(14)

#1. Dataset Preperation
aba <- read.csv("/Users/jisu/Desktop/breast-cancer-wisconsin.data")
data <- aba[, 2:11]
data$X1.3 <- as.numeric(data$X1.3)
data

colnames(data)<- c("a", "b", "c", "d","e", "f","g", "h","i", "class")
str(data)

data<- subset(data, f!="?")
data<- subset(data, !is.na(f))
str(data)

#2. Split training set and test set
ind <- sample(2, nrow(data), replace=TRUE, prob=c(0.7, 0.3))

trainData <- data[ind==1,]
testData <- data[ind==2,]
trainData

#3. create Random Forest 
rf <- randomForest(class ~ b+c+d+f+g+h+i, data=trainData, ntree=100, proximity=TRUE)

#4. Predict on test data
#5. Get Error and Accuracy
rf.pred <- predict(rf, newdata=testData)
tb <- table(rf.pred, testData$class)

error.rpart <- 1-(sum(diag(tb))/sum(tb))
error.rpart 
sum(rf.pred==testData$class)/length(rf.pred)*100