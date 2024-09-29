<?php

declare(strict_types=1);

require_once(__DIR__ . '/../db/connection.db.php');

function get_all_conditions(PDO $dbh): array
{
    $stmt = $dbh->prepare("SELECT * FROM Condition ORDER BY condition ASC");
    $stmt->execute();
    return $stmt->fetchAll();
}

function get_all_sizes(PDO $dbh): array
{
    $stmt = $dbh->prepare("SELECT * FROM Size ORDER BY size ASC");
    $stmt->execute();
    return $stmt->fetchAll();
}

function get_all_categories(PDO $dbh): array
{
    $stmt = $dbh->prepare("SELECT * FROM Category ORDER BY category ASC");
    $stmt->execute();
    $result = $stmt->fetchAll();
    return $result;
}

function add_category(PDO $db, string $catg): void
{
    $stmt = $db->prepare("INSERT INTO Category(category) VALUES (?);");
    $stmt->execute(array($catg));
}

function add_size(PDO $db, string $size): void
{
    $stmt = $db->prepare("INSERT INTO Size(size) VALUES (?);");
    $stmt->execute(array($size));
}

function add_condition(PDO $db, string $cond): void
{
    $stmt = $db->prepare("INSERT INTO Condition(condition) VALUES (?);");
    $stmt->execute(array($cond));
}

function remove_category(PDO $db, string $catg): void
{
    $stmt = $db->prepare("DELETE FROM Category WHERE category = ?;");
    $stmt->execute(array($catg));
}

function remove_size(PDO $db, string $size): void
{
    $stmt = $db->prepare("DELETE FROM Size WHERE size = ?;");
    $stmt->execute(array($size));
}

function remove_condition(PDO $db, string $cond): void
{
    $stmt = $db->prepare("DELETE FROM Condition WHERE condition = ?;");
    $stmt->execute(array($cond));
}
