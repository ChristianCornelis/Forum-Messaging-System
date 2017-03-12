<?php 
    exec("./converter login.wpml");
    echo (file_get_contents("login.html"));
?>
