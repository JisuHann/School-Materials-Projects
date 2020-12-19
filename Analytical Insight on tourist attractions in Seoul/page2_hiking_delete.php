<?php include("base.php")?>
<?php
include_once 'includes/dbhc.inc.php';
if(!$conn){die('Connect Error ('.mysqli_connect_errno().')'.mysqli_connect_error());}
error_reporting(E_ALL ^ E_NOTICE);
$entrance = $_GET['entrance'];
$sql = "
Delete from hiking_trail Where entrance = ?;
 ";

$stmt = mysqli_stmt_init($conn);

  if(!mysqli_stmt_prepare($stmt, $sql)){
    echo "SQL statement failed";
  }
  else {
    //Bind parameters to the placeholder
    mysqli_stmt_bind_param($stmt, "s",$entrance);
    mysqli_stmt_execute($stmt);
  }


if(isset($_SESSION)){

    $str = "delete from hiking_trail Where entrance = '".$entrance."'";
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