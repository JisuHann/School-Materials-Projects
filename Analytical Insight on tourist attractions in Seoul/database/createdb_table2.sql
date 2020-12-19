/*
총 19개
major_tourspot
    gu      구 이름 foreign key
    name    관광지 이름 primary key
    pay     유/무료
    visitor_year	1년간 내외국인 방문자 수
https://www.index.go.kr/potal/main/EachDtlPageDetail.do?idx_cd=2428 
*/
create table major_tourspot(
  gu varchar(30),
  name varchar(50) not null,
  pay varchar(5),
  visitor_year int,
  primary key(name),
  foreign key(gu) references visitor_gu (gu)
);

insert into major_tourspot values('Jongno','Gyeongbokgung','yes','4447571');
insert into major_tourspot values('Jongno','Jongmyo Shrine','yes','415196');
insert into major_tourspot values('Jongno','Changgyeonggung','yes','835972');
insert into major_tourspot values('Jongno','Changdeokgung Palace','yes','1803034');
insert into major_tourspot values('Jung','Deoksugung','yes','1849804');
insert into major_tourspot values('Jung','Namsangol Hanok Village','no','1163995');
insert into major_tourspot values('Jung','Seoul Museum of Art','no','1385209');
insert into major_tourspot values('Yongsan','National Museum of Korea','yes','3476606');
insert into major_tourspot values('Dongdaemun','Seoul Yangnyeongsi Oriental Medicine Museum','yes','80340');
insert into major_tourspot values('Dongdaemun','King Sejong Memorial Hall','yes','6348');
insert into major_tourspot values('Nowon','Joseon Royal Tombs Exhibition Hall','yes','99223');
insert into major_tourspot values('Seodaemun','Seodaemun Natural History Museum','yes','328427');
insert into major_tourspot values('Seodaemun','Seodaemun Prison History Hall','yes','697980');
insert into major_tourspot values('Mapo','Trick Eye Museum','yes','258504');
insert into major_tourspot values('Seocho','Heonneung Inneung','yes','39234');
insert into major_tourspot values('Gangnam','Seolleung Jeongneung','yes','364008');
insert into major_tourspot values('Songpa','Lotte World','yes','5692646');
insert into major_tourspot values('Songpa','Seoul Sky','yes','1482455');
insert into major_tourspot values('Songpa','Aquarium','yes','1290266');

