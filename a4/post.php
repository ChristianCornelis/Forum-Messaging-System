<?php
	$username = $_POST["username"];
	echo("Currently logged in as: " . $username);
	$cmd = './converter post.wpml';
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

	if (isset($_POST["submit"]))
	{

		if ($_POST["streamInput"] == " ")
			echo "Error: Stream name cannot be a space.";
		else if ($_POST["streamInput"] == "")
			echo "Error: Stream name cannot be left blank";
		else if (strstr($_POST["streamInput"], "'") != NULL)
			echo "Error: Stream name cannot contain an apostrophe.";
		else if ($_POST["textInput"] == "")
			echo "Error: Text cannot be blank.";
		else
		{
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

	}

?>
