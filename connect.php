<?php

	function Connection(){
		$server="mysql.hostinger.in.th";
		$user="u394792511_nui";
		$pass="123456";
		$db="u394792511_hotel";

		$connection = mysql_connect($server, $user, $pass);

		if (!$connection) {
	    	die('MySQL ERROR: ' . mysql_error());
		}

		mysql_select_db($db) or die( 'MySQL ERROR: '. mysql_error() );

		return $connection;
	}
?>
