<?php

function invalidUid($username){
    $result;
    if(!preg_match("/^[a-zA-Z0-9]*$/", $username)){
        $result = true;
    }
    else{
        $result = false;
    }
    return $result;
}


function pwdMatch($pwd, $pwdRepeat){
    $result;
    if($pwd !== $pwdRepeat){
        $result = true;
    }
    else{
        $result = false;
    }
    return $result;
}


function uidExists($conn, $username){
    $sql = "SELECT * FROM users WHERE usersUid = ?;";
    $stmt = mysqli_stmt_init($conn);
    if(!mysqli_stmt_prepare($stmt, $sql)){
        echo "<script>alert('Something went wron22g, try again!');</script>";
    }
    mysqli_stmt_bind_param($stmt, "s", $username);
    mysqli_stmt_execute($stmt);

    $resultData = mysqli_stmt_get_result($stmt);

    if($row = mysqli_fetch_assoc($resultData)){
        return $row;
    }else{
        $result = false;
        return $result;
    }
    mysqli_stmt_close($stmt);
}

function createUser($conn, $name, $username, $pwd){
    $sql = "INSERT INTO users (usersName, usersUid, usersPwd) VALUES ( ?, ?, ?);";
    $stmt = mysqli_stmt_init($conn);
    if(!mysqli_stmt_prepare($stmt, $sql)){
        echo "<script>alert('Something wet wrong!');</script>";
    }
    
    mysqli_stmt_bind_param($stmt, "sss", $name, $username, $pwd);
    mysqli_stmt_execute($stmt);
    header('Location: ../home.php');
        exit();
}


function loginUser($conn, $username, $pwd, $url){
    $uid = uidExists($conn, $username);

    if($uid==false){
        echo "<script>alert('No User id!');</script>";
        header('Location: ../home.php');
    }
    $pwdHashed = $uid["usersPwd"]; 
    if($pwdHashed != $pwd){
        header('Location: ../profile.php?id='.$username."pwd=".$pwd);
        exit();
    }else if($pwdHashed == $pwd){
        session_start();
        $_SESSION["userid"] = $uid["usersId"];
        $_SESSION["useruid"] = $uid["usersUid"];
        header('Location: ../profile.php?sessionid='.$_SESSION["userid"]);
        exit();
    }else{
        header('Location: '.$url."?user=notset");
        exit();
    }
}
