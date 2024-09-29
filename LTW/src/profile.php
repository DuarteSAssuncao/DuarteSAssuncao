<?php

declare(strict_types=1);

require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/users.db.php');

session();
redirect_if_not_logged_in();

$username = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']);
$fullname = get_fullname(get_database_connection(), $username);
$email = get_email(get_database_connection(), $username);

draw_header($username . "'s Profile");
?>

<article>
    <form action="../actions/action_edit_profile.php" method="post">
        <section class="parameters">
            <label for="username">Username:</label>
            <input type="text" name="username" id="username" value="<?= $username ?>" required>
            <label for="fullname" name="fullname">Full Name:</label>
            <input type="text" name="fullname" id="fullname" value="<?= $fullname ?>" required>
            <label for="email">Email:</label>
            <input type="email" name="email" id="email" value="<?= $email ?>" required>
            <label for="new_password">New Password:</label>
            <input type="password" name="new_password" id="new_password">
        </section>


        <section class="authentication">
            <label for="password">Old Password:</label>
            <input type="password" name="old_password" id="old_password" required>
        </section>
        <input type="submit" value="Edit Profile">
    </form>
</article>

<article>
    <input type="button" value="Log Out" onclick="location.href='../actions/action_logout.php';">
</article>

<?php
draw_footer();
