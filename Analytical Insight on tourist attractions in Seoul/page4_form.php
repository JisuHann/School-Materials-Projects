<!DOCTYPE html>
<html>
<head>
        <meta lang = "UTF-8">
        <title>Hallyu delete</title>
    </head>
    <body>
    <?php 
        include("base.php");
        require_once './includes/dbhc.inc.php';
    ?>
    <div id = "wrapper">
        <button class="button button1" onclick="location.href='./page4_main.php'">Back</button>
        <br><br><br>
        <?php
            if(!$conn){
                die('could not connect:'.mysql_error());
            }else if($_POST["form_name"]=="course"){
                
            }
            else{
                if ($_POST["form_name"]=="insert"){
                    $sql = "insert into hallyu values (('".$_POST["which_gu"]."'),('".$_POST["which_name"]."'),('".$_POST["which_grp"]."'),('".$_POST["which_who"]."'),('".$_POST["which_insta"]."'),('".$_POST["which_value"]."'))"; 
                }
                if ($_POST["form_name"]=="delete"){
                    $sql = "Delete from hallyu where name =  '".$_POST["delete_name"]."'";
                }
                if ($_POST["form_name"]=="update"){
                    $sql = "UPDATE hallyu set ".$_POST["update_attribute"]." = ".$_POST["update_to"]." WHERE name= '".$_POST["update_name"]."'";  
                }
                if ($_POST["form_name"]=="select"){
                    $where = "";
                    if(isset($_POST['cb2'])){
                        if($where != ""){ $where =  $where."OR who LIKE '%BTS%'";
                        }else{$where =  $where."who LIKE '%BTS%'";}
                    }
                    if(isset($_POST['cb3'])){
                        if($where != ""){ $where =  $where."OR who LIKE '%NCT%'";
                        }else{ $where =  $where." who LIKE '%NCT%' ";}
                    }
                    if(isset($_POST['cb4'])){
                        if($where != ""){$where =  $where."OR who LIKE '%BlackPink%'";
                        }else{$where =  $where."who LIKE '%BlackPink%'";}
                    }
                    if(isset($_POST['cb5'])){
                        if($where != ""){$where =  $where."OR grp = 'kdrama'";
                        }else{$where =  $where."grp = 'kdrama'";}
                    }
                    if(isset($_POST['cb6'])){
                        if($where != ""){ $where =  $where."OR grp LIKE 'kbeauty'";
                        }else{$where =  $where."grp LIKE 'kbeauty'";}}
                    $sql = "select * from hallyu where ".$where; 
                    if(isset($_POST['cb1'])){
                        if($where != ""){$sql = "select gu, name,grp, who,value, rank() over (order by insta desc) as rank from hallyu where ".$where;
                        }else {$sql = "select gu, name,grp, who, value,rank() over (order by insta desc) as rank from hallyu";}
                    }
                    if(isset($_POST['cb7'])){
                        if($where != ""){$sql = "select gu, name,grp, who,value, rank() over (order by value desc) as rank from hallyu where ".$where;
                        }else {$sql = "select gu, name,grp, who, value,rank() over (order by insta desc) as rank from hallyu";}}
                }
                
                $res = mysqli_query($conn, $sql);
                if($res){
                    $sql2 = "Select * from hallyu"; 
                    if($_POST["form_name"]=="select"){
                        $sql2 = $sql;
                    }
                    $res2 = mysqli_query($conn, $sql2);
                    echo "<table class = 'table table-hover'>";
                    echo "<tr class='table-success'><th>District</th><th>Name</th><th>Group</th><th>who</th><th>compare</th><th>value</th>";
                    
                    while($newArray = mysqli_fetch_array($res2, MYSQLI_ASSOC)){
                        $gu = $newArray['gu'];
                        $name = $newArray['name'];
                        $grp = $newArray['grp'];
                        $who = $newArray['who'];
                        if(isset($_POST['cb7'])){
                            $insta = $newArray['rank'];
                        }else if(isset($_POST['cb1'])){
                            $insta = $newArray['rank'];
                        }
                        else{
                            $insta = $newArray['insta'];
                        }
                        
                        $value = $newArray['value'];
    
                        echo "<tr>";
                        echo "<td>" . $gu . "</td>";
                        echo "<td>" . $name . "</td>";
                        echo "<td>" . $grp . "</td>";
                        echo "<td>" . $who . "</td>";
                        echo "<td>" . $insta . "</td>";
                        echo "<td>" . $value . "</td>";
                        echo "</tr>";
                    }
                    echo "</table>";
                }else{
                    printf("Could not retrieve records. %s\n", mysqli_error($conn));
                }
            }

            if($_POST["form_name"]=="course"){
                $where = "( gu = '".$_POST["sel_gu"]."') ";
                $condition = "";
                    if(isset($_POST['cb2'])){
                        if($condition != ""){ $condition =  $condition."OR who LIKE '%BTS%'";
                        }else{$condition =  $condition."who LIKE '%BTS%'";}
                    }
                    if(isset($_POST['cb3'])){
                        if($condition != ""){ $condition =  $condition."OR who LIKE '%NCT%'";
                        }else{ $condition =  $condition." who LIKE '%NCT%' ";}
                    }
                    if(isset($_POST['cb4'])){
                        if($condition != ""){$condition =  $condition."OR who LIKE '%BlackPink%'";
                        }else{$condition =  $condition."who LIKE '%BlackPink%'";}
                    }
                    
                    if(isset($_POST['cb5'])){
                        if($condition != ""){$condition =  $condition."OR grp = 'kdrama'";
                        }else{$condition =  $condition."grp = 'kdrama'";}
                    }
                    if(isset($_POST['cb6'])){
                        if($condition != ""){ $condition =  $condition."OR grp LIKE 'kbeauty'";
                        }else{$condition =  $condition."grp LIKE 'kbeauty'";}}
                    $sql2 = "select * from hallyu where ".$where." AND (".$condition.")"; 
                    if(isset($_POST['cb1'])){
                        if($condition != ""){$sql2 = "select gu, name,grp, who,value, rank() over (order by insta desc) as rank from hallyu where ".$where;
                        }else {$sql2 = "select gu, name,grp, who, value,rank() over (order by insta desc) as rank from hallyu";}
                    }
                    if(isset($_POST['cb7'])){
                        if($where != ""){$sql2= "select gu, name,grp, who,value, rank() over (order by value desc) as rank from hallyu where ".$where;
                        }else {$sql2 = "select gu, name,grp, who, value,rank() over (order by insta desc) as rank from hallyu";}}
                
                $sql = "select * from food where gu = '".$_POST["sel_gu"]."' order by (food+service+value)/3 desc";
                $res2 = mysqli_query($conn, $sql2);
                $res = mysqli_query($conn, $sql);
                $day = (int)$_POST["sel_day"];
                while ($day!=0){
                    echo "Day ".$day."<br><br>";
                    
                    $hallyu_row1 = mysqli_fetch_array($res2);
                    if($hallyu_row1 != null){
                        echo "<table class = 'table table-hover'>";
                        echo "<tr class='table-success'><th>District</th><th>Name</th><th>Group</th></tr>";
                        $gu = $hallyu_row1['gu'];
                        $name = $hallyu_row1['name'];
                        $grp = $hallyu_row1['grp'];
                        echo "<tr>";
                        echo "<td>" . $gu . "</td>";
                        echo "<td>" . $name . "</td>";
                        echo "<td>" . $grp . "</td></tr>";
                        $hallyu_row2 = mysqli_fetch_array($res2);
                        $gu = $hallyu_row2['gu'];
                        $name = $hallyu_row2['name'];
                        $grp = $hallyu_row2['grp'];
                        echo "<tr>";
                        echo "<td>" . $gu . "</td>";
                        echo "<td>" . $name . "</td>";
                        echo "<td>" . $grp . "</td></tr>";
                        echo "</table>";
                    }
                    else{
                        echo "There is no appropriate data! Try again";
                    }

                    echo "<table class = 'table table-hover'>";
                    echo "<tr class='table-success'><th>District</th><th>Name</th><th>Group</th></tr>";
                    
                    $food_row1 = mysqli_fetch_array($res);
                    if($food_row1 != null){
                        $gu = $food_row1['gu'];
                        $name = $food_row1['name'];
                        $grp = $food_row1['grp'];
                        echo "<tr>";
                        echo "<td>" . $gu . "</td>";
                        echo "<td>" . $name . "</td>";
                        echo "<td>" . $grp . "</td></tr>";
                        $food_row2 = mysqli_fetch_array($res);
                        $gu = $food_row2['gu'];
                        $name = $food_row2['name'];
                        $grp = $food_row2['grp'];
                        echo "<tr>";
                        echo "<td>" . $gu . "</td>";
                        echo "<td>" . $name . "</td>";
                        echo "<td>" . $grp . "</td></tr>";
                        $food_row3 = mysqli_fetch_array($res);
                        $gu = $food_row3['gu'];
                        $name = $food_row3['name'];
                        $grp = $food_row3['grp'];
                        echo "<tr>";
                        echo "<td>" . $gu . "</td>";
                        echo "<td>" . $name . "</td>";
                        echo "<td>" . $grp . "</td></tr>";
                        echo "</table>";
                        $day = $day-1;
                    }
                    else{
                        echo "There is no appropriate data! Try again";
                    }

                }
                mysqli_free_result($res2);
                    mysqli_free_result($res);
                    
            }
            if(isset($_SESSION["useruid"])){
                loginsert($conn, $_SESSION["userid"],$_SESSION["useruid"],$sql);
                loginsert($conn, $_SESSION["userid"],$_SESSION["useruid"],$sql2);
            }
            mysqli_close($conn);
            ?>
</div>
        </body>
        <html>