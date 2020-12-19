<!DOCTYPE html>
<html>
    <!--index는 rank, insta,name합친거 쓰라는 말 없긴했는데 혹시 있는지 확인하기-->
    <head>
        <meta lang = "UTF-8">
        <title>Food Main</title>
        <link rel = "stylesheet" href = "./style.css">
    </head>
    <body>
        <?php 
            include('base.php'); 
            require_once 'includes/dbhc.inc.php';
        ?>
        <div id = "wrapper">
        <?php include("page3_button.html");?>
        <?php
            echo "<br>";
            if(!$conn){
                die('could not connect:'.mysql_error());
            }else{
                $sql = "select gu,name,grp,rank() over(partition by gu order by(food+service+value)/3 desc) as rank2, food, service, value, 11-ntile(10) over(order by insta desc) as insta_rank from food"; 
                $res = mysqli_query($conn, $sql);
                if($res){
                    echo "<table class = 'table table-hover'>";
                    echo "<tr class='table-success'><th>District</th><th>Name</th><th>Group</th><th>food</th><th>service</th><th>value</th><th>insta rank</th></tr>";
                    while($newArray = mysqli_fetch_array($res, MYSQLI_ASSOC)){
                        $gu = $newArray['gu'];
                        $name = $newArray['name'];
                        $grp = $newArray['grp'];
                        //$rank = $newArray['rank2'];
                        //$insta = $newArray['insta'];
                        //$insta = $newArray['inst'];
                        $food = $newArray['food'];
                        $service = $newArray['service'];
                        $value = $newArray['value'];
                        $insta_rank = $newArray['insta_rank'];
                        
                        echo "<tr>";
                        echo "<td>" . $gu . "</td>";
                        echo "<td>" . $name . "</td>";
                        echo "<td>" . $grp . "</td>";
                        //echo "<td>" . $rank . "</td>";
                        //echo "<td>" . $insta . "</td>";
                        echo "<td>" . $food . "</td>";
                        echo "<td>" . $service . "</td>";
                        echo "<td>" . $value . "</td>";
                        echo "<td>" . $insta_rank . "</td>";
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
