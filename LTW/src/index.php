<?php

declare(strict_types=1);
require_once(__DIR__ . '/../templates/security.tlp.php');
require_once(__DIR__ . '/../templates/common.tlp.php');
require_once(__DIR__ . '/../templates/item.tlp.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../db/items.db.php');
require_once(__DIR__ . '/../db/entity.db.php');

session();

$db = get_database_connection();
redirect_if_not_logged_in();
draw_header('Browse new items', "index", ['index.css'], js: ['search.js']);

$search = (preg_replace ("/[^a-zA-Z0-9\s%]/", '', '%' . ($_GET['search'] ?? '') . '%' ));
$condition = preg_replace ("/[^a-zA-Z0-9\s%]/", '', $_GET['condition'] ?? '%');
$category = preg_replace ("/[^a-zA-Z0-9\s%]/", '', $_GET['category'] ?? '%');
$size = preg_replace ("/[^a-zA-Z0-9\s%]/", '', $_GET['size'] ?? '%');
$items = get_items_from_others($db, preg_replace ("/[^a-zA-Z0-9\s]/", '', $_SESSION['username']), $search, $condition, $category, $size);
$search = substr($search, 1, -1);

draw_search_form(get_all_conditions($db), get_all_categories($db), get_all_sizes($db), $search, $condition, $category, $size);

?> <section class="items"> <?php
    if (count($items) == 0) {
        $_SESSION['error'] = 'No items found. Please check the filters or try again later.';
        print_error();
    } else {
        foreach ($items as $item) {
            draw_item($item, get_photo_path($db, $item['id']));
        }
    }
?> </section> <?php

draw_footer();
