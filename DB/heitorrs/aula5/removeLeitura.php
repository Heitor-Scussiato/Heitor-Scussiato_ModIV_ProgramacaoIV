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

$idleitura = $_POST['idleitura'];

$my_Insert_Statement = $my_Db_Connection->prepare("DELETE FROM leituraheitorrs WHERE idleituraheitorrs == :idleitura");
$my_Insert_Statement->bindParam(':idleitura', $idleitura);

if ($my_Insert_Statement->execute()) {
  echo " Leitura Removida com sucesso!!";
} else {
  echo "Deu RUIM!";
}
?>
