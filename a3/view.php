<?php
	$fptr = fopen("usernameData", "r");
	$username = fgets($fptr);
	fclose($fptr);

	$cmd = './converter config/view.wpml';
	exec($cmd, $output, $status);

	if ($status)
			echo('Exec() failed');
	else
	{
			foreach($output as $line)
			{
				echo $line;
				if (strstr($line, "Stream options for this user:") != NULL)
				{
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
				else {
					//echo $line;
				}
			}
	}


		/*$cmd2 = './view.py *OUTPUT* ' . escapeshellarg($username) . ' 0';
		exec($cmd2, $output2, $status2);

		if ($status2)
				echo('Exec() failed');
		else
		{
				foreach($output2 as $line2)
						echo $line2;
		}*/

 ?>
