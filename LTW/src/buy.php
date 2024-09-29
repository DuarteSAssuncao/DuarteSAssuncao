<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/items.db.php');

session();
redirect_if_not_logged_in();
draw_header('Checkout');

$dbh = get_database_connection();
$user = preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']);
$cart = get_items_in_cart($dbh, $user);

?>
<table>
    <tr>
        <td>Item</td>
        <td>Price</td>
    </tr>
<?php
foreach($cart as $item) {
    ?>
    <tr>
        <td><?=$item['brand'] . ' ' . $item['model']?></td>
        <td><?=$item['price'] . '€'?></td>
    </tr>
    <?php    
}
?>
</table>
<form method="post" action="../actions/action_buy.php">
    <label for="address">Full Address:</label>
    <input type="text" id="address" name="address" required>
    <label for="zip_code">Postal/ZIP Code:</label>
    <input type="text" id="zip_code" name="zip_code" required>
    <input type="submit" value="Complete Order">
</form>
<?php
draw_footer();
