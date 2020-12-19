<?php

if(isset($_POST["submit2"])){
    $name = $_POST["name"];
    $username = $_POST["uid"];
    $pwd = $_POST["pwd"];
    $pwdRepeat = $_POST["pwdrepeat"];

    require_once './dbhc.inc.php';
    require_once './functions.inc.php';

    if(invalidUid($name) !== false){
        echo "<script>alert('Choose a proper user id');</script>";
        lheader("location: ../home.php");
        exit();        
    }
    if(pwdMatch($pwd, $pwdRepeat) !== false){
        echo "<script>alert('Passwords doesn't match!');</script>";
        header("location: ../home.php");
        exit();

    }
    
    if(uidExists($conn, $username) !== false){
        echo "<script>alert('User id already exist');</script>";
        header("location: ../home.php");
        exit();

    }
    createUser($conn, $name, $username, $pwd);
}else{
    echo "<script>alert('Something get wrong! Try again');</script>";
    header("location: ../home.php");
    exit();
}