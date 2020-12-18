<!DOCTYPE html>
<html>
    <head>

    </head>
    <body>
        <?php 
            $a = $_GET["php1"];
            $b = $_GET["php2"];
            $c = $_GET["php_sel"];

            echo ($a)."<br>";
            echo ($b)."<br>";
            echo ($c)."<br>";

            @$fp = fopen("./text.txt", "r");
            flock($fp, LOCK_SH);
            if(!$fp){
                echo "no file";
            }
            else{
                while(!feof($fp)){
                    $k = fgets($fp);
                    echo ($k)."<br>";
                }
            }
            flock($fp, LOCK_UN);
            fclose($fp);
        ?>
    </body>
</html>