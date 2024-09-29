<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/items.db.php');

session();

$item = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_GET['item_id']);
if ($item === null || $item === '') $photo_path = "";
else {
    $db = get_database_connection();
    $photo_path = get_photo_path($db, (int) $item);
}

echo json_encode($photo_path);
