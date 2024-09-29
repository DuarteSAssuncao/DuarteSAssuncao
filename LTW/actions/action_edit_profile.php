<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/users.db.php');
session();

$db = get_database_connection();
$old_username = $_SESSION['username'];
$new_username = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['username']);
$fullname = preg_replace ("/[<>]/", '', $_POST['fullname']);
$old_email = get_email($db, $old_username);
$new_email = preg_replace ("/[^a-zA-Z0-9\s@.]/", '', $_POST['email']);
$old_password = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['old_password']);
$new_password = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['new_password']);

// If the user does not provide a new password, the password should remain untouched
if (is_null($new_password) || empty($new_password)) {
    $new_password = $old_password;
}

// Checking correct password and if the new username or email already exists or not
if (!verify_user($db, $old_username, $old_password)) {
    $_SESSION['error'] = "Wrong credentials. Check your old password.";
} else if ($old_username !== $new_username && does_username_already_exist($db, $new_username)) {
    $_SESSION['error'] = "Username already exists. Please choose another one or keep the same.";
} else if ($old_email !== $new_email && does_email_already_exist($db, $new_email)) {
    $_SESSION['error'] = "Email already exists. Please choose another one or keep the same.";
} else {
    update_user($db, $old_username, $new_username, $fullname, $new_email, $new_password);
    $_SESSION['username'] =  preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['username']);
    $_SESSION['error'] = "Profile updated successfully.";
}

header("Location: ../src/profile.php");
