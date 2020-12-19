/*
- Song (name, artist_name, album, song_date)
- Artist (artist_name, agency, debut_year)
- Album (Title, album_date, Likes)
The song records the name of songs, the name of the artist who sing the corresponding song,
 the name of album that song belongs, the date when the song is released. song_date is Date type and Primary key is name.
The Artist records the name of artists, agency of the artist, debut_year of the artist.
 debut_year is Int typ and Primary key is artist_name.
The Album records the title of the album, the date when the album is released, the count of Likes (based on Melon Website).
 album_date is Date type and primary key is Title.
*/
create table Song(
  artist_name varchar(30),
  name varchar(30) not null,
  album varchar(30),
  song_date DATE,
  primary key(name)
);
CREATE INDEX song_artist ON Song(artist_name);
CREATE INDEX song_al ON Song(album);
create table Artist(
  artist_name varchar(30) NOT NULL,
  agency varchar(30) not null,
  debut_year int,
  Primary key (artist_name),
  Foreign key (artist_name) REFERENCES Song(artist_name)ON UPDATE CASCADE ON DELETE CASCADE
);

create table Album(
  album varchar(30) not null,
  album_date DATE,
  Likes int not null,
  Primary key (album),
  Foreign key (album) references Song(album)  ON UPDATE CASCADE ON DELETE CASCADE
);
/*View song_album that song and album natural joins and insert data
*/
CREATE VIEW song_album(name, artist_name, album, Likes) AS select name, Song.artist_name, album, Likes from (Song natural join Album), artist where Song.artist_name = Artist.artist_name;

insert into Song(artist_name, name, album, song_date) values('Taylor Swift', '22', 'Red', '2013-05-12');
  insert into Song(artist_name, name, album, song_date) values('Taylor Swift', 'ME!', 'Lover','2019-04-23');
    insert into Song(artist_name, name, album, song_date) values('Taylor Swift', 'Lover', 'Lover','2019-08-23');
insert into Song(artist_name, name, album, song_date) values('Charlie Puth', 'One Call Away', 'Nine Track Mind', '2016-11-11');
  insert into Song(artist_name, name, album, song_date) values('Charlie Puth', 'See You Again', 'Fast and Furios', '2015-03-17');
    insert into Song(artist_name, name, album, song_date) values('Charlie Puth', 'Attention', 'Voicenotes','2018-05-11');
insert into Song(artist_name, name, album, song_date) values('Taeyeon', 'Happy', 'Happy', '2020-05-04');
insert into Song(artist_name, name, album, song_date) values('Baekhyun', 'Candy', 'Delight','2020-05-24');
  insert into Song(artist_name, name, album, song_date) values('Baekhyun', 'Bungee', 'Delight','2020-05-25');
    insert into Song(artist_name, name, album, song_date) values('Baekhyun', 'Love Again', 'Delight', '2020-05-25');
  insert into Song(artist_name, name, album, song_date) values('Taeyeon', 'Dear Me', 'Purpose','2020-01-15');
    insert into Song(artist_name, name, album, song_date) values('Taeyeon', 'Starlight', 'Why','2016-06-25');
insert into Song(artist_name, name, album, song_date) values('Taeyeon', 'Why', 'Why', '2016-06-28');
  insert into Song(artist_name, name, album, song_date) values('Taeyeon', 'Spark', 'Purpose','2020-01-15');
  insert into Song(artist_name, name, album, song_date) values('Taeyeon', 'Something New', 'Something New', '2018-06-18');
  insert into Song(artist_name, name, album, song_date) values('Taeyeon', 'Cover Up', 'My Voice','2017-04-03');

  insert into Album(album,  Likes, album_date ) values ('Red', 35988, '2013-05-14');
  insert into Album(album,  Likes, album_date ) values ('Lover', 20619, '2019-08-23');
insert into Album(album,  Likes, album_date ) values ('Nine Track Mind', 183417, '2016-11-11');
insert into Album(album,  Likes, album_date ) values ('Fast and Furios', 199607, '2015-03-17');
insert into Album(album,  Likes, album_date ) values ('Voicenotes', 153940, '2018-05-11');
insert into Album(album,  Likes, album_date ) values ( 'Happy', 17731, '2020-05-04');
insert into Album(album,  Likes, album_date ) values ('Delight', 94052, '2020-05-25');
insert into Album(album,  Likes, album_date ) values ('Why', 73884, '2016-06-28');
insert into Album(album,  Likes, album_date ) values ('Purpose', 92620, '2020-01-15');
insert into Album(album,  Likes, album_date ) values ('Something New', 37433, '2018-06-18');

  insert into Artist(artist_name, agency, debut_year) values ('Taylor Swift', 'Republic Records', 2006);
  insert into Artist(artist_name, agency, debut_year) values ('Charlie Puth', 'Atlantic Records', 2009);
  insert into Artist(artist_name, agency, debut_year) values ('Taeyeon', 'SM', 2007);
  insert into Artist(artist_name, agency, debut_year) values ('Baekhyun', 'SM', 2014);
