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