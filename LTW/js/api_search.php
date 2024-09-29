<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/items.db.php');

session();

$search = "%" . preg_replace ("/[^a-zA-Z0-9\s%]/", '', $_GET['search']) . "%";
$condition = preg_replace ("/[^a-zA-Z0-9\s%]/", '', $_GET['condition']);
$category = preg_replace ("/[^a-zA-Z0-9\s%]/", '', $_GET['category']);
$size = preg_replace ("/[^a-zA-Z0-9\s%]/", '', $_GET['size']);

$db = get_database_connection();
$items = get_items_from_others($db, preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']), $search, $condition, $category, $size);

echo json_encode($items);
