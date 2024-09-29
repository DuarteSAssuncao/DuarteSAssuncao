<?php

declare(strict_types=1);

function draw_item(array $item, string $photo): void
{
?>
    <a class="card" href="../src/item.php?id=<?= $item['id'] ?>">
        <article onclick="this.parentNode.submit()">
            <img src="<?= $photo ?>" alt="<?= $item['descript'] ?>">
            <h3><?= $item['brand'] . ' - ' . $item['model'] ?></h3>
            <p><?= $item['price'] ?></p>
        </article>
    </a>
<?php
}

function draw_search_form(array $conditions, array $categories, array $sizes, string $d_string, string $d_cond, string $d_cat, string $d_size): void
{
?>
    <form action="index.php" method="get" class="search">
        <label for="Condition">Condition:
            <select id="condition" name="condition">
                <option value='%'>All</option>
                <?php
                foreach ($conditions as $condition) {
                ?>
                    <option value='<?= $condition['condition'] ?>' <?= $d_cond == $condition['condition'] ? 'selected' : '' ?>>
                        <?= $condition['condition'] ?>
                    </option>
                <?php
                }
                ?>
            </select>
        </label>
        <label for="Category">Category:
            <select id="category" name="category">
                <option value='%'>All</option>
                <?php
                foreach ($categories as $category) {
                ?>
                    <option value='<?= $category['category'] ?>' <?= $d_cat == $category['category'] ? 'selected' : '' ?>>
                        <?= $category['category'] ?>
                    </option>
                <?php
                }
                ?>
            </select>
        </label>
        <label for="Size">Size:
            <select id="size" name="size">
                <option value='%'>All</option>
                <?php
                foreach ($sizes as $size) {
                ?>
                    <option value='<?= $size['size'] ?>' <?= $d_size == $size['size'] ? 'selected' : '' ?>>
                        <?= $size['size'] ?>
                    </option>
                <?php
                }
                ?>
            </select>
        </label>

        <span>
            <label for="search">Search:
                <input type="text" id="search" name="search" value=<?= $d_string ?>>
            </label>
            <input type="submit" value="&#x1F50E;">
        </span>
    </form>
<?php
}
