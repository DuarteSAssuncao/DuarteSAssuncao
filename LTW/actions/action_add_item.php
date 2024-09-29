<?php

declare(strict_types=1);

require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/items.db.php');
require_once(__DIR__ . '/../db/images.db.php');
require_once(__DIR__ . '/../db/users.db.php');

session();
$dbh = get_database_connection();

$seller = get_user_id($dbh, preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']));

$itemId = add_item($dbh, preg_replace ("/[<>]/", '', $_POST['brand']), preg_replace ("/[<>]/", '', $_POST['model']), preg_replace ("/[<>]/", '', $_POST['descript']), (float)$_POST['price'], preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['condition']), preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['size']), preg_replace ("/[^a-zA-Z0-9\s]/", '', $_POST['category']), $seller);

add_image($dbh, $itemId, $_FILES['image']);

header("Location: ../src/item.php?id=$itemId");
