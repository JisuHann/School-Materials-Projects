<!DOCTYPE html>
<html>
    <head>
    <head>
        <meta lang = "UTF-8">
        <title>Page3 Main</title>
        <link rel = "stylesheet" href = "./style.css">
    </head>
    <body>
        <?php 
            include("base.php");
            require_once './includes/dbhc.inc.php';
        ?>
        <div id = "wrapper">
        <button class="button button1" onclick="location.href='./page3_main.php'">Back</button>
        <br><br><br>
        <?php
            if(!$conn){
                die('could not connect:'.mysql_error());
            }else{
                if ($_POST["form_name"]=="insert"){
                    $sql = "insert into food values (('".$_POST["which_gu"]."'),('".$_POST["which_name"]."'),('".$_POST["which_grp"]."'),('".$_POST["which_insta"]."'),('".$_POST["which_food"]."'),('".$_POST["which_service"]."'),('".$_POST["which_value"]."'))"; 

                }
                if ($_POST["form_name"]=="delete"){
                    $sql = "Delete from food where name =  '".$_POST["delete_name"]."'";
                }
                if ($_POST["form_name"]=="update"){
                    $sql = "UPDATE food set ".$_POST["update_attribute"]." = ".$_POST["update_to"]." WHERE name= '".$_POST["update_name"]."'"; 
                }
                if($_POST["form_name"]=="select"){
                    $sql ="Select * from food";
                }
                
                $res = mysqli_query($conn, $sql);
                
                $sql2 = "Select * from food"; 
                if($_POST["form_name"]=="select"){
                    $sql2 = "select gu,name,grp, rank() over(order by(food*".$_POST["food_range"]."+service*".$_POST["service_range"]."+value*".$_POST["value_range"].")/3 desc) as score_rank, 11-ntile(10) over(order by insta desc) as insta_rank from food";
                }
                if($res){
                    $res2 = mysqli_query($conn, $sql2);
                    echo "<table class = 'table table-hover'>";
                    if($_POST["form_name"]=="select"){
                        echo "<tr class='table-success'><th>District</th><th>Name</th><th>Group</th><th>score rank</th><th>insta rank</th></tr>";
                    }else{echo "<tr class='table-success'><th>District</th><th>Name</th><th>Group</th><th>who</th><th>insta</th><th>score</th><th>food</th></tr>";
                    }                
                    while($newArray = mysqli_fetch_array($res2, MYSQLI_ASSOC)){
                        $gu = $newArray['gu'];
                        $name = $newArray['name'];
                        $grp = $newArray['grp'];
                        echo "<tr>";
                        echo "<td>" . $gu . "</td>";
                        echo "<td>" . $name . "</td>";
                        echo "<td>" . $grp . "</td>";
                        if($_POST["form_name"]=="select"){
                            $insta = $newArray['insta_rank'];
                            $score = $newArray['score_rank'];
                            echo "<td>" . $score . "</td>";
                            echo "<td>" . $insta . "</td>";
                            
                        }else{
                            $insta = $newArray['insta'];
                            $food = $newArray['food'];
                            $service = $newArray['service'];
                            $value = $newArray['value'];
                            echo "<td>" . $insta . "</td>";
                            echo "<td>" . $food . "</td>";
                            echo "<td>" . $service . "</td>";
                            echo "<td>" . $value . "</td>";
                        }
                        echo "</tr>";
                    }
                    echo "</table>";
                }else{
                    printf("Could not retrieve records. %s\n", mysqli_error($conn));
                }
            }
            if(isset($_SESSION["useruid"])){
                loginsert($conn, $_SESSION["userid"],$_SESSION["useruid"],$sql);
            }
            mysqli_free_result($res2);
            mysqli_close($conn);
            ?>
            </div>
</body>
</html>
