<?php
		$cmd = './converter config/view.wpml';
		exec($cmd, $output, $status);

		if ($status)
				echo('Exec() failed');
		else
		{
				foreach($output as $line)
						echo $line;
		}

 ?>
