<?php
$username='miguelde_modulo4';
$password='modulo4';
$dbname='miguelde_modulo4';
$host='localhost';
try {
 $conn = new PDO("mysql:host=$host;dbname=$dbname", $username, $password);
 $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
 $sql='SELECT * FROM macheitorrs';
 $data = $conn->query($sql);
 echo '<html>
 <link rel="stylesheet" href="../style.css" type="text/css" />

 <div class="container">
<h1>Heitor Rauber Scussiato</h1>
<h3>Placas & Mac</h3>
</div>
<div class="container2">

 <table border=2>
 <tr>
     <th>Nome</th>
     <th>ID</th>
     <th>Valor</th>
 </tr>
 <tr>';
 foreach($data as $row) {
    echo '
    <tr>
    <td>'.$row[1].'</td>
    <td>'.$row[0].'</td>
    <td>'.$row[2].'</td>
    </tr>';
 }
 echo '</table> </div></html>';
} catch(PDOException $e) {echo 'ERROR: ' . $e->getMessage();}