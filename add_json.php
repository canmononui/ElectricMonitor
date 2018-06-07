<?php

	include("connect.php");
   	$link=Connection();

$query = "SELECT nome, cognome FROM Utenti WHERE codice='0d8dc'";
$persone = $connessione->query($query);
$persona = $persone->fetch_assoc();

echo json_encode($persona);
?>