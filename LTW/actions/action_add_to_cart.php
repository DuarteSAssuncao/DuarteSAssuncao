<?php

declare(strict_types=1);

require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/users.db.php');
require_once(__DIR__ . '/../db/items.db.php');

session();

$dbh = get_database_connection();

$user_id = (int)(get_user_by_username($dbh, preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']))['id']);
$item_id = (int)($_GET['item']);

add_to_cart($dbh, $item_id, $user_id);

header("Location: ../src/item.php?id=" . $item_id . "#add_to_cart_button");
