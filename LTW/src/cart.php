<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../templates/item.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/items.db.php');

session();
redirect_if_not_logged_in();
draw_header('Shopping Cart');

$dbh = get_database_connection();
$items = get_items_in_cart($dbh, preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']));

foreach ($items as $item) {
    // draw_item($item, "../photos/" . get_item_images($dbh, $item['id'])[0]['photo']);
    $photo = "../photos/" . get_item_images($dbh, $item['id'])[0]['photo'];
    ?>
    <a class="card" href="../src/item.php?id=<?= $item['id'] ?>">
        <article onclick="this.parentNode.submit()">
            <img src="<?= $photo ?>" alt="<?= $item['descript'] ?>">
            <h3><?= $item['brand'] . ' - ' . $item['model'] ?></h3>
            <p><?= $item['price'] ?></p>
        </article>

        <form class="delete" action="../actions/action_remove_from_cart.php?item=<?= $item['id'] ?>" method="post">
            <input id="remove_from_cart_button" type="submit" name="delete" value="Delete">
        </form>
    </a>
    <?php
}
if (!empty($items)) {
?>
    <form method="post" action="buy.php">
        <input type="submit" value="Checkout">
    </form>        
<?php
} else {
    ?>
    <h2>Your cart is empty!</h2>
    <?php
}

draw_footer();
