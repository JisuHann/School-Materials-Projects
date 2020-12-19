/*
총 73개
major_attr
    gu      구 이름 foreign key
    name    명소 이름 primary key
    season     명소의 테마-계절
    accompany     명소의 테마-동반
    review	      명소의 review
*/
create table major_attr (
  gu varchar(30),
  name varchar(50) not null,
  season varchar(30),
  accompany varchar(30),
  review float,
  primary key(name),
  foreign key(gu) references visitor_gu (gu)
);

insert into major_attr values('Jongno','Korean History Museum','Winter Fall','Family Kids','4.4');
insert into major_attr values('Jongno','Gwanghwamun Square','Winter Fall','Family Friends','4.4');
insert into major_attr values('Jongno','Naksan Park','Spring Fall Winter','Friends Lover','4.5');
insert into major_attr values('Jongno','Ewha Mural Village','Winter Fall Summer','Friends Lover','4.1');
insert into major_attr values('Jongno','Gwangjang Market','Winter','Family Friends','4.1');
insert into major_attr values('Jongno','Bukchon Hanok Village','Fall Summer','Family Friends','4.3');
insert into major_attr values('Jongno','Tapgol Park','Summer Winter','Kids Family','3.7');
insert into major_attr values('Jongno','Cheonggyecheon','Summer Spring','Friends Lover','4.2');
insert into major_attr values('Jongno','Dongdaemun Castle Park','Fall Winter','Friends','4.3');
insert into major_attr values('Jongno','Jogyesa Temple','Summer Fall','Family','4.4');

insert into major_attr values('Jongno','National Folk Museum','Winter Summer','Kids','4.5');
insert into major_attr values('Jongno','Insadong','Winter Fall','Lover Friends','4.5');
insert into major_attr values('Jongno','National Museum of Modern and Contemporary Art','Summer Winter','Friends','4.5');
insert into major_attr values('Jongno','Samcheongdong-gil','Fall Winter','Friends','4.2');
insert into major_attr values('Jongno','Gwanghwamun','Spring Summer','Friends Family','4.5');
insert into major_attr values('Jongno','National Palace Museum','Spring Summer','Family Kids','4.5');
insert into major_attr values('Jongno','Statue of King Sejong','Fall Summer Spring Winter','Family Friends Kids','4.6');
insert into major_attr values('Jongno','The museum is alive Insadong','Fall Spring Winter','Friends','4.2');
insert into major_attr values('Jongno','Statue of Chungmugong Yi Sun-sin','Summer Spring Winter Fall','Family Friends Kids','4.6');
insert into major_attr values('Jongno','Ikseon-dong Hanok Street','Fall Winter Spring','Lover Friends','4.1');

insert into major_attr values('Jongno','Seoul Daehak-ro','Winter Fall','Friends','4.2');
insert into major_attr values('Jung','Dongdaemun Market','Summer Fall Winter','Friends Family','4.1');
insert into major_attr values('Jung','Seoul Animation Center','Winter Fall Summer Spring','Kids','4.1');
insert into major_attr values('Jung','Myeongdong Nanta Theater','Summer Fall','Family Friends Kids','4.5');
insert into major_attr values('Jung','Grevin Museum','Winter Fall Spring Summer','Family Friends','4.2');
insert into major_attr values('Jung','Myeongdong Cathedral','Fall Winter','Friends','4.6');
insert into major_attr values('Jung','Namsan Park','Summer Spring Fall','Lover Friends Family','4.6');
insert into major_attr values('Jung','Myeongdong shopping street','Winter Fall Spring','Family Friends','4.3');
insert into major_attr values('Jung','N Seoul Tower','Winter Fall Spring','Friends Lover','4.4');
insert into major_attr values('Jung','Dongdaemun Design Plaza','Summer Fall','Family Friends','4.3');

insert into major_attr values('Jung','Dongdaemun History and Culture Park','Spring Summer Fall Winter','Family Friends','4.0');
insert into major_attr values('Jung','Seoul City Hall','Summer Spring Fall Winter','Kids Friends Family','4.2');
insert into major_attr values('Jung','Namdaemun Market','Winter Fall','Friends','4.2');
insert into major_attr values('Jung','Seoullo 7017','Fall Spring Summer','Friends Family Lover','4.1');
insert into major_attr values('Jung','Sungnyemun','Winter Fall Spring Summer','Family Kids Friends','4.4');
insert into major_attr values('Mapo','Hongdae street','Fall Winter','Friends','4.3');
insert into major_attr values('Mapo','Korean Film Museum','Winter Fall Spring','Friend Family','4.2');
insert into major_attr values('Mapo','Hongdae Art Market Free Market','Summer Winter','Friends','4.0');
insert into major_attr values('Mapo','World Cup Sunset Park','Fall Spring Summer','Family Kids Friends Lover','4.4');
insert into major_attr values('Mapo','World Cup Sky Park','Fall Spring Summer','Family Kids Friends Lover','4.5');

insert into major_attr values('Mapo','World Cup Peace Park','Fall Spring Summer','Family Kids Friends Lover','4.5');
insert into major_attr values('Mapo','Gyeonguiseon Forest Road','Fall Spring Summer','Friends Lover','4.4');
insert into major_attr values('Yeongdeungpo','KBS','Fall Spring Summer','Kids','4.2');
insert into major_attr values('Yeongdeungpo','Seonyudo Park','Fall Spring Summer','Family Kids','4.5');
insert into major_attr values('Yeongdeungpo','Yeouido Han River Park','Fall Spring Summer','Lover Friends','4.5');
insert into major_attr values('Yeongdeungpo','63 Sea World','Fall Spring Summer','Friends Lover Kids','4.2');
insert into major_attr values('Yeongdeungpo','Seoul Marina Club & Yacht','Summer','Family Friends','4.0');
insert into major_attr values('Seocho','Yangjae-dong Flower Shop','Spring Summer','Friends Lover','4.9');
insert into major_attr values('Seocho','Sebitseom','Spring Summer Fall ','Friends Lover','4.2');
insert into major_attr values('Seocho','Seorae Island','Spring Fall','Lover Family','5.0');

insert into major_attr values('Seocho','Yangjae Civic Forest','Fall Spring Summer','Kids Family','4.4');
insert into major_attr values('Seocho','Goto Mall','Summer Winter','Kids Family Friends','4.1');
insert into major_attr values('Seocho','Montmartre Park','Spring Fall','Family','4.4');
insert into major_attr values('Gangnam','Starfield COEX Mall','Summer Winter','Family Friends','4.2');
insert into major_attr values('Gangnam','COEX Aquarium','Fall Spring Summer Winter','Friends Family Lover Kids','4.3');
insert into major_attr values('Gangnam','Dosan Park','Fall Spring Summer','Family Friends','4.4');
insert into major_attr values('Gangnam','Maebongsan','Fall Spring Summer','Lover Friends','4.5');
insert into major_attr values('Gangnam','Dogok Neighborhood Park','Fall Spring Summer','Friends','4.0');
insert into major_attr values('Songpa','Seokchon Lake','Spring Summer','Lover Friends Family','4.5');
insert into major_attr values('Songpa','Olympic Park','Fall Spring Summer','Friends Lover Family','4.6');

insert into major_attr values('Songpa','Songpanaru Park','Fall Spring Summer','Lover Friends','4.5');
insert into major_attr values('Yongsan','Leeum, Samsung Museum of Art','Spring Summer Fall Winter','Friends Lover','4.5');
insert into major_attr values('Yongsan','Korean War Memorial','Spring Summer Fall','Kids Family','4.6');
insert into major_attr values('Yongsan','Yongsan Family Park','Fall','Family','4.5');
insert into major_attr values('Seongbuk','Korean Furniture Museum','Spring Summer Fall Winter','Friends Lover','4.6');
insert into major_attr values('Seongbuk','Bukhansan National Park','Fall Spring Summer','Family Friends','4.6');
insert into major_attr values('Dongjak','Noryangjin Seafood Wholesale Market','Fall Spring Summer Winter','Friends Family','3.8');
insert into major_attr values('Dongjak','Borame Park','Fall Spring Summer','Friends Lover Family','4.4');
insert into major_attr values('Gwangjin','Ttukseom Amusement Park','Fall Spring Summer','Family Kids','4.4');
insert into major_attr values('Gwangjin','Ttukseom Han River Park Swimming Pool','Summer','Kids','4.3');

insert into major_attr values('Gwanak','Gwanaksan Valley','Fall Spring Summer','Friends Family Kids','4.5');
insert into major_attr values('Gangseo','Seoul Botanical Garden','Fall Winter','Kids','4.2');
insert into major_attr values('Seongdong','Seoul Forest','Fall Spring Summer','Family Lover','4.6');
