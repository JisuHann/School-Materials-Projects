<!DOCTYPE html>
<html>
    <head>

    </head>
    <body>
        <?php
            $a = $_GET["php1"];
            $b = $_GET["php2"];
            $c = $_GET["sel"];
            echo httpspecialchars($a)."<br>";
            echo httpspecialchars($b)."<br>";
            echo httpspecialchars($c)."<br>";
            

            @$fp = fopen("./text.txt", "r");
            flock($fp, LOCK_SH);
            if(!$fp){
                echo "nothing";
            }
            while(!feop($fp)){
                $k = fgets($fp);
                echo $k."<br>";
            }
            flock($fp, LOCK_UN);
            fclose($fp);
        ?>
    </body>
</html>