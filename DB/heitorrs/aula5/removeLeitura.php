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

$idleituraIni = $_POST['idleituraIni'];
$idleituraFim = $_POST['idleituraFim'];

if ($idleituraIni <= $idleituraFim) {
  $quantRemover = $idleituraFim - $idleituraIni;

  for ($i=$idleituraIni; $i<=$idleituraFim;$i++) {

    $my_Insert_Statement = $my_Db_Connection->prepare("DELETE FROM leituraheitorrs WHERE idleituraheitorrs = :idleitura");
    $my_Insert_Statement->bindParam(':idleitura', $i);
    
    if ($my_Insert_Statement->execute()) {
      echo "<p>" . $i . ": Leitura Removida com sucesso!!</p>";
    } else {
      echo "Deu RUIM!";
    }
  }
}


?>
