<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/users.db.php');
require_once(__DIR__ . '/../db/connection.db.php');

session();

$db = get_database_connection();
$username = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST["selected"]);
$new_admin = !is_admin($db, $username);
update_admin_status($db, $username, $new_admin);
header("Location: ../src/admin_dashboard.php");
