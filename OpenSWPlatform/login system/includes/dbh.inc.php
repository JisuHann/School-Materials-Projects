<?php
$serverName = "localhost";
$dbUsername = "root";
$dbPassword = "root";
$dbName = "team01";

$conn = mysqli_connect($serverName, $dbUsername, $dbPassword, $dbName);

if(!$conn){
    die("Connection Failed: ".mysqli_connect_error());
}

