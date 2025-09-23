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

$idleitura = $_POST['idleitura'];
$idmac = $_POST['idmac'];
$datatime = $_POST['hora'];
$umidade = $_POST['umidade'];
$temperatura = $_POST['temperatura'];

$my_Insert_Statement = $my_Db_Connection->prepare(
"UPDATE leituraheitorrs 
 SET macheitorrs_idmacheitorrs = :idmac,
   datatime = :hora,
   umidade = :umidade,
   temperatura=:temperatura
 WHERE idleituraheitorrs = :idleitura"
);

$my_Insert_Statement->bindParam(':idleitura', $idleitura);
$my_Insert_Statement->bindParam(':idmac', $idmac);
$my_Insert_Statement->bindParam(':hora', $datatime);
$my_Insert_Statement->bindParam(':umidade', $umidade);
$my_Insert_Statement->bindParam(':temperatura', $temperatura);

if ($my_Insert_Statement->execute()) {
  echo " Enviado com sucesso!";
} else {
  echo "deu merda";
}