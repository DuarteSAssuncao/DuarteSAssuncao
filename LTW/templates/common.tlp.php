<?php

declare(strict_types=1);

require_once(__DIR__ . '/../db/users.db.php');
require_once(__DIR__ . '/../db/connection.db.php');
require_once(__DIR__ . '/../templates/security.tlp.php');

function draw_header(string $title, string $content = 'content', array $css = [], bool $minimal = false, array $js = []): void
{
?>
    <!DOCTYPE html>
    <html lang="en">

    <head>
        <title><?= "DINO: " . $title ?></title>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no">
        <link rel="icon" href="../media/logo.png" type="image/png">
        <link rel="stylesheet" href="../css/style.css">
        <link rel="stylesheet" href="../css/card.css">
        <link rel="stylesheet" href="../css/responsive.css">
        <?php
        foreach ($css as $file) {
        ?>
            <link rel="stylesheet" href="../css/<?= $file ?>">
        <?php
        }
        foreach ($js as $file) {
        ?>
            <script src="../js/<?= $file ?>" defer></script>
        <?php
        }
        ?>
    </head>

    <body>
        <?php
        if (!$minimal) {
        ?>
            <header>
                <a href="index.php">
                    <img src="../media/logo.png" alt="DINO Logo" width="82" height="82">
                </a>
                <nav>
                    <?php
                    if (is_admin(get_database_connection(), $_SESSION['username'])) {
                    ?>
                        <a href="admin_dashboard.php">
                            <img src="../media/admin.svg" alt="Admin icon" width="50" height="50">
                            <p>Admin</p>
                        </a>
                    <?php
                    }
                    ?>
                    <a href="talk.php">
                        <img src="../media/chat.svg" alt="Chat icon" width="50" height="50">
                        <p>Chat</p>
                    </a>
                    <a href="seller_dashboard.php">
                        <img src="../media/sell.svg" alt="Sell icon" width="50" height="50">
                        <p>Sell</p>
                    </a>
                    <a href="cart.php">
                        <img src="../media/shop_cart.svg" alt="Cart icon" width="50" height="50">
                        <p>Cart</p>
                    </a>
                    <a href="profile.php">
                        <img src="../media/user_settings.svg" alt="Profile icon" width="50" height="50">
                        <p>Profile</p>
                    </a>
                </nav>
            </header>
        <?php
        } else {
        ?>
            <header class="minimal">
                <p><strong> Dino </strong> Is Not OLX</p>
                <img src="../media/logo.png" alt="DINO Logo" width="82" height="82">
            </header>
        <?php
        }
        print_error();
        ?>
        <h1> <?= $title ?> </h1>
        <section class="<?= $content ?>">
        <?php
    }

    function draw_footer(): void
    {
        ?>
        </section>
        <footer>
            <a href="mailto:up202208319@fe.up.pt">&#9426; Duarte Assunção - up202208319@fe.up.pt</a>
            <a href="mailto:up202208755@fe.up.pt">&#9426; Guilherme Matos - up202208755@fe.up.pt</a>
            <a href="mailto:up202208393@fe.up.pt">&#9426; João Ferreira - up202208393@fe.up.pt</a>
        </footer>
    </body>

    </html>
    <?php
    }

    function print_error(): void
    {
        if (isset($_SESSION['error'])) { ?>
        <bold>
            <?= $_SESSION['error'] ?>
        </bold>
<?php
            unset($_SESSION['error']);
        }
    }
