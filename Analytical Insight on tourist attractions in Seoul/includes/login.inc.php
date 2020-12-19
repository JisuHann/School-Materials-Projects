<?php
if(isset($_POST["submit"])){
    $username = $_POST["uid"];
    $pwd = $_POST["pwd"];
    $url = $_POST["url"];

    require_once 'dbhc.inc.php';
    require_once 'functions.inc.php';

    loginUser($conn, $username, $pwd, $url);
}else{
    echo "<script>alert('Something went wrong, tryw Again!');</script>";
}