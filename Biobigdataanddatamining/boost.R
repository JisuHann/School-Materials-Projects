rm(list = ls())

library(adabag)
data(iris)
boo.adabag <- boosting(Species~., data=iris, boos=TRUE, mfinal=10)
boo.adabag$importance

#{adabag}의 boosting() 함수는 부스팅을 이용하여 분류를 수행
#plot() 함수를 통해 분류 결과를 트리 형태로 출력

plot(boo.adabag$trees[[10]])
text(boo.adabag$trees[[10]])


#predict() 함수를 통해 새로운 자료에 대한 분류(예측)를 수행

pred <- predict(boo.adabag, newdata=iris)
tb <- table(pred$class, iris[,5])
tb
#setosa, versicolor, virginica 모두 정확히 분류


#오분류율 계산
error.rpart <- 1-(sum(diag(tb))/sum(tb))
error.rpart 
