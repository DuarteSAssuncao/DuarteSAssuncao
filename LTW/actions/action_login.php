<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/users.db.php');
session();

if (verify_user(get_database_connection(), preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['username']), preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['password']))) {
    $_SESSION['username'] = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['username']);
    header("Location: ../src/index.php");
} else {
    $_SESSION['error'] = "Login failed. Check your username and password.";
    redirect_if_not_logged_in();
}
