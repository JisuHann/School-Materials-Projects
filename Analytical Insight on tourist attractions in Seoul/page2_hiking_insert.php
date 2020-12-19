<?php include("base.php")?>
<?php
include_once 'includes/dbhc.inc.php';
if(!$conn){die('Connect Error ('.mysqli_connect_errno().')'.mysqli_connect_error());}
error_reporting(E_ALL ^ E_NOTICE);
$gu = $_GET['gu'];
$mountain = $_GET['mountain'];
$entrance = $_GET['entrance'];
$distance = $_GET['distance'];
$time = $_GET['time'];
$difficulty = $_GET['difficulty'];

$sql = "
Insert into hiking_trail values(?,?,?,?,?,?);
 ";

$stmt = mysqli_stmt_init($conn);

  if(!mysqli_stmt_prepare($stmt, $sql)){
    echo "SQL statement failed";
  }
  else {
    //Bind parameters to the placeholder
    mysqli_stmt_bind_param($stmt, "sssdds", $gu, $mountain, $entrance, $distance, $time, $difficulty);
    mysqli_stmt_execute($stmt);
    echo "<br><br><p class='text-center'>Insert Completed!</p>";
  }


if(isset($_SESSION)){

    $str = "insert into hiking_trail values(".$gu.",".$mountain.",".$entrance.",".$distance.",".$time.",".$difficulty.")";
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
