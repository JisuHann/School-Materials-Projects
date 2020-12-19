create database team01;
use team01;

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

create table hallyu(
  gu varchar(30),
  name varchar(50) not null,
  grp varchar(30),
  who varchar(30),
  insta int,
  value float,
  primary key(name),
  foreign key (gu) REFERENCES visitor_gu(gu)
);

insert into hallyu values('Jongno','The Piano','kpop','Kang Daniel', 386, 4.0);
insert into hallyu values('Yongsan','Mabong Lamb Skewers Yongsan Branch','kpop','Kang Daniel', 93, 4.0);
insert into hallyu values('Gangnam','Picky Papa Daniel Forest','kpop','Kang Daniel', 131, 4.2);
insert into hallyu values('Jongno','Hotel Seiine','kdrama','Hotel del Luna', 216, 3.9);
insert into hallyu values('Jung','Hyemindang & Coffee Hanyakbang','kdrama','Hotel del Luna', 319, 4.2);
insert into hallyu values('Jongno','Changhwadang','kdrama','Hotel del Luna', 633, 3.8);
insert into hallyu values('Songpa','Seoul Book Bogo','kdrama','Hotel del Luna', 1096, 4.2);
insert into hallyu values('Seocho','Roller City','ktvshow','I Live Alone', 43, 4.1);
insert into hallyu values('Gangnam','Eum Lobatayakki','ktvshow','I Live Alone', 92, 4.4);
insert into hallyu values('Gangnam','Cartoon Shop V','ktvshow','I Live Alone', 51, 4.2);
insert into hallyu values('Gangnam','Hirai Chinese Glass, Seolleung branch','ktvshow','I Live Alone',127, 3.7);
insert into hallyu values('Gangnam','Coex Artium','kpop','NCT127', 131, 4.3);
insert into hallyu values('Gangnam','Café de Paris','kpop','NCT127', 118, 4.2);
insert into hallyu values('Mapo','Goyonam Hongdae','kpop','NCT127', 8, 4.3);
insert into hallyu values('Seongdong','Oneul Seongsu Malgeum','kpop','EXO', 22, 4.1);
insert into hallyu values('Gangnam','Insadong Chon','kpop','EXO', 150, 3.6);
insert into hallyu values('Dongdaemun','Sharo Stone','kpop','EXO', 37, 3.9);
insert into hallyu values('Songpa','Go-Kart','kpop','BTS V', 36, 4.1);
insert into hallyu values('Jongno','Cheonggyecheon Stream','kpop','BTS Suga', 2691, 4.2);
insert into hallyu values('Jung','Seoullo 7017','kpop','BTS Suga', 5685, 4.1);
insert into hallyu values('Seocho','Sebitseom Island','kpop','BTS Suga', 129, 4.2);
insert into hallyu values('Dongdaemun','Seoul Folk Flea Market','kpop','BTS Jimin', 3028, 3.9);
insert into hallyu values('Yongsan','Grilled Pork Belly','kpop','BTS Jimin', 227, 4.1);
insert into hallyu values('Dongjak','Noryangjin Fish Market','kpop','BTS Jin', 20162, 3.8);
insert into hallyu values('Seongdong','Eungbongsan Pagoda','kpop','GOT7', 14, 4.1);
insert into hallyu values('Gwangjin','Weareoui','kpop','Seventeen', 20, 3.9);
insert into hallyu values('Mapo','Maison Kitty Bunny Pony Seoul','kpop','BlackPink', 91, 4.3);
insert into hallyu values('Seodaemun','Mad Coffee','kpop','BlackPink', 118, 4.5); 
insert into hallyu values('Seodaemun','Shinchon iZone Pop','kpop','BTS', 70, 4.1);
insert into hallyu values('Yongsan','Cafe & Gather','kpop','BTS', 26, 4.3);
insert into hallyu values('Gwangjin','Achasan','kpop','BTS', 236, 4.3);
insert into hallyu values('Yongsan','PP Seoul','kdrama','Song Hye-kyo', 60, 4.5);

insert into hallyu values('Jongno','Gyeonghuigung Palace','kdrama','Kingdom', 830, 4.3);
insert into hallyu values('Jongno','Jongmyo Shrine','kdrama','Kingdom', 418, 4.5);
insert into hallyu values('Jongno','Changdeokgung Palace','kdrama','Kingdom', 9605, 4.6);
insert into hallyu values('Jongno','Changgyeonggung Palace','kdrama','Kingdom', 2322,4.6);

insert into hallyu values('Mapo','VR Square Hongdae Branch','kpop','BTS', 113, 4.1);
insert into hallyu values('Seongdong','Seoul Forest','kpop','BTS RM', 5826, 4.6);
insert into hallyu values('Gangnam','Dosan Jokbal','kpop','BTS v', 44, 4.2);
insert into hallyu values('Gangnam','Beat Phobia Sinnonhyeon Branch','kpop','BTS Jin Jimin', 131, 4.3);

insert into hallyu values('Songpa','Lotte World Tower - Seoul Sky','kpop','BTS Jungkook', 1150, 4.5);
insert into hallyu values('Jung','Namsan Cable Car','kpop','BTS Jungkook', 7522, 4.2);
insert into hallyu values('Jung','Deoksugung Stonewall Walkway','kpop','BTS Jungkook', 52, 4.7);
insert into hallyu values('Jongno','Naksan Park','kpop','BTS Jungkook', 3609, 4.5);
insert into hallyu values('Seocho','Banpo Hangang Park - Moonlight Rainbow Fountain','kpop','BTS Jungkook', 1944, 4.5);

insert into hallyu values('Seodaemun','Seodaemun Independence Park','kdrama','One Spring Night', 401, 4.5);
insert into hallyu values('Dobong','Ssangmundong Coffee','kdrama','One Spring Night', 10, 4.5);
insert into hallyu values('Dobong','Himchan Pharmacy','kdrama','One Spring Night', 6, 3.7);

insert into hallyu values('Yongsan','Maratuzi','kpop','MONSTA X Wonho Shownu', 47, 3.9);
insert into hallyu values('Gangnam','Jokhwang Sangje, Apgujeongrodeo branch','kpop','MONSTA X', 16, 4.6);

insert into hallyu values('Jung','Bowling Bowling','kpop','IZ*ONE', 134, 4.3);
insert into hallyu values('Nowon','Parasol Bunsik','kpop','IZ*ONE', 28, 3.5);

insert into hallyu values('Songpa','Jamsil Kart Track','kextreme','car race attraction', 2, 4.5);
insert into hallyu values('Gangnam','Leco_de','kbeauty','Leferi', 60, 3.9);
insert into hallyu values('Gangnam','House of AROMATICA','kbeauty','clean, vegan beauty brand', 39, 4.1);

insert into hallyu values('Jung','Baekbeom Plaza, Namsan Park','kdrama','Itaewon Class', 1, 4.0);
insert into hallyu values('Yongsan','Noksapyeong Overpass','kdrama','Itaewon Class', 32, 3.6);
insert into hallyu values('Yongsan','Ichon Hangang Park','kdrama','Itaewon Class', 566, 4.3);
insert into hallyu values('Yongsan','G Guesthouse','kdrama','Itaewon Class', 79, 4.2);
CREATE TABLE users(
    usersId int(11) PRIMARY KEY AUTO_INCREMENT NOT NULL,
    usersName varchar(128) NOT NULL,
    usersUid varchar(128) NOT NULL,
    usersPwd varchar(128) NOT NULL
);

INSERT INTO users (usersName, usersUid, usersPwd) VALUES ("admin", "admin", "admin");
INSERT INTO users (usersName, usersUid, usersPwd) VALUES ("user1", "user1", "user1");

CREATE TABLE log(
    usersId int(11),
    usersUid varchar(128) NOT NULL,
    ontime timestamp NOT NULL,
    command varchar(500) NOT NULL,
    PRIMARY KEY(usersUid, ontime),
    foreign key (usersId) REFERENCES users (usersId)
);

INSERT INTO log(usersId,usersUid,  ontime, command) VALUES (2, "user1", now(), "insert into hallyu values('Songpa','Go-Kart','kpop','BTS V', 36, 4.1)");
INSERT INTO log(usersId,usersUid,  ontime, command) VALUES (2, "user1", now() - interval 2 day, "update food set insta = 324 where name = 'La Seina'");
INSERT INTO log(usersId,usersUid,  ontime, command) VALUES (2, "user1", now() - interval 3 day, "insert into food values('Gangnam','Kwonsooksoo', 'korean', 49, 5, 5, 4.5)");
INSERT INTO log(usersId,usersUid,  ontime, command) VALUES (2, "user1", now() - interval 4 day, "delete from hallyu where name = 'Deoksugung'");
INSERT INTO log(usersId,usersUid,  ontime, command) VALUES (1, "admin", now() - interval 1 day, "insert into hallyu values('Songpa','Go-Kart','kpop','BTS V', 36, 4.1)");
INSERT INTO log(usersId,usersUid,  ontime, command) VALUES (1, "admin", now(), "update food set insta = 324 where name = 'La Seina'");