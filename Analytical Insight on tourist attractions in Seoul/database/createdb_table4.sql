/*
현재 52개

food
    gu  구이름
    name 식당이름
    grp 분류(korean, cafe, bars)
    review 인스타그램 게시물 수(인기 정도): 200개 이상이면 200
    score 별점 수 (음식 퀄리티)

https://www.tripadvisor.com/Restaurants-g294197-Seoul.html
https://english.visitseoul.net/restaurants
*/
create table food(
  gu varchar(30),
  name varchar(50) not null,
  grp varchar(30),
  insta int,
  food float,
  service float,
  value float,
  primary key(name),
  foreign key (gu) REFERENCES visitor_gu(gu)
);

insert into food values('Jung','La Yeon', 'korean', 82, 4, 4.5, 3.5);
insert into food values('Jung','Jinju Hoegwan', 'korean', 73, 4.5, 3.5, 3.5);
insert into food values('Jung','Mugyodong Bugeokukjib', 'korean', 675, 4.5, 4, 4.5);
insert into food values('Jung','Yeji Sikdang', 'korean', 126, 4.5, 4.5, 4.5);

insert into food values('Jongno','Jamaejip', 'korean',299, 4.5, 4, 4.5);
insert into food values('Jongno','Jin Ok Hwa Original Chicken Restaurant', 'korean', 597, 4.5, 4, 4.5);
insert into food values('Jongno','Myeongdong Dakhanmari Main', 'korean', 193, 4.5, 4, 4.5);
insert into food values('Jongno','Balwoo Gongyang', 'korean', 148, 4.5, 4,4);
insert into food values('Jongno','Dining in SPACE', 'korean', 23, 5,5,4);
insert into food values('Jongno','Doore', 'korean', 17, 3.5, 3.5, 3);
insert into food values('Jongno','Songane Dakhanmari', 'korean', 41, 5, 4.5, 5);
insert into food values('Jongno', 'Jihwaja Seoul', 'korean', 161, 5,5,4.5);
insert into food values('Jongno','Sunine Bindaetteok', 'korean', 147, 4, 3.5, 4);
insert into food values('Jongno','Suga', 'korean', 43, 4.5, 4.5, 4.5);

insert into food values('Mapo','Jinmi Sikdang', 'korean', 208, 4.5, 3.5, 4);
insert into food values('Mapo','Yeonnamseo Sikdang', 'korean', 274, 4.5, 3.5, 4);
insert into food values('Mapo','Hongdae Dakgalbi', 'korean', 129, 4.5, 4.5, 4.5);
insert into food values('Mapo','choigozip Hongdae', 'korean', 171, 4.5, 4.5, 4);

insert into food values('Seocho','Flavors', 'korean', 136, 4.5, 4.5, 4);
insert into food values('Seocho','Pro Ganjang Gejang Sinsa', 'korean', 290, 4, 3.5, 3);
insert into food values('Seocho','Kyungbokkung Sadang','korean', 52, 4.5, 4.5, 3.5);
insert into food values('Seocho', 'Maji', 'korean', 7, 5,5,4);

insert into food values('Gangnam', 'Jungsik', 'korean', 468, 4.5, 4.5, 4);
insert into food values('Gangnam','Wonjo Ssambabjib Nonhyeon Main','korean', 110, 4, 3.5, 4.5);
insert into food values('Gangnam','Yeontabal Gangnam Station', 'korean',36, 5, 4.5, 3.5);

insert into food values('Yongsan','Bada Sikdang', 'korean', 53, 4, 3, 3.5);
insert into food values('Yongsan','EID - Halal Korean Food', 'korean', 139, 4.5, 4.5, 4.5);
insert into food values('Yongsan','Parc', 'korean', 82, 4.5, 4.5, 4);
insert into food values('Yongsan','Dooreyoo', 'korean', 13, 4.5, 4.5, 4);

insert into food values('Seodaemun', 'Byeokje Galbi', 'korean', 67, 4.5, 4.5, 4);
insert into food values('Jung', 'La Seine', 'korean', 243, 4.5, 4.5, 3.5);
insert into food values('Jung', 'Migabon', 'korean', 652, 4.5, 4.5, 3.5);
insert into food values('Jung', 'Aria', 'korean', 142, 4.5, 4.5, 3.5);
insert into food values('Jung','Congee House Meyeongdong', 'korean', 219, 4.5, 4.5, 4);

insert into food values('Jung','Andong Jjimdak', 'korean', 148, 4.5, 4, 4);
insert into food values('Seocho','Seocho Sariwon', 'korean', 23, 4.5, 4.5, 3.5);
insert into food values('Seocho','Bongpiyang Seocho', 'korean', 41, 4.5, 4.5, 3.5);
insert into food values('Seocho','Cham Seollongtang-Seocho', 'korean', 9, 4, 4, 4);
insert into food values('Seocho','Philkyungjae', 'korean', 70, 4.5, 4, 3.5);
insert into food values('Seocho','Pulipchae Sadang', 'korean', 17, 4, 4, 4);
insert into food values('Seocho','Yellow Cafe Seocho', 'cafe', 23, 4, 3.5, 3.5);

insert into food values('Gangnam','Jangseng Geongangwon', 'bar', 74, 5, 5, 5);
insert into food values('Gangnam','Yang Good', 'korean', 138, 5, 4.5, 4.5);
insert into food values('Gangnam','Mingles', 'korean', 175, 4.5 ,4.5, 4.5);
insert into food values('Gangnam','Grand Kitchen', 'korean', 169, 4.5, 3.5, 4);
insert into food values('Gangnam','Chaegeundaam', 'korean', 42, 4.5, 4.5, 4.5);
insert into food values('Gangnam','School Food Garosu-gil', 'korean', 114, 4, 3.5, 3.5);
insert into food values('Gangnam','Kwonsooksoo', 'korean', 49, 5, 5, 4.5);

insert into food values('Mapo','Mapo Mandu', 'korean', 70, 4, 3.5, 4.5);
insert into food values('Mapo','Mapo Jinjja Wonjo Choidaepo', 'korean', 105, 4.5, 3.5, 4);
insert into food values('Mapo','Mapo Yangji Seolleongtang', 'korean', 57, 4, 3.5, 4);
insert into food values('Mapo','Mapo Galmegi', 'korean', 42, 4, 3.5, 3.5);
