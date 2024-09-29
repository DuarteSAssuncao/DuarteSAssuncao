<?php

declare(strict_types=1);

function add_item(PDO $dbh, string $brand, string $model, string $descript, float $price, string $condition, string $size, string $category, int $seller): int{
    $stmt = $dbh->prepare("INSERT INTO ITEM(brand, model, descript, price, isSold, condition, size, category, seller) VALUES (?, ?, ?, ?, false, ?, ?, ?, ?)");
    $stmt->execute(array($brand, $model, $descript, $price, $condition, $size, $category, $seller));

    $stmt = $dbh->prepare("SELECT id FROM ITEM WHERE brand = ? AND model = ? AND descript = ? AND price = ? AND isSold = ? AND condition = ? AND size = ? AND category = ? AND seller = ?");
    $stmt->execute(array($brand, $model, $descript, $price, 0, $condition, $size, $category, $seller));
    $ret = $stmt->fetch();
    return $ret['id'];
}

function remove_item(PDO $dbh, int $id): void{
    $stmt = $dbh->prepare("SELECT photo FROM Photo WHERE item = ?");
    $stmt->execute(array($id));
    $photos = $stmt->fetchAll();

    foreach ($photos as $photo) unlink(__DIR__ . "/../photos/" . $photo['photo']); // delete all the photos

    $stmt = $dbh->prepare("DELETE FROM Photo WHERE item = ?");
    $stmt->execute(array($id));

    $stmt = $dbh->prepare("DELETE FROM ShoppingCart WHERE item = ?");
    $stmt->execute(array($id));

    $stmt = $dbh->prepare("DELETE FROM Purchase WHERE item = ?");
    $stmt->execute(array($id));

    $stmt = $dbh->prepare("DELETE FROM Item WHERE id = ?");
    $stmt->execute(array($id));
}

function get_items_in_cart(PDO $dbh, string $username): array {
    $stmt = $dbh->prepare("
        SELECT I.id as id, I.brand as brand, I.model as model, I.descript as descript, I.price as price, I.isSold as isSold, I.condition as condition, I.size as size, I.category as category, I.seller as seller
        FROM ShoppingCart as SC, User as U, Item as I
        WHERE SC.user = U.id AND SC.item = I.id AND U.username = ?
    ");
    $stmt->execute(array($username));
    return $stmt->fetchAll();
}

function is_in_cart(PDO $dbh, int $item_id, int $user_id): bool {
    $stmt = $dbh->prepare("
        SELECT *
        FROM ShoppingCart as SC, User as U
        WHERE SC.user = U.id AND SC.item = ? AND U.id = ?
    ");
    $stmt->execute(array($item_id, $user_id));
    return $stmt->fetch() !== false;
}

function add_to_cart(PDO $dbh, int $item_id, int $user_id): void {
    $stmt = $dbh->prepare("INSERT INTO ShoppingCart (item, user) VALUES (?, ?)");
    $stmt->execute(array($item_id, $user_id));
}

function remove_from_cart(PDO $dbh, int $item_id, int $user_id): void {
    $stmt = $dbh->prepare("DELETE FROM ShoppingCart WHERE item = ? AND user = ?");
    $stmt->execute(array($item_id, $user_id));
}

function get_item_images(PDO $dbh, int $id): array {
    $stmt = $dbh->prepare("SELECT * FROM Photo WHERE item = ?");
    $stmt->execute(array($id));
    return $stmt->fetchAll();
}

function get_items(PDO $dbh): array {
    $stmt = $dbh->prepare("SELECT * FROM Item");
    $stmt->execute();
    return $stmt->fetchAll();
}

function get_item(PDO $dbh, int $id): array {
    $stmt = $dbh->prepare("SELECT * FROM Item WHERE id = ?");
    $stmt->execute(array($id));
    $ret = $stmt->fetch();
    if(!$ret) return array();
    return $ret;
}

function is_owner(PDO $dbh, int $item_id, int $user_id): bool {
    $stmt = $dbh->prepare("SELECT seller FROM Item WHERE id = ?");
    $stmt->execute(array($item_id));
    $sellerId =  (int)($stmt->fetch()['seller']);
    return $sellerId === $user_id;
}

function edit_price(PDO $dbh, int $item_id, float $price): void {
    $stmt = $dbh->prepare("UPDATE Item SET price = ? WHERE id = ?");
    $stmt->execute(array($price, $item_id));
}

function get_items_from_others(PDO $dbh, string $username, string $search, string $condition, string $category, string $size): array {
    $stmt = $dbh->prepare(
        "SELECT * FROM Item 
        WHERE seller != (SELECT id FROM User WHERE username = ?)
        AND (brand LIKE ? OR model LIKE ? OR descript LIKE ?)
        AND (condition LIKE ?)
        AND (category LIKE ?)
        AND (size LIKE ?)
        AND isSold = 0"
    );
    $stmt->execute(array($username, $search, $search, $search, $condition, $category, $size));
    return $stmt->fetchAll();
}

function get_photo_path(PDO $dbh, int $id): string{
    $stmt = $dbh->prepare("SELECT photo FROM Photo WHERE item = ?");
    $stmt->execute(array($id));
    return "../photos/" . $stmt->fetch()['photo'];
}

function get_my_items(PDO $db, string $username): array {
    $stmt = $db->prepare("SELECT * FROM Item WHERE seller = (SELECT id FROM User WHERE username = ?)");
    $stmt->execute(array($username));
    return $stmt->fetchAll();
}