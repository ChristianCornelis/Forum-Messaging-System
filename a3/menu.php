<?php
	//grabbing username
	/*$fptr = fopen("usernameData", "r");
	$username = fgets($fptr);
	fclose($fptr);*/

	echo("AAA" . $_POST["username"]);

	//generating HTML code for webpage
	$cmd = './converter config/menu.wpml';
	exec($cmd, $output, $status);
	//if exec unsuccessful
	if ($status)
			echo('Exec() failed');
	else
	{
		//echoing HTML to screen
		foreach($output as $line)
		{
			echo $line;
			//checking if all user's subscribed streams should be outputted
			if (strstr($line, "Stream options for this user:") != NULL)
			{
				//outputting user's streams
				$cmd2 = './view.py *OUTPUT* ' . escapeshellarg($username) . ' 0';
				exec($cmd2, $output2, $status2);

				if ($status2)
						echo('Exec() failed');
				else
				{
						foreach($output2 as $line2)
								echo $line2;
				}
				echo "<br><br>";
			}
		}
	}

	//if submit button to go to the viewing program is pushed
	if (isset($_POST["submit"]))
	{
		echo "IN";
		$stream = $_POST["streamInput"];
		$fptr3 = fopen("streamData", "w");
		fwrite($fptr3, $stream);
		fclose($fptr3);
	}

 ?>
