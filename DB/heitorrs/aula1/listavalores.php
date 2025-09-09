<?php
$username='miguelde_modulo4';
$password='modulo4';
$dbname='miguelde_modulo4';
$host='localhost';
try {
 $conn = new PDO("mysql:host=$host;dbname=$dbname", $username, $password);
 $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
 $sql='SELECT * FROM leitura';
 $data = $conn->query($sql);
 echo '<html>
 <style> table {position: fixed; text-aling: center; left: 35%;} body {aling-content: center;} </style>
 <body>
 <table border=2>
 <tr>
     <th>Nº</th>
     <th>ID</th>
     <th>Placa</th>
     <th>Data</th>
     <th>Valor</th>
     </tr>
 <tr>';
 foreach($data as $row) {
     echo '
     <tr>
     <td>'.$row[0].'</td>
     <td>'.$row[1].'</td>
     <td>'.$row[2].'</td>
     <td>'.$row[3].'</td>
     <td>'.$row[4].'</td>
     </tr>';
    }
    echo '</table> </body></html>';
    
} catch(PDOException $e) {
 echo 'ERROR: ' . $e->getMessage();
}
 ?>