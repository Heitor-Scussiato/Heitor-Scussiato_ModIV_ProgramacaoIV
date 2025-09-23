<!DOCTYPE html>
<html lang="pt-BR">
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
 <head>
    <title>Lista LEITURAS Heitor</title>
<link rel="stylesheet" href="../style.css" type="text/css" />
</head>

<div class='container'>
<h1>Heitor Rauber Scussiato</h1>
<h3>Leituras Mac</h3>
</div>
<div class='container2'>

<?php
$username='miguelde_modulo4';
$password='modulo4';
$dbname='miguelde_modulo4';
$host='localhost';
try {
 $conn = new PDO("mysql:host=$host;dbname=$dbname", $username, $password);
 $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
 $sql='SELECT * FROM leituraheitorrs';
 $data = $conn->query($sql);
 echo ' <table>
 <tr>
     <th>Nº</th>
     <th>ID</th>
     <th>Data</th>
     <th>Umidade</th>
     <th>Temperatura</th>
     </tr>
 <tr>';
 foreach($data as $row) {
     echo '
     <tr>
     <td>'.$row[0].'</td>
     <td>'.$row[1].'</td>
     <td>'.$row[2].'</td>
     <td>'.$row[3].'%</td>
     <td>'.$row[4].'ºC</td>
     </tr>';
    }
    echo '</table> </div></html>';
    
} catch(PDOException $e) {
 echo 'ERROR: ' . $e->getMessage();
}
 ?>