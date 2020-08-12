<?php


/*    echo $_SERVER["REQUEST_SCHEME"]."://".$_SERVER['HTTP_HOST'].$_SERVER['SCRIPT_NAME'];
    echo " "."\n";
    echo $_SERVER["QUERY_STRING"];
    echo " "."\r\n";
    echo $_GET['lux'];

 */

    if($_GET['lux'] !=''){
      $lux = $_GET['lux'];
    } else {
      $lux = NULL;
   }

   echo $lux;

/*    echo " "."\r\n";
    echo $_GET['temperature'];

    if($_GET['lux'] != ''){
            $bh1750 = new bh1750($_GET['lux']);
            echo 'hello';
            print_r($bh1750);
    }

 */

//$idea = 1;

//if($idea === 1) {

//class Logger
//{
//	public function log() {
//		echo "hello";
		        $mysqli = new mysqli("localhost", "root", "password", "scandalux");
        /* check connection */
        if (mysqli_connect_errno()) {
           printf("Connect failed: %s\n", mysqli_connect_error());
           exit();
         }

        $dt = date("Y-m-d H:i:s");
        // I need to create a value for ID that prints the next value
         $query = "INSERT INTO BH1750 VALUES (NULL, $lux,"."'$dt'".")";
        $mysqli->query($query);

         /* close connection */
         $mysqli->close()

//}
//	}

//}

//$logger = new Logger;
//$logger->log();

//Logger::log();

?>
