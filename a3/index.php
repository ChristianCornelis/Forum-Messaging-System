<?php
    $cmd = './converter config/login.wpml';
    exec($cmd, $output, $status);

    if ($status)
        echo('Exec() failed');
    else
    {
        foreach($output as $line)
            echo $line;
    }
	if (isset($_POST["submit"]))
	{
		echo "YES";
		$username = $_POST["usernameInput"];
		$fptr = fopen("usernameData", "w");
		fwrite($fptr, $username);
		fclose($fptr);

		header("location: view.php");
		//file_put_contents("usernameData", $username);
	}

?>
