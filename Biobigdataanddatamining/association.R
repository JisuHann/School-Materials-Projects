rm(list = ls())

library(arules)
library(arulesViz)

load("C:/Temp/titanic.raw.rdata")
summary(titanic.raw)

titanic <- titanic.raw

class(titanic)
dim(titanic)

options(digits=4)  #유효숫자 3자리

#모든 규칙 생성
rules.all <- apriori(titanic)

#규칙 확인
inspect(rules.all)


#Finding rules with rhs indicating survival only and lower support
#규칙의 우변(rhs)이 생존여부(survided)와 관계된 규칙
#설정값 변경: 최소부분집합크기 =2, 최소지지도 =0.005, 최소신뢰도=0.8
# rules with rhs containing "Survived" only

rules <- apriori(titanic, parameter = list(minlen=2, supp=0.005, conf=0.8),
                appearance = list(rhs=c("Survived=No", "Survived=Yes"), default="lhs"),
                control = list(verbose=F))

#규칙 확인
inspect(rules)

#향상도(lift) 기준으로 정렬
rules.sorted <- sort(rules, by="lift")

#규칙 확인
inspect(rules.sorted)

#규칙1은 2등석의 모든 어린이가 생존했다는 것을 의미
#규칙2는 규칙1에 비해 더 이상의 추가 정보를 제공하지 않는다
#이러한 규칙은 일종의 불필요한 중복이므로, 중복규칙을 찾아 제거해야한다.
#When a rule (#2) is a super rule of another rule (#1)
#and the former has the same or a lower lift, 
#the former rule (#2) is considered to be redundant.


# Finding redundant rules
#중복되는 규칙 찾기
inspect(rules.sorted[is.redundant(rules.sorted)])


#Pruning redundant rules
#중복되는 규칙 제거 
rules.pruned <- rules.sorted[!is.redundant(rules.sorted)]

#규칙 확인
inspect(rules.pruned)


#Interpreting rules
inspect(rules.pruned[1]) 

#이 규칙은 class2nd의 모든 아이가 살아남았다고 명시하지만
#다른 클래스와의 생존율을 비교하기 위한 정보는 전혀 제공하지 않는다.
#따라서, parameters  수정

rules2 <- apriori(titanic, control = list(verbose=F),
                 parameter = list(minlen=3, supp=0.002, conf=0.2),
                 appearance = list(default="none", rhs=c("Survived=Yes"),
                                   lhs=c("Class=1st", "Class=2nd", "Class=3rd",
                                         "Age=Child", "Age=Adult")))

rules.sorted2 <- sort(rules2, by="confidence")
inspect(rules.sorted2)

#===================================================================
# visualization
#연관규칙 시각화

#Scatter plot
plot(rules.all)


#Balloon plot
plot(rules.pruned, method="grouped")


#Graph-based visualizations
plot(rules.pruned, method="graph")
plot(rules.pruned, method="graph", control=list(type="items"))


#Parallel coordinates plot (평행좌표그림)
plot(rules.pruned, method="paracoord", control=list(reorder=TRUE))


#matrix-based visualization
plot(rules.pruned, method="matrix", measure="lift") 
plot(rules.pruned, method="matrix", engine="3d", measure="lift")  
