<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../templates/item.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/items.db.php');

session();
redirect_if_not_logged_in();
draw_header('Your Sales');

$db = get_database_connection();
$items = get_my_items($db, preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']));

?>
<input type="button" value="+ Add Item" onclick="location.href='new_item.php';">

<?php

foreach ($items as $item) {
    draw_item($item, get_photo_path($db, $item['id']));
}


draw_footer();
