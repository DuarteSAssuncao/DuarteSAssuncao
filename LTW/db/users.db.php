<?php

declare(strict_types=1);

function register_user(PDO $dbh, string $fullname, string $email, string $username, string $password): void
{
    $stmt = $dbh->prepare('INSERT INTO User (fullName, username, pw, eMail) VALUES (?, ?, ?, ?)');
    $stmt->execute(array($fullname, $username, password_hash($password, PASSWORD_DEFAULT), $email));
}

function update_user(PDO $dbh, string $old_username, string $new_username, string $fullname, string $email, string $password): void
{
    $stmt = $dbh->prepare('UPDATE User SET fullName = ?, username = ?, pw = ?, eMail = ? WHERE username = ?');
    $stmt->execute(array($fullname, $new_username, password_hash($password, PASSWORD_DEFAULT), $email, $old_username));
}

function verify_user(PDO $dbh, string $username, string $password): bool
{
    $stmt = $dbh->prepare('SELECT pw FROM User WHERE username = ?');
    $stmt->execute(array($username));
    $hash = $stmt->fetch()['pw'];
    return password_verify($password, $hash);
}

function is_admin(PDO $dbh, string $username): bool
{
    $is_it = $dbh->prepare('SELECT isAdmin FROM User WHERE username = ?');
    $is_it->execute(array($username));
    $value = $is_it->fetch()['isAdmin'];
    return $value === 1;
}

function does_email_already_exist(PDO $dbh, string $email): bool
{
    $stmt = $dbh->prepare('SELECT * FROM User WHERE email = ?');
    $stmt->execute(array($email));

    return $stmt->fetch() !== false;
}

function does_username_already_exist(PDO $dbh, string $username): bool
{
    $stmt = $dbh->prepare('SELECT * FROM User WHERE username = ?');
    $stmt->execute(array($username));

    return $stmt->fetch() !== false;
}

function get_user_id(PDO $dbh, string $username): int
{
    $stmt = $dbh->prepare('SELECT id FROM User WHERE username = ?');
    $stmt->execute(array($username));
    return (int)$stmt->fetch()['id'];
}

function get_fullname(PDO $dbh, string $username): string
{
    $stmt = $dbh->prepare('SELECT fullName FROM User WHERE username = ?');
    $stmt->execute(array($username));

    return $stmt->fetch()['fullName'];
}

function get_email(PDO $dbh, string $username): string
{
    $stmt = $dbh->prepare('SELECT eMail FROM User WHERE username = ?');
    $stmt->execute(array($username));

    return $stmt->fetch()['eMail'];
}

function get_all_users(PDO $db): array
{
    $it = $db->prepare("SELECT * FROM User ORDER BY isAdmin ASC, fullName ASC");
    $it->execute();
    return $it->fetchAll();
}

function get_admin_count(PDO $db): int
{
    $it = $db->prepare("SELECT count(*) FROM User where isAdmin = 1");
    $it->execute();
    return $it->fetch()[0];
}

function update_admin_status(PDO $db, string $username, bool $new_admin): void
{
    $it = $db->prepare("UPDATE User SET isAdmin = ? WHERE username = ?");
    $it->execute(array($new_admin, $username));
}

function get_user_by_username(PDO $dbh, string $username): array
{
    $stmt = $dbh->prepare('SELECT * FROM User WHERE username = ?');
    $stmt->execute(array($username));
    return $stmt->fetch();
}

function get_user_by_id(PDO $dbh, int $user_id): array
{
    $stmt = $dbh->prepare('SELECT * FROM User WHERE id = ?');
    $stmt->execute(array($user_id));
    return $stmt->fetch();
}
