<?php
$servername = "localhost";
$database = "miguelde_modulo4"; 
$username = "miguelde_modulo4";
$password = "modulo4";
$sql = "mysql:host=$servername;dbname=$database;";
$dsn_Options = [PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION];
try { 
  $my_Db_Connection = new PDO($sql, $username, $password, $dsn_Options);
  echo "Connected successfully";
} catch (PDOException $error) {
  echo 'Connection error: ' . $error->getMessage();
}

// Set the variables for the person we want to add to the database

$idmac = $_POST['idmac'];
$idmac = $_POST['datatime'];
$idmac = $_POST['umidade'];
$idmac = $_POST['temperatura'];

$my_Insert_Statement = $my_Db_Connection->prepare(
"INSERT INTO leituraheitorrs (macheitorrs_idmacheitorrs, datatime , umidade, temperatura) 
VALUES (:macheitorrs_idmacheitorrs, :datatime , :umidade, :temperatura) "
);

$my_Insert_Statement->bindParam(':macheitorrs_idmacheitorrs', $idmac);
$my_Insert_Statement->bindParam(':datatime', $datatime);
$my_Insert_Statement->bindParam(':umidade', $umidade);
$my_Insert_Statement->bindParam(':temperatura', $temperatura);

if ($my_Insert_Statement->execute()) {
  echo "Enviado com sucesso!";
} else {
  echo "deu merda";
}