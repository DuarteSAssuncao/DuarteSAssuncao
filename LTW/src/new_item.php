<?php

declare(strict_types=1);

require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/entity.db.php');

session();
redirect_if_not_logged_in();
draw_header('Sell a New Item');

$dbh = get_database_connection();
$conds = get_all_conditions($dbh);
$sizes = get_all_sizes($dbh);
$cats = get_all_categories($dbh);
?>

<form action="../actions/action_add_item.php" method="post" enctype="multipart/form-data">
    <label for="brand">Brand:</label>
    <input type="text" id="brand" name="brand" required>

    <label for="model">Model:</label>
    <input type="text" id="model" name="model">

    <label for="descript">Description:</label>
    <input type="text" id="descript" name="descript">

    <label for="price">Price:</label>
    <input type="number" id="price" step="0.01" name="price" required>

    <label for="condition">Condition:</label>
    <select id="condition" name="condition" required>
        <?php foreach ($conds as $cond) { ?>
            <option value="<?= $cond['condition'] ?>"><?= $cond['condition'] ?></option>
        <?php } ?>
    </select>

    <label for="size">Size:</label>
    <select id="size" name="size" required>
        <?php foreach ($sizes as $size) { ?>
            <option value="<?= $size['size'] ?>"><?= $size['size'] ?></option>
        <?php } ?>
    </select>

    <label for="category">Category:</label>
    <select id="category" name="category" required>
        <?php foreach ($cats as $cat) { ?>
            <option value="<?= $cat['category'] ?>"><?= $cat['category'] ?></option>
        <?php } ?>
    </select>

    <label for="upload">Upload Images:</label>
    <input type="file" id="upload" name="image" accept="image/*">

    <input type="submit" value="Add Item">
</form>
<?php
draw_footer();
