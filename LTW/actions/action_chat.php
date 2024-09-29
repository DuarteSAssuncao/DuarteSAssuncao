<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/chats.db.php');
session();
$dbh = get_database_connection();

$user1_id = (int) $_POST['user1'];
$user2_id = (int) $_POST['user2'];

$chat = get_chat_between($dbh, $user1_id, $user2_id);

header("Location: ../src/chat.php?id=" . $chat['id'] . "#last");
