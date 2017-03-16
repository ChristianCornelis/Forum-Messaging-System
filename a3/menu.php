<?php
	//grabbing username
	/*$fptr = fopen("usernameData", "r");
	$username = fgets($fptr);
	fclose($fptr);*/
	$username = $_POST["username"];
	echo("Currently logged in as: " . $username);

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

			//checking if all user's subscribed streams should be outputted
			if (strstr($line, "Stream options for this user:") != NULL)
			{
				echo $line;
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
			//else check if a hidden field should be filled
			else if (strstr($line, "ENTER USERNAME HERE") != NULL)
			{
				echo (str_replace("ENTER USERNAME HERE", $username, $line));
			}
			//else output the line
			else
			{
				echo $line;
			}
		}
	}

	//if submit button to go to the viewing program is pushed
	if (isset($_POST["submit"]))
	{
		$stream = $_POST["streamInput"];
		$fptr3 = fopen("streamData", "w");
		fwrite($fptr3, $stream);
		fclose($fptr3);
	}

 ?>
