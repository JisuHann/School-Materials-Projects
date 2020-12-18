<!DOCTYPE html>
<html>
    <head>

    </head>
    <body>
        <?php

            $a = $_GET["php1"];
            $b = $_GET["php2"];
            $sel = $_GET["sel"];

            DEFINE('a1', 1000);
            DEFINE('b1', 1);
            $tot_a = a1 * $a;
            $tot_b = b1 * $b;
            $tot = $tot_a + $tot_b;
            $llll= "total a is ".$tot_a."and b is".$tot_b."<br>";
            echo "a is ".$a."and b is".$b."<br>";
            echo $llll."<br>";
            echo "the sum is".$tot."<br>";
            echo "and sel is".$sel."<br>";


            @$fp = fopen("./text.txt", "r");
            flock($fp, LOCK_SH);
            if(!$fp){
                echo "error";
            }
            while(!feof($fp)){
                $ll = fgets($fp);
                echo $ll."<br>";
            }
            flock($fp, LOCK_UN);
            fclose($fp);

            @$fp2 = fopen("./text2.txt", "w");
            fwrite($fp2, $llll, strlen($llll));
            fclose($fp2);
        ?>
    </body>
</html>