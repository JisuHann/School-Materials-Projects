<!DOCTYPE html>
<html>
    <!--index는 rank, insta,name합친거 쓰라는 말 없긴했는데 혹시 있는지 확인하기-->
    <head>
        <meta lang = "UTF-8">
        <title>Profile</title>
        <link rel = "stylesheet" href = "./style.css">
    </head>
    <body>
        <?php include('base.php'); ?>
        <div id = "wrapper">
        <?php
            echo "Hello, ".$_SESSION["useruid"];
            include_once 'includes/dbhc.inc.php';
            if(!$conn){
                die('could not connect:'.mysql_error());
            }else{
                $sql = "select * from log where usersUid='".$_SESSION["useruid"]."' order by ontime asc"; 
                //Gu- 평균 + insta
                $res = mysqli_query($conn, $sql);
                if($res){
                    echo "<table class = 'table table-hover'>";
                    echo "<tr class='table-success'><th>timestamp</th><th>Command name</th></tr>";
                    while($newArray = mysqli_fetch_array($res, MYSQLI_ASSOC)){
                        $time = $newArray['ontime'];
                        $cmd = $newArray['command'];

                        echo "<tr>";
                        echo "<td>" . $time . "</td>";
                        echo "<td>" . $cmd . "</td>";
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