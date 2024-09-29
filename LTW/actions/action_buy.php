<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/items.db.php');
require_once(__DIR__ . '/' . '../db/purchases.db.php');
session();

$dbh = get_database_connection();
$user = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']);
$cart = get_items_in_cart($dbh, $user);
$address = preg_replace ("/[<>]/", '', $_POST['address']);
$zip = preg_replace ("/[<>]/", '', $_POST['zip_code']);
foreach ($cart as $item) {
        add_purchase($dbh, $item['id'], $user, $address, $zip);
        set_sold($dbh, $item['id'], true);
        foreach (get_all_users($dbh) as $target) {
                remove_from_cart($dbh, $item['id'], $target['id']);
        }
}

$_SESSION['error'] = "Purchase successful!";
header("Location: ../src/cart.php");
