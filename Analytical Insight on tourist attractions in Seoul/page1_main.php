<?php include("base.php")?>
<html>
<head>
  <title>Major Attraction</title>
  <link rel="stylesheet" href = './style.css'>
</head>
</html>
<?php
include_once 'includes/dbhc.inc.php';


$sql = "
SELECT rank() over (order by (0.6*hotel + 0.4*tourism) desc) as gu_rank, gu, hotel, tourism
FROM visitor_gu
ORDER BY gu_rank;";
$res = mysqli_query($conn, $sql);
if($res){

    echo "<div class='container'>";
    echo "<br><h1 class='text-center'>Rank On Visited Districts in Seoul</h1><br>";
    echo "<table class='table'>";
    echo"   <thead>
            <tr>
            <th scope='col'>Rank</th>
            <th scope='col'>District</th>
            <th scope='col'>Number of Hotels</th>
            <th scope='col'>Number of Tourism Buisnesses</th>
            </tr>
            </thead>";
    echo "<tbody>";

    while($row = mysqli_fetch_assoc($res)){

        $gu_rank = $row['gu_rank'];
        $gu = $row['gu'];
        $hotel = $row['hotel'];
        $tourism = $row['tourism'];


        echo "<tr>";

        echo "<th scope='row'>" . $gu_rank . "</th>";
        echo "<td>" . $gu . " Gu </td>";
        echo "<td>" . $hotel . "</td>";
        echo "<td>" . $tourism . "</td>";
        echo "</tr>";

    }
    echo "</tbody>";
    echo "</table>";
    echo "</div>";
}else{
    printf("Could not retrieve records. %s\n", mysqli_error($mysqli));
}
mysqli_free_result($res);

$sql = "
SELECT gu, sum(visitor_year) as sum
FROM major_tourspot
GROUP BY gu
ORDER BY sum(visitor_year) desc;";
$res = mysqli_query($conn, $sql);
if($res){

    echo "<br><div class='container'>";
    echo "<h1 class='text-center'>The Visitors Last year</h1><br>";
    echo "<table class='table'>";
    echo"   <thead>
            <tr>
            <th scope='col'>District</th>
            <th scope='col'>Visitors(2019)</th>
            </tr>
            </thead>";
    echo "<tbody>";

    while($row = mysqli_fetch_assoc($res)){

        $gu = $row['gu'];
        $sum = $row['sum'];


        echo "<tr>";
        echo "<td>" . $gu . " Gu </td>";
        echo "<td>" . $sum . "</td>";
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


<div class= "container">
<form action="page1_main.php" method="POST">
  <h1 class="text-center">    The Most Visited places in District</h1><br>
    <div class="form-row align-items-center">
      <div class="col-auto my-1">
        <label class="mr-sm-2 sr-only" for="inlineFormCustomSelect">Preference</label>
        <select class="form-control form-control-sm" id="inlineFormCustomSelect" name="distriction">
          <option selected>Choose...</option>
          <option value="Songpa">Songpa</option>
          <option value="Jongno">Jongno</option>
          <option value="Jung">Jung</option>
          <option value="Yongsan">Yongsan</option>
          <option value="Seodaemun">Seodaemun</option>
          <option value="Gangnam">Gangnam</option>
          <option value="Mapo">Mapo</option>
          <option value="Nowon">Nowon</option>
          <option value="Dongdaemun">Dongdaemun</option>
          <option value="Seocho">Seocho</option>
        </select>
      </div>
      <div class="col-auto my-1">

        <button type="submit" class="button button1" onclick="onclick(event)">Submit</button>
      </div>
    </div>

</form>
</div>

  <script>

  function onclick(event) {
    event.preventDefault();
  }
  </script>

</html>

<?php
error_reporting(E_ALL ^ E_NOTICE);
$distriction = mysqli_real_escape_string($conn, $_POST['distriction']);

$sql = "
SELECT rank() over (order by visitor_year desc) as tourspot_rank, name, pay
FROM major_tourspot
WHERE gu = ?
ORDER BY tourspot_rank;";
$stmt = mysqli_stmt_init($conn);

  if(!mysqli_stmt_prepare($stmt, $sql)){
    echo "SQL statement failed";
  }
  else {
    //Bind parameters to the placeholder
    mysqli_stmt_bind_param($stmt, "s", $distriction);
    mysqli_stmt_execute($stmt);
    $res = mysqli_stmt_get_result($stmt);


    echo "<br><div class='container'>";

    echo "<table class='table'>";
    echo"   <thead>
            <tr>
            <th scope='col'>Rank</th>
            <th scope='col'>Place</th>
            <th scope='col'>Entrance Fee</th>
            </tr>
            </thead>";
    echo "<tbody>";

    while($row = mysqli_fetch_assoc($res)){
      $tourspot_rank = $row['tourspot_rank'];
      $name = $row['name'];
      $pay = $row['pay'];

      echo "<tr>";
      echo "<td>" . $tourspot_rank . "</td>";
      echo "<td>" . $name . "</td>";
      echo "<td>" . $pay . "</td>";
      echo "</tr>";
    }
    echo "</tbody>";
    echo "</table>";
    echo "</div>";

    echo "<br>";
  }

mysqli_free_result($res);
mysqli_close($conn);?>
