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

if (($_POST['from']!='ESP8266')){
    $datatime = $_POST['datatime'];

}else{
    $h = "3"; //HORAS DO FUSO ((BRASÃLIA = -3) COLOCA-SE SEM O SINAL -).
    $hm = $h * 60;
    $ms = $hm * 60;    //COLOCA-SE O SINAL DO FUSO ((BRASÃLIA = -3) SINAL -) ANTES DO ($ms). DATA
    $datatime = gmdate("Y/m/d H:i:s", time()-($ms));     
}

$idmac = $_POST['idmac'];

$umidade = $_POST['umidade'];
$temperatura = $_POST['temperatura'];

$my_Insert_Statement = $my_Db_Connection->prepare(
"INSERT INTO leituraheitorrs (macheitorrs_idmacheitorrs, datatime , umidade, temperatura) 
VALUES (:idmac, :datatime , :umidade, :temperatura) "
);

$my_Insert_Statement->bindParam(':idmac', $idmac);
$my_Insert_Statement->bindParam(':datatime', $datatime);
$my_Insert_Statement->bindParam(':umidade', $umidade);
$my_Insert_Statement->bindParam(':temperatura', $temperatura);

if ($my_Insert_Statement->execute()) {
  echo " Enviado com sucesso!";
} else {
  echo "deu merda";
}