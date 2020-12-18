<!DOCTYPE html>
<html>
    <head>

    </head>
    <body>
        <?php
            $a = $_GET["php1"];
            $b = $_GET["php2"];
            $c = $_GET["sel"];

            DEFINE('a1', 100);
            DEFINE('b1', 50);
            echo htmlspecialchars($a)."okay i have a1"."<br>";
            echo htmlspecialchars($b)."okay i have b1"."<br>";
            $tot_a = $a * $a1;
            $tot_b = $a * $b1;

            echo htmlspecialchars($tot_a)."this is total"."<br>";
            echo htmlspecialchars($tot_b)."this is total"."<br>";

            echo htmlspecialchars($c)."<br>";

            @$fp = fopen("./text.txt", "r");
            flock($fp, LOCK_SH);
            if(!$fp){
                echo "error";
            }
            while(!feof($fp)){
                $k = fgets ($fp);
                echo htmlspecialchars($k)."<br>";
            }
            flock($fp, LOCK_UN);
            fclose($fp);
        ?>
    </body>
</html>