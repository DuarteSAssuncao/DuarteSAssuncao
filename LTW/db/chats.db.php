<?php

declare(strict_types=1);

function get_chat_by_id(PDO $dbh, int $id): array
{
    $stmt = $dbh->prepare("SELECT * FROM Chat WHERE id = ?");
    $stmt->execute(array($id));
    $ret = $stmt->fetch();
    if(!$ret) return array();
    return $ret;
}

function get_user_chats(PDO $dbh, int $user_id): array
{
    $stmt = $dbh->prepare("SELECT * FROM Chat WHERE user1 = ? OR user2 = ?");
    $stmt->execute(array($user_id, $user_id));
    return $stmt->fetchAll();
}

function get_chat_between(PDO $dbh, int $user1_id, int $user2_id): array
{
    $stmt = $dbh->prepare("SELECT * FROM Chat WHERE (user1 = ? AND user2 = ?) OR (user1 = ? AND user2 = ?)");
    $stmt->execute(array($user1_id, $user2_id, $user2_id, $user1_id));
    $ret = $stmt->fetch();

    if ($ret !== false) return $ret; // If exists, return chat.
    // If not, create it:
    $stmt = $dbh->prepare("INSERT INTO Chat (user1, user2) VALUES (?, ?)");
    $stmt->execute(array($user1_id, $user2_id));
    // And return it:
    $stmt = $dbh->prepare("SELECT * FROM Chat WHERE user1 = ? AND user2 = ?");
    $stmt->execute(array($user1_id, $user2_id));

    return $stmt->fetch();
}

function get_chat_messages(PDO $dbh, int $chat_id): array
{
    $stmt = $dbh->prepare("SELECT * FROM Msg WHERE chat = ? ORDER BY dt ASC");
    $stmt->execute(array($chat_id));
    return $stmt->fetchAll();
}

function send_message(PDO $dbh, int $chat_id, int $sender_id, string $content): void
{
    $stmt = $dbh->prepare("INSERT INTO Msg (chat, sender, content, dt) VALUES (?, ?, ?, DATETIME('now'))");
    $stmt->execute(array($chat_id, $sender_id, $content));
}
