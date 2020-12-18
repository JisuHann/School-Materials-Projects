<!DOCTYPE html>
<html>
    <head>
        <meta charset= "utf-8">
    </head>
    <body>
        <?php
            $a = $_GET["a"];
            $b = $_GET["b"];
            $sel = $_GET["sel"];

            echo htmlspecialchars($sel)."<br>";

            DEFINE('a1',23);
            DEFINE('b1',34);
            $tot_a = $a * a1;
            $tot_b = $b * b1;
            $tot = $tot_a + $tot_b;

            echo "a total is ".$tot_a."and b total is ".$tot_b."<br>";
            echo "total is".$tot."<br>";

            @$fp = fopen("./text.txt", "r");
            flock($fp, LOCK_SH);
            if(!$fp){
                echo "error";
            }
            while(!feof($fp)){
                $kk = fgets($fp);
                echo htmlspecialchars($kk)."<br>";
            }
            flock($fp, LOCK_UN);
            fclose($fp);

            @$fp2 = fopen("./text2.txt", "a");
            flock($fp2, LOCK_SH);
            if(!$fp2){
                echo "error";
            }
            fwrite($fp2, "is this right?");
            flock($fp2, LOCK_UN);
            fclose($fp2);
        ?>
    </body>
</html>