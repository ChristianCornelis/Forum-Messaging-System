<?php

	$username = $_POST["username"];
	$offset = 0;
	echo("Currently logged in as: " . $username);

	//generating HTML code for webpage
	$cmd = './converter config/viewMenu.wpml';
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
				echo "<br>";
			}
			//else check if a hidden field should be filled
			else if (strstr($line, "ENTER USERNAME HERE") != NULL)
			{
				echo (str_replace("ENTER USERNAME HERE", $username, $line));
			}
			else if (strstr($line, "ENTER OFFSET HERE") != NULL)
			{
				echo (str_replace("ENTER OFFSET HERE", $offset, $line));
			}
			//else output the line
			else
			{
				echo $line;
			}
		}
	}

 ?>