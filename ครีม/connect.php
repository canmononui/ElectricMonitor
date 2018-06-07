<?php 
    $servername = "mysql.hostinger.in.th";
    $username = "u394792511_nui";
    $password = "123456";
    $dbname = "u394792511_hotel";
 // Create connection
$conn = new mysqli($servername, $username, $password,$dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
echo "connected";

?>