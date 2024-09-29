<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/entity.db.php');

session();
redirect_if_not_admin();
draw_header('Edit Entities', "admin", ['admin.css']);

$db = get_database_connection();

?>
<label for="show_cond">
    <h3>Condition</h3>
</label>
<input type="checkbox" id="show_cond">
<ul class="entries_cond">
    <li class="new_entry">
        <form method="post" action="../actions/action_add_condition.php">
            <label for="cond_name">New Condition:</label>
            <input type="text" name="cond_name" id="cond_name" required>
            <input type="submit" value="Create" name="submit">
        </form>
    </li>
    <?php
    $conditions = get_all_conditions($db);
    foreach ($conditions as $cond) {
    ?>
        <li class="existing_entry">
            <form method="post" action="../actions/action_remove_condition.php">
                <p><?= $cond['condition'] ?></p>
                <input type="hidden" value="<?= $cond['condition'] ?>" name="selected">
                <input type="submit" value="🗑" name="submit">
            </form>
        </li>
    <?php
    }
    ?>
</ul>
<label for="show_size">
    <h3>Size</h3>
</label>
<input type="checkbox" id="show_size">
<ul class="entries_size">
    <li class="new_entry">
        <form method="post" action="../actions/action_add_size.php">
            <label for="size_name">New Size:</label>
            <input type="text" name="size_name" id="size_name" required>
            <input type="submit" value="Create" name="submit">
        </form>
    </li>
    <?php
    $sizes = get_all_sizes($db);
    foreach ($sizes as $size) {
    ?>
        <li class="existing_entry">
            <form method="post" action="../actions/action_remove_size.php">
                <p><?= $size['size'] ?></p>
                <input type="hidden" value="<?= $size['size'] ?>" name="selected">
                <input type="submit" value="🗑" name="submit">
            </form>
        </li>
    <?php
    }
    ?>
</ul>
<label for="show_catg">
    <h3>Category</h3>
</label>
<input type="checkbox" id="show_catg">
<ul class="entries_catg">
    <li class="new_entry">
        <form method="post" action="../actions/action_add_category.php">
            <label for="catg_name">New Category:</label>
            <input type="text" name="catg_name" id="catg_name" required>
            <input type="submit" value="Create" name="submit">
        </form>
    </li>
    <?php
    $categories = get_all_categories($db);
    foreach ($categories as $catg) {
    ?>
        <li class="existing_entry">
            <form method="post" action="../actions/action_remove_category.php">
                <p><?= $catg['category'] ?></p>
                <input type="hidden" value="<?= $catg['category'] ?>" name="selected">
                <input type="submit" value="🗑" name="submit">
            </form>
        </li>
    <?php
    }
    ?>
</ul>
<?php
draw_footer();
?>
