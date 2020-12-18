<!DOCTYPE html>
<html>
    <head>

    </head>
    <body>
        <?php
            $a = $_GET["name1"];
            $b = $_GET["pwd1"];
            echo htmlspecialchars($a)."<br>";
            echo htmlspecialchars($b)."<br>";
            @$fp  = fopen("$document_root/text.txt", "r");
            flock ($fp, LOCK_SH);
            if(!($fp)){
                
            }
            while(!feof($fp)){
                $k = fgets($fp);
                echo htmlspecialchars($k);
            }
            flock($fp, LOCK_UN);
            fclose($fp);
        ?>
    </body>
</html>