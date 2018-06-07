<?php
   	include("connect.php");

   	$link=Connection();

	$volt1=$_POST["volt1"];
	$amp_all1=$_POST["amp_all1"];
	$amp_air1=$_POST["amp_air1"];
	$amp_water1=$_POST["amp_water1"];
	$amp_light1=$_POST["amp_light1"];
	$amp_plug1=$_POST["amp_plug1"];
	

	$query = "INSERT INTO sensor (volt,amp_all,amp_air,amp_water,amp_light,amp_plug)
		VALUES ('".$volt1."','".$amp_all1."','".$amp_air1."','".$amp_water1."','".$lamp_light1."','".$amp_plug1."')";

   	mysql_query($query,$link);
	mysql_close($link);

   	header("Location: index.php");
?>
