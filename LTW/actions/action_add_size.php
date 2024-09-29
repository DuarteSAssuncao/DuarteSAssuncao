<?php

declare(strict_types=1);

require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/entity.db.php');
require_once(__DIR__ . '/../db/connection.db.php');

session();

$db = get_database_connection();

$size = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['size_name']);
add_size($db, $size);
header("Location: ../src/entities.php");
