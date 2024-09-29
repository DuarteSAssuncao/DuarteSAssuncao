<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/chats.db.php');
require_once(__DIR__ . '/../db/users.db.php');

session();
redirect_if_not_logged_in();

$dbh = get_database_connection();
$user = get_user_by_username($dbh, preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']));
$chats = get_user_chats($dbh, $user['id']);

if (!$chats) {
    draw_header('No Chats Yet.');
    draw_footer();
} else {
    draw_header("Chats", content: "talk", css: array("chat.css"));

    foreach ($chats as $chat){
        $user_other = get_user_by_id($dbh, $chat['user1'] === $user['id'] ? $chat['user2'] : $chat['user1']);
        $messages = get_chat_messages($dbh, $chat['id']);
        
        ?>
            <a class="conversation" href="chat.php?id=<?=$chat['id']?>#last">
                <h3><?=$user_other['fullName']?> (<?=$user_other['username']?>)</h3>
                <?php
                    if ($messages) {
                        $last = end($messages);
                        ?>
                            <p><strong><?=$last['sender'] === $user['id'] ? "You: " : $user_other['username'] . ": "?></strong> <?=$last['content']?></p>
                        <?php
                    }
                ?>
            </a>
        <?php
    }

    draw_footer();
}
