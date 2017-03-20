<?php

	$username = $_POST["username"];

	if (strcmp($username, "") == 0)
		$username= 'Guest User';
	else if (strcmp($username, " ") == 0)
		$username = 'Guest User';

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

			//check if a hidden field should be filled
			if (strstr($line, "ENTER USERNAME HERE") != NULL)
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

 ?>
