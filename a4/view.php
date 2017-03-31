<?php
	//function to print out a post by calling on the viewing program
	function printPost($postOffset, $output, $status, $username, $stream, $markAll, $orderBy)
	{
		if ($status)
			echo('Exec() failed');
		else
		{
			$toDecrement = 0;
			$toIncrement = 0;
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
					/*if marking all as read with any stream but all*/
					else if (strcmp($stream, "all") != 0)
					{
						//marking all as read
						$cmd2 = './view.py ' .escapeshellarg($stream) . ' ' . escapeshellarg($username) . ' 3141592654';
						$postOffset = 0;
					}
					//if marking all as read with all streams
					else if (strcmp($stream, "all") == 0 && $markAll == 1)
					{
						$cmd2 = './view.py ' .escapeshellarg($stream) . ' ' . escapeshellarg($username) . ' 98765432109';
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
								$postOffset = $postOffset-1;
								echo (str_replace("*AT END*", "", $line2));
							}
							else if (strstr($line2, "*AT BEGINNING*") != NULL)
							{
								$postOffset = $postOffset + 1;
								echo (str_replace("*AT BEGINNING*", "", $line2));
							}
							else if (strstr($line2, "*AT ALL BEGNINNING*") != NULL)
							{
								$postOffset = 0;
								echo (str_replace("*AT ALL BEGNINNING*", "", $line2));
							}
							else if (strstr($line2, "*AT ALL END*") != NULL)
							{
								$postOffset = $postOffset-1;
								//echo $line2;
								echo (str_replace("*AT ALL END*", "", $line2));
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
				else if (strstr($line, "ENTER ORDER HERE") != NULL)
				{
					echo (str_replace("ENTER ORDER HERE",  $orderBy, $line));
				}
				//else check if a hidden field should be filled
				else if (strstr($line, "ENTER STREAM HERE") != NULL)
				{
					echo (str_replace("ENTER STREAM HERE", $stream, $line));
				}
				else if (strstr($line, "ENTER OFFSET HERE") != NULL)
				{
					echo (str_replace("ENTER OFFSET HERE", $postOffset, $line));
					if ($toDecrement == 0 && $toIncrement == 0)
						echo (str_replace("ENTER OFFSET HERE", $postOffset, $line));
					else if ($toIncrement == 0 && $toDecrement == 1)
					{
						//$postOffset = $postOffset -1;
						echo (str_replace("ENTER OFFSET HERE", $postOffset, $line));
						//$postOffset = $postOffset + 1;
					}
					else if ($toIncrement == 1 && $toDecrement == 0)
					{
						$postOffset = $postOffset +1;
						echo (str_replace("ENTER OFFSET HERE", $postOffset, $line));
						$postOffset = $postOffset - 1;
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
	$orderBy = $_POST['order'];
	echo "Currently ordering by " . $orderBy;
	//outputting the current user and stream to inform the user
	echo ("Currently logged in as: " . $username);
	echo("<BR> Currently viewing the " . $stream . " stream");

	//generating HTML code for webpage
	$cmd = './converter view.wpml';
	exec($cmd, $output, $status);
	//if exec unsuccessful


	if (isset($_POST['Next_post'])) //== "Next post")
	{
		$offset = $offset+1;
		$returnedOffset = printPost($offset, $output, $status, $username, $stream, $markAll, $orderBy);

		if ($returnedOffset == 0)
			$offset = 0;
	}

	else if (isset($_POST['Previous_post']))// == "Previous post")
	{
		$offset = $offset - 1;
		$returnedOffset = printPost($offset, $output, $status, $username, $stream, $markAll, $orderBy);
		$offset = $returnedOffset;
	}
	else if (isset($_POST['Check_for_new_posts']))
	{
		$offset = 0;
		$returnedOffset = printPost($offset, $output, $status, $username, $stream, $markAll, $orderBy);
		$offset = $returnedOffset;
	}
	else if (isset($_POST['Mark_all_as_read']))
	{
		$markAll = 1;
		$returnedOffset = printPost($offset, $output, $status, $username, $stream, $markAll, $orderBy);
		$offset = $returnedOffset;
	}
	else if (isset($_POST['Order_toggle']))
	{
		if (strcmp($orderBy, "name") == 0)
			$orderBy = "date";
		else
			$orderBy = "name";

		$returnedOffset = printPost($offset, $output, $status, $username, $stream, $markAll, $orderBy);
	}
	else {
		$returnedOffset = printPost(0, $output, $status, $username, $stream, $markAll, $orderBy);
		$offset = $returnedOffset;
	}

 ?>
