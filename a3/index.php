<?php
	/*if (isset($_POST["submit"]))
	{
		echo("IN THIS");

		/*if (file_exists("messages/"))
			header("location: menu.php");
		else
			header("location: addAuthor.php");*/
	

    $cmd = './converter config/login.wpml';
    exec($cmd, $output, $status);

    if ($status)
        echo('Exec() failed');
    else
    {
        foreach($output as $line)
            echo $line;
    }

	/*$username = $_POST["usernameInput"];
	echo ("<form=\"test\" method =\"POST\" action = \"index.php\">");
	echo("\t<input type=\"hidden\" name=\"username\" value=\"" . $username . "\">");
	echo("</form>");*/
	//echo("</body>\n</html>\n");

?>
