<?php
	$username = $_POST["username"];
	echo("Currently logged in as: " . $username);

	$cmd = './converter config/addAuthor.wpml';
	exec($cmd, $output, $status);

	if ($status)
		echo('Exec() failed');
	else
	{
		foreach($output as $line)
		{
			if (strstr($line, "ENTER USERNAME HERE") != NULL)
			{
				echo (str_replace("ENTER USERNAME HERE", $username, $line));
			}
			else
				echo $line;
		}
	}


	if (isset($_POST["isRemovable"]))
	{
		switch($_POST["isRemovable"])
		{
			case "Add":
				if (strstr($_POST['streamInput'], " ") != NULL)
					echo("Error: No spaces can be present in the streams list.");
				else if (strcmp($_POST['streamInput'], "") == 0)
					echo("Error: Stream input cannot be left blank.");
				else
				{
					exec("./addauthor " . $_POST["streamInput"] ." " . $username, $output2, $status2);

					if ($status2)
						echo('Exec() failed.');
					else
					{
						foreach ($output2 as $line2) {
							echo $line2;
						}
					}
				}
				break;

			case "Remove":
				if (strstr($_POST['streamInput'], " ") != NULL)
					echo("Error: No spaces can be present in the streams list.");
				else if (strcmp($_POST['streamInput'], "") == 0)
					echo("Error: Stream input cannot be left blank.");
				else
				{
					exec("./addauthor " . $_POST["streamInput"] ." " . $username . " -r", $output3, $status3);

					if ($status3)
						echo('Exec() failed.');
					else
					{
						foreach ($output3 as $line3) {
							echo $line3;
						}
					}
				}
				break;

		}
	}
?>
