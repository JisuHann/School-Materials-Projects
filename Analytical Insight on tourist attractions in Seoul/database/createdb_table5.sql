/*
총 7개
hiking_trail
    gu      구 이름 foreign key
    mountain    산이름
    entrance 입구이름 primary key
    distance 거리,
    time     왕복 등산 시간
    difficulty     난이도
 
*/
create table hiking_trail(
  gu varchar(30),
  mountain varchar(30),
  entrance varchar(50) not null,
  distance float,
  time float,
  difficulty varchar(30),
  primary key(entrance),
  foreign key(gu) references visitor_gu (gu)
);

insert into hiking_trail values('Gwanak','Gwanaksan','Seoul National University Main Gate','7.4','4.5','Hard');
insert into hiking_trail values('Jongno','Inwangsan','Sajik Park','4.1','3.0','Easy');
insert into hiking_trail values('Eunpyeong','Bukhansan','Entrance to Bukhansanseong','11.7','6.0','Normal');
insert into hiking_trail values('Seocho','Cheonggye Mountain','Cheonggye Mountain Station','3','1.5','Peaceful');
insert into hiking_trail values('Seongdong','Eungbongsan','Eungbong Station','1.2','0.5','Peaceful');
insert into hiking_trail values('Seodaemun','Ansan','Dongnimmun station','7','1.5','Easy');
insert into hiking_trail values('Jongno','Baekak','Jahamungogae','4.7','3','Normal');
