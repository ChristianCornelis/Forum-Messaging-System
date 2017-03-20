<?php

    $cmd = './converter config/login.wpml';
    exec($cmd, $output, $status);

    if ($status)
        echo('Exec() failed');
    else
    {
        foreach($output as $line)
            echo $line;
    }

?>
