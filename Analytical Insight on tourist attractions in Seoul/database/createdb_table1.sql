/*
현재 25개

visitor_gu
    gu 구 이름 foreign key
    hotel 관광호텔 등록 현황
    tourism  관광사업체 등록 현황 (여행업)

http://data.seoul.go.kr/dataList/10202/S/2/datasetView.do
http://data.seoul.go.kr/dataList/408/S/2/datasetView.do 
*/
create table visitor_gu(
  gu varchar(30) not null,
  hotel int,
  tourism int,
  primary key(gu)
);

create index gu_index on visitor_gu(gu);
insert into visitor_gu values('Jongno', 44, 351);
insert into visitor_gu values('Jung', 101, 600);
insert into visitor_gu values('Yongsan', 16, 113);
insert into visitor_gu values('Seongdong', 8, 65);
insert into visitor_gu values('Gwangjin', 11, 36);
insert into visitor_gu values('Dongdaemun', 14, 53);
insert into visitor_gu values('Jungnang', 3, 17);

insert into visitor_gu values('Seongbuk', 5, 23);
insert into visitor_gu values('Gangbuk', 5, 12);
insert into visitor_gu values('Dobong', 3, 5);
insert into visitor_gu values('Nowon', 1, 13);
insert into visitor_gu values('Eunpyeong', 12, 37);
insert into visitor_gu values('Seodaemun', 8, 123);

insert into visitor_gu values('Mapo', 24, 546);
insert into visitor_gu values('Yangcheon', 1, 33);
insert into visitor_gu values('Gangseo', 24, 183);
insert into visitor_gu values('Guro', 14, 135);
insert into visitor_gu values('Geumcheon', 9, 113);
insert into visitor_gu values('Yeongdeungpo', 33, 336);
insert into visitor_gu values('Dongjak', 3, 20);

insert into visitor_gu values('Gwanak', 13, 33);
insert into visitor_gu values('Seocho', 14, 192);
insert into visitor_gu values('Gangnam', 70, 302);
insert into visitor_gu values('Songpa', 20, 101);
insert into visitor_gu values('Gangdong', 4, 113);