<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/users.db.php');

session();
redirect_if_not_admin();
draw_header('Admin Dashboard', "admin", ['admin.css']);
?>
<h3><a href="../src/entities.php">Edit Entities</a></h3>
<h2>User Control Panel</h2>
<article class="user_display">
    <table>
        <tr>
            <td>
                Full Name
            </td>
            <td>
                User Name
            </td>
            <td>
                EMail
            </td>
            <td>
                Admin
            </td>
            <td>

            </td>
        </tr>
        <?php
        $users = get_all_users(get_database_connection());
        $admin = get_admin_count(get_database_connection());
        foreach ($users as $user) {
            $username   = $user['username'];
            $fullname   = $user['fullName'];
            $email      = $user['eMail'];
            $is_admin   = $user['isAdmin'];
            $cls = "";
            if ($admin <= 1 and $is_admin) {
                $cls = "not_enough_admins";
            } else {
                if ($is_admin) {
                    $cls = "demote";
                } else {
                    $cls = "promote";
                }
            }
        ?>
            <tr>
                <td><?= $fullname ?></td>
                <td><?= $username ?></td>
                <td><?= $email ?></td>
                <td><?= $is_admin ? "Yes" : "No" ?></td>
                <td>
                    <form method="post" action="../actions/action_toggle_admin.php">
                        <input type="hidden" value="<?= $username ?>" name="selected">
                        <input type="submit" value="<?= $is_admin ? "Demote" : "Promote" ?>" name="submit" class="<?= $cls ?>">
                    </form>
                </td>
            </tr>
        <?php
        }
        ?>
    </table>
</article>
<?php
draw_footer();
