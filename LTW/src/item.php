<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/items.db.php');
require_once(__DIR__ . '/../db/users.db.php');
require_once(__DIR__ . '/../db/purchases.db.php');

session();
redirect_if_not_logged_in();

$dbh = get_database_connection();
$item_id = (int)$_GET['id'];
$item = get_item($dbh, (int)$item_id);
$user = get_user_by_username($dbh, preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']));

if (empty($item)) {
    draw_header('Not found!');
    draw_footer();
} else {
    draw_header($item['brand'] . ' - ' . $item['model'], "item", ["item.css"]);
    $photos = get_item_images($dbh, $item_id);
    if ($photos) {
        foreach ($photos as $photo) {
            ?>
            <img class="photo" src="<?= "../photos/" . $photo['photo'] ?>" alt="Item photo.">
            <?php
        }
    }

    ?>
    <article class="info">
        <p class="category">Category: <?= $item['category'] ?></p>
        <p class="condition">Condition: <?= $item['condition'] ?></p>
        <p class="size">Size: <?= $item['size'] ?></p>
        <?php

        if (is_owner($dbh, $item_id, $user['id']) || is_admin($dbh, $user['username'])) {
                if ($item['isSold']) {
                $purch = get_purchase_by_item($dbh, $item_id);
                $tgtuser = get_user_by_id($dbh, $purch['buyer']);
                ?>
                <p>Price: <?=$item['price']?>€</p>
                <p>Sold to: <?=$tgtuser['fullName']?></p>
                <p>Address: <?=$purch['address'] . ', ' . $purch['postalCode']?></p> 
                <form>
                    <input type='button' onclick="window.print();" value="Print Shipping Form">
                </form>    
                <?php
                } else {    
            ?>
            <form class="price" action="../actions/action_edit_price.php?item=<?= $item_id ?>"
                    method="post">
                <label for="price">Price:</label>
                <input type="number" step="0.01" name="price" value="<?= $item['price'] ?>">
                <input id="edit_price" type="submit" value="Change Price">
            </form>
                <?php
                }
                ?>
            <form class="delete" action="../actions/action_remove_item.php?item=<?= $item_id ?>"
                    method="post">
                <input id="delete_item" type="submit" value="Delete Item">
            </form>
            <?php
        } else {
            ?>
            <p class="price">Price: <?= $item['price'] ?> €</p>
            <?php
            if (!is_in_cart($dbh, $item_id, $user['id'])) {
                ?>
                <form class="cart" action="../actions/action_add_to_cart.php?item=<?= $item_id ?>" 
                    method="post">
                    <input id="add_to_cart_button" type="submit" name="add" value="Add to cart">
                </form>
                <?php
            } else {
                ?>
                <div class="cart">
                    <p>Already in your cart!</p>
                </div>
                <?php
            }
            ?>
            <form class="chat" action="../actions/action_chat.php" method="post">
                <input type="hidden" name="user1" value="<?=$user['id']?>">
                <input type="hidden" name="user2" value="<?=$item['seller']?>">
                <input id="chat_button" type="submit" name="chat" value="Chat with seller">
            </form>
            <?php
        }
        ?>
    </article>
    <?php

    ?>
    <article class="descript">
        <p><?= $item['descript'] ?></p>
    </article>
<?php

    draw_footer();
}
