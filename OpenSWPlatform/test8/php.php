<!DOCTYPE html>
<html>
    <head>

    </head>
    <body>
        <?php
            $a = $_GET["php1"];
            $b = $_GET["php2"];
            $c = $_GET["sel"];
            
            echo $a."<br>";
            echo $b."<br>";
            echo $c."<br>";

            DEFINE ('a1', 1000);
            DEFINE('b1', 1);
            $tot_a = a1 * $a;
            $tot_b = b1 * $b;
            $tot = $tot_a + $tot_b;

            echo "the sum of a is ".$tot_a."<br>";
            echo "the sum of b is ".$tot_b."<br>";
            echo "the sum is ".$tot."<br>";

            @$fp = fopen("./text.txt", "r");
            flock($fp, LOCK_SH);
            if(!$fp){
                echo "error";
            }
            while(!feof($fp)){
                $t = fgets($fp);
                echo htmlspecialchars($t)."<br>";
            }
            flock($fp, LOCK_UN);
            fclose($fp);

        ?>
    </body>
</html>