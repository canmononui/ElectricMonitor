<?php
include 'connect.php';
	$volt1=$_POST["volt1"];
	$amp_all1=$_POST["amp_all1"];
	$amp_air1=$_POST["amp_air1"];
	$amp_water1=$_POST["amp_water1"];
	$amp_light1=$_POST["amp_light1"];
	$amp_plug1=$_POST["amp_plug1"];
	
	$sql = "INSERT INTO sensor`(id`, time, volt, amp_all, amp_air, amp_water, amp_light, amp_plug)";
	$sql .= "VALUES ("."NULL".",'"."CURRENT_TIMESTAMP"."','".$volt1."','".$amp_all1."','".$amp_air1."','".$amp_water1."','".$amp_light1."','".$amp_plug1."')";
if($conn->query($sql))
{
    echo "OK";
}
$conn->close();
?>