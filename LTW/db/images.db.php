<?php

declare(strict_types=1);

require_once(__DIR__ . '/../db/connection.db.php');

function add_image(PDO $dbh, int $item, array $image): void
{
    if ($image['name'] === "") {
        $_SESSION['error'] = "No images were uploaded.";
        return;
    }

    $a = explode('.', $image['name']);
    $extension = strtolower(end($a));
    $fileName = uniqid('', true) . '.' . $extension;

    if ($image['error'] === 0) {
        move_uploaded_file($image['tmp_name'], __DIR__ . "/../photos/" . $fileName);

        $stmt = $dbh->prepare("INSERT INTO Photo(item, photo) VALUES(?, ?)");
        $stmt->execute(array($item, $fileName));
    } else {
        $_SESSION['error'] = "Error uploading image.";
    }
}
