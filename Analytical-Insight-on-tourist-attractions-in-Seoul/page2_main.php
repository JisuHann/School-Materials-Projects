<?php include("base.php")?>
<html>
<head>
  <link rel="stylesheet" href = './style.css'>
</head>
<div class= "container">

<form action="page2_main.php" method="GET">
  <br>
  <h1 class="text-center">    Recommendation on Tourist Attractions </h1><br>
    <div>

      <div class="form-check form-check-inline">
        <input class="form-check-input" type="radio" name="season" id="inlineRadio1" value="Spring">
        <label class="form-check-label">Spring</label>
      </div>
      <div class="form-check form-check-inline">
        <input class="form-check-input" type="radio" name="season" value="Summer">
        <label class="form-check-label">Summer</label>
      </div>
      <div class="form-check form-check-inline">
        <input class="form-check-input" type="radio" name="season" value="Fall">
        <label class="form-check-label">Fall</label>
      </div>
      <div class="form-check form-check-inline">
        <input class="form-check-input" type="radio" name="season" value="Winter">
        <label class="form-check-label">Winter</label>
    </div>
</div>
<br>
    <div>

      <div class="form-check form-check-inline">
        <input class="form-check-input" type="radio" name="accompany" value="Friends">
        <label class="form-check-label">Friends</label>
      </div>
      <div class="form-check form-check-inline">
        <input class="form-check-input" type="radio" name="accompany" value="Lover">
        <label class="form-check-label">Lover</label>
      </div>
      <div class="form-check form-check-inline">
        <input class="form-check-input" type="radio" name="accompany" value="Family">
        <label class="form-check-label">Family</label>
      </div>
      <div class="form-check form-check-inline">
        <input class="form-check-input" type="radio" name="accompany" value="Kids">
        <label class="form-check-label">Kids</label>
    </div>
  </div>
        <br>
      <div class="col-auto my-1">
        <button type="submit" class="button button1">Submit</button>
      </div>
</form>
</div>

</html>
<?php
include_once 'includes/dbhc.inc.php';
if(!$conn){die('Connect Error ('.mysqli_connect_errno().')'.mysqli_connect_error());}
error_reporting(E_ALL ^ E_NOTICE);
$season =  $_GET['season'];
$accompany = $_GET['accompany'];

$sql = "
SELECT gu, name, review
FROM major_attr
WHERE season LIKE CONCAT('%',?,'%') AND accompany LIKE CONCAT('%',?,'%'); ";

$stmt = mysqli_stmt_init($conn);

  if(!mysqli_stmt_prepare($stmt, $sql)){
    echo "SQL statement failed";
  }
  else {
    //Bind parameters to the placeholder
    mysqli_stmt_bind_param($stmt, "ss", $season, $accompany);
    mysqli_stmt_execute($stmt);
    $res = mysqli_stmt_get_result($stmt);

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

    while($row = mysqli_fetch_assoc($res)){
      $gu = $row['gu'];
      $name = $row['name'];
      $review = $row['review'];

      echo "<tr>";
      echo "<td>" . $gu . " Gu </td>";
      echo "<td>" . $name . "</td>";
      echo "<td>" . $review . "</td>";
      echo "</tr>";
    }
    echo "</tbody>";
    echo "</table>";
    echo "</div>";
mysqli_free_result($res);
  }

?>
<div class="container">
<a href="page2_review_transaction.php">Update Review!</a>
</div>

<html>
<div class= "container">

<form action="page2_main.php" method="GET">
  <br>
  <h1 class="text-center">    Recommendation on Hiking Trails </h1><br>
  <div>
      <div class="form-check form-check-inline">
        <input class="form-check-input" type="radio" name="difficulty" value="Peaceful">
        <label class="form-check-label">Peaceful</label>
      </div>
      <div class="form-check form-check-inline">
        <input class="form-check-input" type="radio" name="difficulty" value="Easy">
        <label class="form-check-label">Easy</label>
    </div>
    <div class="form-check form-check-inline">
      <input class="form-check-input" type="radio" name="difficulty" value="Normal">
      <label class="form-check-label">Normal</label>
    </div>
    <div class="form-check form-check-inline">
      <input class="form-check-input" type="radio" name="difficulty" value="Hard">
      <label class="form-check-label">Hard</label>
    </div>
  </div>

        <br>
      <div class="col-auto my-1">
        <button type="submit" class="button button1">Submit</button>
      </div>
</form>
</div>



</html>
<?php

if(!$conn){die('Connect Error ('.mysqli_connect_errno().')'.mysqli_connect_error());}
error_reporting(E_ALL ^ E_NOTICE);
$difficulty = $_GET['difficulty'];

$sql = "
SELECT gu, mountain, entrance, distance, time
FROM hiking_trail
WHERE difficulty = ?; ";

$stmt = mysqli_stmt_init($conn);

  if(!mysqli_stmt_prepare($stmt, $sql)){
    echo "SQL statement failed";
  }
  else {
    //Bind parameters to the placeholder
    mysqli_stmt_bind_param($stmt, "s", $difficulty);
    mysqli_stmt_execute($stmt);
    $res = mysqli_stmt_get_result($stmt);

    echo "<br><div class='container'>";

    echo "<table class='table'>";
    echo"   <thead>
            <tr>
            <th scope='col'>District</th>
            <th scope='col'>Mountain</th>
            <th scope='col'>Entrance</th>
            <th scope='col'>Distance(km)</th>
            <th scope='col'>Time(hour)</th>
            </tr>
            </thead>";
    echo "<tbody>";

    while($row = mysqli_fetch_assoc($res)){
      $gu = $row['gu'];
      $mountain = $row['mountain'];
      $entrance = $row['entrance'];
      $distance = $row['distance'];
      $time = $row['time'];

      echo "<tr>";
      echo "<td>" . $gu . " Gu </td>";
      echo "<td>" . $mountain . "</td>";
      echo "<td>" . $entrance . "</td>";
      echo "<td>" . $distance . "</td>";
      echo "<td>" . $time . "</td>";
      echo "</tr>";
    }
    echo "</tbody>";
    echo "</table>";
    echo "</div>";
mysqli_free_result($res);
  }
  mysqli_close($conn);
?>
<div class="container">
<a href="page2_hiking.php">Data manipulation on Hiking Trails Table</a>
</div>
<br>
<br>
