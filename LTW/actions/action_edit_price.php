<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/items.db.php');
session();

$dbh = get_database_connection();

edit_price($dbh, (int)$_GET['item'], (float)$_POST['price']);

header("Location: ../src/item.php?id=" . $_GET['item']);
