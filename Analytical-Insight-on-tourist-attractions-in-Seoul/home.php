<!DOCTYPE html>
<html>
    <head>
        <meta lang = "UTF-8">
        <title>Home</title>
        <link rel = "stylesheet" href = "./style.css">
    </head>
    <body>
        <?php 
            include('base.php'); ?>
        <div id = "wrapper">
        <div class='container p-3 my-3 bg-success text-white'>
        <?php
            if(isset($_SESSION["userid"])){
                echo "<h3>Hello, ".$_SESSION["useruid"]."</h3>";
            }else{
                echo "<h3>Hello, Login and check out your daily log!</h3>";
            }
            ?>
        <p><br>this is the main page. Tap the tab to browse the site!<br><br>
For starters! | Check out the most visited district in Seoul!<br><br>
Attractions | Get recommendations on tourist attractions and hiking trails. <br><br>
Restaurants | You can make your own restaurant ranking<br><br>
Hallyu spots | In addition to ranking your own spots, you can also make courses along with restaurants!</p>
        </div>
        </div>
</body>
</html>