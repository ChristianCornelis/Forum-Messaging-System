<?php
	$cmd = './converter config/addAuthor.wpml';
	exec($cmd, $output, $status);

	if ($status)
		echo('Exec() failed');
	else
	{
		foreach($output as $line)
			echo $line;
	}


	if (isset($_POST["isRemovable"]))
	{
		$fptr = fopen("usernameData", "r");
		$username = fgets($fptr);
		fclose($Sfptr);
		switch($_POST["isRemovable"])
		{
			case "Add":
				exec("./addauthor " . $_POST["streamInput"] ." " . $username, $output2, $status2);

				if ($status2)
					echo('Exec() failed.');
				else
				{
					foreach ($output2 as $line2) {
						echo $line2;
					}
				}
				break;
			case "Remove":
				exec("./addauthor " . $_POST["streamInput"] ." " . file_get_contents("usernameData") . " -r", $output3, $status3);

				if ($status3)
					echo('Exec() failed.');
				else
				{
					foreach ($output3 as $line3) {
						echo $line3;
					}
				}
				break;

		}
	}
?>
