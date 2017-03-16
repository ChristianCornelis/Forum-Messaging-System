<?php
	//grabbing username
	$username = $_POST['username'];
	$stream = $_POST['streamInput'];
	echo ("Currently logged in as: " . $username);
	echo("<BR> Currently viewing the " . $stream . " stream");
	//generating HTML code for webpage
	$cmd = './converter config/view.wpml';
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
				if (strstr($line, "Post:") != NULL)
				{
					//outputting user's streams
					$cmd2 = './view.py  ' .escapeshellarg($stream) . " " .escapeshellarg($username) . ' 0';
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

 ?>
