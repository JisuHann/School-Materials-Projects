<!DOCTYPE html>
<html>
    <head>
        <meta charset = "utf-8">
    </head>
    <body>
        <?php
            $a = $_GET["php1"];
            $b = $_GET["php2"];

            echo htmlspecialchars($a)."<br>";
            echo htmlspecialchars($a)."<br>";

            @$fp = fopen("./text.txt", "r");
            flock($fp, LOCK_SH);
            if(!$fp){
                echo "error happened";
            }
            while(!feof($fp)){
                $k = fgets($fp);
                echo htmlspecialchars($k)."<br>";
            }
            flock($fp, LOCK_UN);
            fclose($fp);
        ?>
    </body>
</html>