<?php
$serverName = "localhost";
$dbUsername = "team01";
$dbPassword = "team01";
$dbName = "team01";

$conn = mysqli_connect($serverName, $dbUsername, $dbPassword, $dbName);

if(!$conn){
    die("Connection Failed: ".mysqli_connect_error());
}

function loginsert($conn, $usersid, $usersuid, $sql){
    $sql = "INSERT INTO log(usersId,usersUid,  ontime, command) VALUES (".$usersid.",'".$usersuid."', now(),\"".$sql."\")";
    $login_res = mysqli_query($conn, $sql);
}
