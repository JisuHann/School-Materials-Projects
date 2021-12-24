rm(list = ls())

library(adabag)
data(iris)

iris.bagging <- bagging(Species~., data=iris, mfinal=10)
# mfinal= 반복수  또는  트리의  수(디폴트=100)

iris.bagging$importance	# 변수의  상대적인  중요도

#변수의  중요도는  각  트리에서  변수에  의해  주어지는  
#지니지수의  gain(또는 불확실성의  감소량)을  고려한  척도


#R 패키지 {adabag}의 bagging() 함수는 배깅을 이용하여 분류를 수행
#plot() 함수를 통해 분류 결과를 트리 형태로 출력

plot(iris.bagging$trees[[10]])
text(iris.bagging$trees[[10]])

#predict() 함수를 통해 새로운 자료에 대한 분류(예측)를 수행
#모형 구축에 사용된 자료를 재사용하여 분류를 수행
 
pred <- predict(iris.bagging, newdata=iris)
table(pred$class, iris[,5])
 


