<?php
$lux = '50';
$dt = date("Y-m-d H:i:s");
 $query = "INSERT INTO BH1750 VALUES (NULL, $lux,"."'$dt'".")";
echo $query;
?>
