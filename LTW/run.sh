mkdir -p photos
cd db
rm db.db
sqlite3 db.db < db.sql
cd ..
php -S localhost:9000
