<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/users.db.php');
session();

$db = get_database_connection();
$fullname = preg_replace ("/[<>]/", '', $_POST['fullname']);
$username = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['username']);
$pw = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['password']);
$email = preg_replace ("/[^a-zA-Z0-9\s@.]/", '', $_POST['email']);

if (does_email_already_exist($db, $email)) {
    $_SESSION['error'] = "Email already exists.";
    header('Location: ../src/register.php');
} else if (does_username_already_exist($db, $username)) {
    $_SESSION['error'] = "Username already exists.";
    header('Location: ../src/register.php');
} else {
    register_user($db, $fullname, $email, $username, $pw);
    $_SESSION['username'] = $username;
    header('Location: ../src/index.php');
}
