
<!DOCTYPE html>
<html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
  <link rel="stylesheet" href = './style.css'>
</head>
<body>
<?php $current_url = $_SERVER["HTTP_HOST"] . $_SERVER["REQUEST_URI"];?>
<div>
    <nav class="topnav" id="myTopnav">
        <a href="./home.php" class="active">Home</a>
        <a href='./page1_main.php'>For Starters</a>
        <a href='./page2_main.php'>Attractions</a>
        <a href='./page3_main.php'>Food</a>
        <a href='./page4_main.php'>Hallyu</a>
        <a href="javascript:void(0);" class="icon" onclick="myFunction()">
            <i class="fa fa-bars"></i>
        </a>
        <?php
        session_start();
          if(isset($_SESSION["useruid"])){
            echo "<a>Hello, ".$_SESSION["useruid"]."</a>";
            echo "<button class = 'button button1' onclick='howtoprofile()' style='width:auto;padding: 7px 7px;margin:5px 10px;'>Profile</button>";
            echo "<button class = 'button button1' onclick='howtologout()' style='width:auto;padding: 7px 7px;margin:5px 10px;'>Log Out</button>";
          }else{
            
            echo "<button class = 'button button1' onclick='howtosignup()' style='width:auto;padding: 7px 7px;margin:5px 10px;'>Sign Up</button>";
            echo "<button class = 'button button1' onclick='howtologin()' style='width:auto;padding: 7px 7px;margin:5px 10px;'>Login</button>";
          }
        ?>
        
      </nav>
</div>
<div id="id01" class="modal" >
      
  <form class="modal-content animate" action = "./includes/signup.inc.php" method="post">
    <div class="container">
    <input type = "hidden" name = "url" value = "<?php echo $current_url?>">
      <label for="name"><b>Username</b></label>
      <input type="text" placeholder="Enter Username..." class = "uname" name="name" required>

      <label for="name"><b>User Id</b></label>
      <input type="text" placeholder="Enter Id..." class = "uname" name="uid" required>

      <label for="pwd"><b>Password</b></label>
      <input type="password" placeholder="Enter Password..." class = "uname" name="pwd" required>
        
      <label for="pwd"><b>Repeat Password </b></label>
      <input type = "password" placeholder = "Repeat Password..." class = "uname" name="pwdrepeat" required>
      <button type="submit" class = "button button1" name = "submit2">Sign up</button>
    </form>

    </div>
</div>

<div id="id02" class="modal" >
      
  <form class="modal-content animate" action="./includes/login.inc.php"  method="post">
    <div class="container">
    <input type = "hidden" name = "url" value = "<?php echo $current_url?>">
      <label for="uname"><b>Username/Id</b></label>
      <input type="text" placeholder="Enter Username/Id..." class = "uname" name="uid" required>

      <label for="psw"><b>Password</b></label>
      <input type="password" placeholder="Enter Password" class = "uname" name="pwd" required>
        
      <button type="submit"  name = "submit" class = "button button1" >Login</button>
    </form>
    </div>
</div>


  <script>
  function myFunction() {
    var x = document.getElementById("myTopnav");
    if (x.className === "topnav") {
      x.className += " responsive";
    } else {
      x.className = "topnav";
    }
  }
    var modal1 = document.getElementById('id01');
    var modal2 = document.getElementById('id02');
    window.onclick = function(event) {
      if (event.target == modal1) {
          modal1.style.display = "none";
      }
      if (event.target == modal2) {
          modal2.style.display = "none";
      }
    }
  function howtosignup(){
    document.getElementById('id01').style.display="block";
  }
  function howtologin(){
    document.getElementById('id02').style.display="block";
  }
  function direction(){
    return location.pathname;
  }
  function howtoprofile(){
    location.href='./profile.php';
  }
  function howtologout(){
    location.href='./includes/logout.inc.php';
  }
</script>
</body>
</html>