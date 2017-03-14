<?php
	$cmd = './converter config/post.wpml';
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
		$fptr = fopen("usernameData", "r");
		$username = fgets($fptr);
		fclose($fptr);

		if ($_POST["streamInput"] == " ")
			echo "Error: Stream name cannot be a space.";
		else
			exec("./post " . escapeshellarg($_POST["streamInput"]) ." " . escapeshellarg($username). " " . escapeshellarg($_POST["textInput"]), $output2, $status2);

		if ($status2)
			echo('Exec() failed.');
		else
		{
			foreach ($output2 as $line2) {
				echo $line2;
			}
		}

	}

?>
