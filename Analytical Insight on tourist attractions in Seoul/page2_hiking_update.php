<?php include("base.php")?>
<?php
include_once 'includes/dbhc.inc.php';
if(!$conn){die('Connect Error ('.mysqli_connect_errno().')'.mysqli_connect_error());}
error_reporting(E_ALL ^ E_NOTICE);
$entrance = $_GET['entrance'];
$distance = $_GET['distance'];
$time = $_GET['time'];
$difficulty = $_GET['difficulty'];

$sql = "
UPDATE hiking_trail
SET distance = ?, time = ?, difficulty = ?
WHERE entrance = ?;
 ";

$stmt = mysqli_stmt_init($conn);

  if(!mysqli_stmt_prepare($stmt, $sql)){
    echo "SQL statement failed";
  }
  else {
    //Bind parameters to the placeholder
    mysqli_stmt_bind_param($stmt, "ddss", $distance, $time, $difficulty, $entrance);
    mysqli_stmt_execute($stmt);
    echo "<br><br><p class='text-center'>Update Completed!</p>";
  }


if(isset($_SESSION)){

    $str = "update hiking_trail SET distance =".$distance.", time = ".$time.", difficulty = ".$difficulty."Where entrance = ".$entrance;
    $usersid = $_SESSION["userid"];
    $usersuid = $_SESSION["useruid"];
    $sql = "INSERT INTO log(usersId,usersUid, ontime, command) VALUES (".$_SESSION["userid"].",'".$usersuid."', now(),\"".$str."\")";
    $login_res = mysqli_query($conn, $sql);

    if($login_res){

    }else{
        printf( mysqli_error($conn));
    }
  }

  mysqli_close($conn);
?>
