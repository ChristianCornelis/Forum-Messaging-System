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

		$username = $_POST["usernameInput"];
		$fptr = fopen("usernameData", "w");
		fwrite($fptr, $username);
		fclose($fptr);
		//initializing offset for viewing
		$fptr2 = fopen("viewData", "w");
		fwrite($fptr2, "0");
		fclose($fptr2);
		if (file_exists("messages/"))
			header("location: menu.php");
		else
			header("location: addAuthor.php");
	}

?>
