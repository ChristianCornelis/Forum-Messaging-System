<?php
	//function to print out a post by calling on the viewing program
	function printPost($postOffset, $output, $status, $username, $stream, $markAll)
	{
		if ($status)
			echo('Exec() failed');
		else
		{
			$toDecrement = 0;
			//echoing HTML to screen
			foreach($output as $line)
			{
				//checking if all user's subscribed streams should be outputted
				if (strstr($line, "Post:") != NULL)
				{
					$cmd2 = '';
					echo $line;
					if ($markAll == 0)
					{
						//outputting the appropriate post
						$cmd2 = './view.py  ' .escapeshellarg($stream) . " " .escapeshellarg($username) . ' ' . $postOffset;
					}
					else
					{
						//marking all as read
						$cmd2 = './view.py ' .escapeshellarg($stream) . ' ' . escapeshellarg($username) . ' 3141592654';
						$postOffset = 0;
					}
					exec($cmd2, $output2, $status2);

					if ($status2)
						echo('Exec() failed');
					else
					{
						foreach($output2 as $line2)
						{
							if (strstr($line2, "*AT END*") != NULL)
							{
								$postOffset = 0;
								echo("OFFSET RESET<BR>");
							}
							else if (strstr($line2, "*AT BEGINNING*") != NULL)
							{
								$postOffset = $postOffset + 1;
								$toDecrement = 1;
							}
							else
								echo $line2;
						}
					}
					echo "<br><br>";
					$toReturn = $postOffset;
				}
				//else check if a hidden field should be filled
				else if (strstr($line, "ENTER USERNAME HERE") != NULL)
				{
					echo (str_replace("ENTER USERNAME HERE", $username, $line));
				}
				//else check if a hidden field should be filled
				else if (strstr($line, "ENTER STREAM HERE") != NULL)
				{
					echo (str_replace("ENTER STREAM HERE", $stream, $line));
				}
				else if (strstr($line, "ENTER OFFSET HERE") != NULL)
				{
					if ($toDecrement == 0)
						echo (str_replace("ENTER OFFSET HERE", $postOffset, $line));
					else
					{
						$postOffset = $postOffset -1;
						echo (str_replace("ENTER OFFSET HERE", $postOffset, $line));
						$postOffset = $postOffset + 1;
					}
				}
				//else output the line
				else
				{
					echo $line;
				}
			}
		}

		return $postOffset;
	}
	//grabbing username
	$username = $_POST['username'];
	$stream = $_POST['streamInput'];
	$offset = $_POST['offset'];
	$markAll = 0;
	$returnedOffset = 0;
	//outputting the current user and stream to inform the user
	echo ("Currently logged in as: " . $username);
	echo("<BR> Currently viewing the " . $stream . " stream");
	echo("<BR> Offset is " . $offset);

	//generating HTML code for webpage
	$cmd = './converter config/view.wpml';
	exec($cmd, $output, $status);
	//if exec unsuccessful


	if (isset($_POST['Next_post'])) //== "Next post")
	{
		echo ("IN DAT SHIT");
		$offset = $offset+1;
		echo ("OFFSET IS " . $_POST['offset']);
		$returnedOffset = printPost($offset, $output, $status, $username, $stream, $markAll);

		if ($returnedOffset == 0)
			$offset = 0;
	}

	else if (isset($_POST['Previous_post']))// == "Previous post")
	{
		$offset = $offset - 1;
		$returnedOffset = printPost($offset, $output, $status, $username, $stream, $markAll);
		$offset = $returnedOffset;
	}
	else if (isset($_POST['Check_for_new_posts']))
	{
		$offset = 0;
		$returnedOffset = printPost($offset, $output, $status, $username, $stream, $markAll);
		$offset = $returnedOffset;
	}
	else if (isset($_POST['Mark_all_as_read']))
	{
		$markAll = 1;
		$returnedOffset = printPost($offset, $output, $status, $username, $stream, $markAll);
		$markAll = 0;
		$returnedOffset = printPost(0, $output, $status, $username, $stream, $markAll);
		$offset = $returnedOffset;
	}
	else {
		$returnedOffset = printPost(0, $output, $status, $username, $stream, $markAll);
		$offset = $returnedOffset;
	}

 ?>
