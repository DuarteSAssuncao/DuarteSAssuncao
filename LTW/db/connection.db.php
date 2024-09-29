<?php
function get_database_connection(): PDO
{
    return new PDO('sqlite:../db/db.db');
}
