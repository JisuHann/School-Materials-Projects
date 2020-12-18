<!DOCTYPE html> 
<html> 
<head> 
<title>Bob's Auto Parts - Order Results</title> 
</head> 
<body> 
<h1>Bob's Auto Parts</h1> 
<h2>Order Results</h2> 
<?php 
@$fp = fopen("$document_root/text.txt", 'r');
if (!$fp) {
echo "<p><strong>No orders pending.<br />
Please try again later.</strong></p>";
exit;
}
while (!feof($fp)) {
$order= fgets($fp);
echo htmlspecialchars($order)."<br />";
}
fclose($fp); 
?> 
</body> 
</html> 