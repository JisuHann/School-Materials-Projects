/*
총 59개

hallyu
    gu      구 이름 foreign key
    name    장소 이름 primary key
    grp     분류(kpop, kbeauty, kdrama, ktvshow)
    who     특징
    insta   google map 평 개수  foreign key
    score   google map 평

https://english.visitseoul.net/hallyu 
*/
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