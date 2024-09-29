<?php

declare(strict_types=1);
require_once(__DIR__ . "/../db/items.db.php");

function add_purchase(PDO $dbh, int $item_id, string $buyer_username, string $address, string $postalCode)
{
    $buyer_id = get_user_id($dbh, $buyer_username);
    $stmt = $dbh->prepare("INSERT INTO Purchase(item, buyer, address, postalCode) VALUES (?, ?, ?, ?)");
    $stmt->execute(array($item_id, $buyer_id, $address, $postalCode));
}

function get_purchases(PDO $dbh, string $username): array
{
    $stmt = $dbh->prepare("SELECT * FROM Purchase WHERE buyer = (SELECT id FROM User WHERE username = ?)");
    $stmt->execute(array($username));
    return $stmt->fetchAll();
}

function is_sold(PDO $dbh, int $item_id): bool
{
    $stmt = $dbh->prepare("SELECT isSold FROM Item WHERE id = ?");
    $stmt->execute(array($item_id));
    return $stmt->fetch()['isSold'] !== false;
}

function set_sold(PDO $dbh, int $item_id, bool $value): void {
    $stmt = $dbh->prepare("UPDATE Item SET isSold = ? WHERE id = ?");
    $stmt->execute(array((int) $value, $item_id));
}

function get_purchase_by_item(PDO $db, int $item_id): array {
    $stmt = $db->prepare("SELECT * FROM Purchase WHERE item = ?");
    $stmt->execute(array($item_id));
    return $stmt->fetch();
}

