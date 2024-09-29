<?php

function redirect_if_not_logged_in(): void
{
    if (!isset($_SESSION['username'])) {
        header('Location: ../src/login.php');
    }
}

function redirect_if_not_admin(): void
{
    redirect_if_not_logged_in();
    $username = $_SESSION['username'];
    if (!is_admin(get_database_connection(), $username)) {
        $_SESSION['error'] = 'Naughty naughty! Don\'t touch the admin panels!';
        header('Location: ../src/index.php');
    }
}

function session(): void
{
    session_start(options: [
        'cookie_lifetime' => 0,
        'cookie_httponly' => true,
        'cookie_samesite' => 'Strict',
        'use_strict_mode' => true,
    ]);
}