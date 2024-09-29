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
$chat_id = (int) $_GET['id'];

if (!$chat_id) {
    draw_header('Chat Not found!');
    draw_footer();
} else {
    $chat = get_chat_by_id($dbh, $chat_id);

    if (empty($chat)) {
        draw_header('Chat Not found!');
        draw_footer();
    } else {
        $user_me = get_user_by_username($dbh, preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']));
        $user_other = get_user_by_id($dbh, $chat['user1'] === $user_me['id'] ? $chat['user2'] : $chat['user1']);
        $messages = get_chat_messages($dbh, $chat_id);
        $n_messages = count($messages);
        draw_header("Chat with " . $user_other['fullName'], content: "chat", css: array("chat.css"));
        
        ?><section class="messages"><?php
        for($m = 0; $m < $n_messages; $m++) {
            $message = $messages[$m];
            ?>
                <article <?=$m === $n_messages - 1 ? "id=\"last\"" : ""?> class="<?=$message['sender'] == $user_me['id'] ? "mine" : "theirs"?>">
                    <p><?=$message['content']?></p>
                    <p class="date"><?=$message['dt']?></p>
                </article>
            <?php
        }
        ?></section><?php
        ?>
            <section>
                <form action="../actions/action_send_message.php" method="post">
                    <input type="hidden" name="chat_id" value="<?=$chat_id?>">
                    <input type="hidden" name="sender_id" value="<?=$user_me['id']?>">
                    <input type="text" name="content" placeholder="Type your message here...">
                    <input type="submit" value="Send">
                </form>
            </section>
        <?php

        draw_footer();
    }
}
