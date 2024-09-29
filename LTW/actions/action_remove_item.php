<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/items.db.php');

session();

$dbh = get_database_connection();

remove_item($dbh, (int)$_GET['item']);

header("Location: ../src/index.php");
