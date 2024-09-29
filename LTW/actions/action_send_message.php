<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/chats.db.php');

session();

$dbh = get_database_connection();

$chat_id = (int) $_POST['chat_id'];
$sender_id = (int) $_POST['sender_id'];
$content = preg_replace ("/[<>]/", '', $_POST['content']);

send_message($dbh, $chat_id, $sender_id, $content);

header("Location: ../src/chat.php?id=" . $chat_id  . "#last");
