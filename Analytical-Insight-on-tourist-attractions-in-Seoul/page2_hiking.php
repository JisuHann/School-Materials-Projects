<?php include("base.php")?>
<div class= "container">
<form action="page2_hiking.php" method="GET">
  <br>
  <h2 class="text-center">See All Data </h2><br>
  <form>

      <div class="col-auto my-1">
        <button type="submit" class="button button1">Select All</button>
      </div>
</form>
</div>
</html>
<?php
include_once 'includes/dbhc.inc.php';
if(!$conn){die('Connect Error ('.mysqli_connect_errno().')'.mysqli_connect_error());}
error_reporting(E_ALL ^ E_NOTICE);

$sql = "
Select * from hiking_trail ";
$res = mysqli_query($conn, $sql);
if($res){

    echo "<br><div class='container'>";
    echo "<table class='table'>";
    echo"   <thead>
            <tr>
            <th scope='col'>District</th>
            <th scope='col'>Mountain</th>
            <th scope='col'>Entrance</th>
            <th scope='col'>Distance(km)</th>
            <th scope='col'>Time(hour)</th>
            <th scope='col'>Difficulty</th>
            </tr>
            </thead>";
    echo "<tbody>";

    while($row = mysqli_fetch_assoc($res)){

        $gu = $row['gu'];
        $mountain = $row['mountain'];
        $entrance = $row['entrance'];
        $distance = $row['distance'];
        $time = $row['time'];
        $difficulty = $row['difficulty'];

        echo "<tr>";
        echo "<td>" . $gu . " Gu </td>";
        echo "<td>" . $mountain . "</td>";
        echo "<td>" . $entrance . "</td>";
        echo "<td>" . $distance . "</td>";
        echo "<td>" . $time . "</td>";
        echo "<td>" . $difficulty . "</td>";
        echo "</tr>";

    }
    echo "</tbody>";
    echo "</table>";
    echo "</div>";
}else{
    printf("Could not retrieve records. %s\n", mysqli_error($mysqli));
}

?>
<html>
<head>
  <link rel="stylesheet" href = './style.css'>
</head>
<div class= "container">
<form action="page2_hiking_insert.php" method="GET">
  <br>
  <h2 class="text-center">Insert Data </h2><hr>

    <div class="row">
      <div class="col">
        <input type="text" class="form-control" name="gu" placeholder="District">
      </div>
      <div class="col">
        <input type="text" class="form-control" name="mountain" placeholder="Mountain">
      </div>
      <div class="col">
        <input type="text" class="form-control" name="entrance" placeholder="Entrance">
      </div>
    </div>
    <div class="row">
      <div class="col">
        <input type="number" name="distance" placeholder="Distance(km)" class="form-control" data-decimals="1" min="0" max="8000" step="0.1"/>
      </div>
      <div class="col">
        <input type="number" name="time" placeholder="Time(hour)" class="form-control" data-decimals="1" min="0" max="8000" step="0.1"/>
      </div>
      <div class="col">
        <input type="text" class="form-control" name="difficulty" placeholder="Difficulty">
      </div>
    </div>

        <hr>
      <div class="col-auto my-1">
        <button type="submit" class="button button1">Submit</button>
      </div>
</form>
</div>
</html>

<div class= "container">
<form action="page2_hiking_delete.php" method="GET">
  <br>
  <h2 class="text-center">Delete Data </h2><hr>
    <div class="row">
      <div class="col">
        <input type="text" class="form-control" name="entrance" placeholder="Entrance">
      </div>
    </div>
        <hr>
      <div class="col-auto my-1">
        <button type="submit" class="button button1">Submit</button>
      </div>
</form>
</div>
</html>

<div class= "container">
<form action="page2_hiking_update.php" method="GET">
  <br>
  <h2 class="text-center">Update Data </h2><hr>

    <p class="text-center">Select Entrance</p>
    <div class="row">
      <div class="col">
        <input type="text" class="form-control" name="entrance" placeholder="Entrance">
      </div>
    </div>
    <br><p class="text-center">Change To</p>
    <div class="row">
      <div class="col">
        <input type="number" name="distance" placeholder="Distance(km)" class="form-control" data-decimals="1" min="0" max="8000" step="0.1"/>
      </div>
      <div class="col">
        <input type="number" name="time" placeholder="Time(hour)" class="form-control" data-decimals="1" min="0" max="8000" step="0.1"/>
      </div>
      <div class="col">
        <input type="text" class="form-control" name="difficulty" placeholder="Difficulty">
      </div>
    </div>

        <hr>
      <div class="col-auto my-1">
        <button type="submit" class="button button1">Submit</button>
      </div>
</form>
</div>
<br><br>
</html>