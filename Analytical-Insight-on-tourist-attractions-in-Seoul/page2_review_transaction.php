<?php include("base.php")?>
<html>
<head>
  <link rel="stylesheet" href = './style.css'>
</head>
<div class= "container">

<form action="page2_review_transaction.php" method="GET">
  <br>
  <h3 class="text-center"> Have you been to any above places already? </h3><br>
  <div class="row">
      <input type="text" name="name" class="form-control" placeholder="Place Name">
    </div>
<br>
    <div class="row">
      <input type="number" name="review" placeholder="review(scale 0.0 ~ 5.0)" class="form-control" data-decimals="1" min="0" max="5" step="0.5"/>
    </div>


<br>
      <div class="col-auto my-1">
        <button type="submit" class="button button1">Submit</button>
      </div>
        </div>
<br>
</form>
</div>

</html>
<?php
include_once 'includes/dbhc.inc.php';
if(!$conn){die('Connect Error ('.mysqli_connect_errno().')'.mysqli_connect_error());}
mysqli_autocommit($conn, FALSE);
error_reporting(E_ALL ^ E_NOTICE);
$query_success = TRUE;
$name =  $_GET['name'];
$review = $_GET['review'];
$sql = "
UPDATE major_attr
SET review = ROUND(review*0.75 + ?*0.25, 1)
WHERE name = ?;";
$stmt = mysqli_prepare($conn, $sql);
mysqli_stmt_bind_param($stmt, 'ds', $review, $name);
if(!mysqli_stmt_execute($stmt)) $query_success=FALSE;
mysqli_stmt_close($stmt);

$sql = "
SELECT gu, name, review
FROM major_attr
WHERE name = ?;";
$stmt = mysqli_prepare($conn, $sql);
mysqli_stmt_bind_param($stmt, 's', $name);
if(!mysqli_stmt_execute($stmt)) $query_success=FALSE;


if($query_success){

  mysqli_commit($conn);


  $res = mysqli_stmt_get_result($stmt);
  while($row = mysqli_fetch_assoc($res)){
    echo "<p class='text-center'>Updated Successfully</p>";
    echo "<br><div class='container'>";
    echo "<table class='table'>";
    echo"   <thead>
            <tr>
            <th scope='col'>District</th>
            <th scope='col'>Recommended Attraction</th>
            <th scope='col'>Review</th>
            </tr>
            </thead>";
    echo "<tbody>";
    $gu = $row['gu'];
    $name = $row['name'];
    $review = $row['review'];

    echo "<tr>";
    echo "<td>" . $gu . " Gu </td>";
    echo "<td>" . $name . "</td>";
    echo "<td>" . $review . "</td>";
    echo "</tr>";
    echo "</tbody>";
    echo "</table>";
    echo "</div>";
  }
  mysqli_free_result($res);
}
else{
  echo "Error";
  mysqli_rollback($conn);
}
mysqli_stmt_close($stmt);
mysqli_close($conn);
?>
