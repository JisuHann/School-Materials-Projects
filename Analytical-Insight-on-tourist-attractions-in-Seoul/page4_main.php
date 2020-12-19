<!DOCTYPE html>
<html>
    <head>
        <meta lang = "UTF-8">
        <title>Hallyu Main</title>
        <link rel = "stylesheet" href = "./style.css">
    </head>
    <body> 
        <?php
            include("base.php");
            require_once 'includes/dbhc.inc.php';
        ?>
        <div id = "wrapper" >
        <?php include("page4_button.html");?>
        <?php
        if(!$conn){
            die('could not connect:'.mysql_error());
        }else{
            $sql = "select gu, name, grp, who, ntile(10) over(order by insta desc) as insta_rank, value from hallyu order by insta_rank asc, value desc"; 
            //insta_rank 안에 score 정렬해야 하는데 하나 더 만든다음에야 가능해서 조금 더 봐야함.
            $res = mysqli_query($conn, $sql);
            if($res){
                echo "<table class = 'table table-hover'>";
                echo "<tr class='table-success'><th>District</th><th>Name</th><th>Group</th><th>who</th><th>insta</th><th>value</th></tr>";
                
                while($newArray = mysqli_fetch_array($res, MYSQLI_ASSOC)){
                    $gu = $newArray['gu'];
                    $name = $newArray['name'];
                    $grp = $newArray['grp'];
                    $who = $newArray['who'];
                    //$insta = $newArray['insta'];
                    $insta = $newArray['insta_rank'];
                    $score = $newArray['value'];

                    echo "<tr>";
                    echo "<td>" . $gu . "</td>";
                    echo "<td>" . $name . "</td>";
                    echo "<td>" . $grp . "</td>";
                    echo "<td>" . $who . "</td>";
                    echo "<td>" . $insta . "</td>";
                    echo "<td>" . $score . "</td>";
                    echo "</tr>";
                }
                echo "</table>";
            }else{
                printf("Could not retrieve records. %s\n", mysqli_error($mysqli));
            }
            mysqli_free_result($res);
            mysqli_close($conn);
        }
        ?>
    </div>
    </body>
</html>

