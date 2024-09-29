-- DROP TABLE IF EXISTS Condition;
-- DROP TABLE IF EXISTS ItemSize;
-- DROP TABLE IF EXISTS Category;
-- DROP TABLE IF EXISTS User;
-- DROP TABLE IF EXISTS Item;
-- DROP TABLE IF EXISTS ShoppingCart;
-- DROP TABLE IF EXISTS Inquiry;
-- DROP TABLE IF EXISTS IMessage;

CREATE TABLE IF NOT EXISTS Condition(
    condition TEXT PRIMARY KEY
);

CREATE TABLE IF NOT EXISTS Size(
    size TEXT PRIMARY KEY 
);

CREATE TABLE IF NOT EXISTS Category(
    category TEXT PRIMARY KEY 
);

CREATE TABLE IF NOT EXISTS User(
    id INTEGER PRIMARY KEY,
    fullName TEXT NOT NULL,
    username TEXT UNIQUE NOT NULL,
    pw TEXT NOT NULL, -- password
    eMail TEXT UNIQUE NOT NULL,
    isAdmin BOOLEAN DEFAULT (FALSE)
);

CREATE TABLE IF NOT EXISTS Item(
    id INTEGER PRIMARY KEY,
    brand TEXT NOT NULL,
    model TEXT,
    descript TEXT,
    price REAL NOT NULL CHECK (price > 0) DEFAULT (1),
    isSold BOOLEAN DEFAULT (FALSE),
    condition TEXT NOT NULL REFERENCES Condition(cond) ON DELETE SET NULL,
    size TEXT REFERENCES Size(size) ON DELETE SET NULL,
    category TEXT REFERENCES Category(category) ON DELETE SET NULL,
    seller INT REFERENCES User(id) ON DELETE SET NULL,
    UNIQUE(brand, model, seller)
);

CREATE TABLE IF NOT EXISTS Photo(
    id INTEGER PRIMARY KEY,
    item INT NOT NULL REFERENCES Item (id) ON DELETE CASCADE,
    photo TEXT NOT NULL,
    UNIQUE(item, photo)
);

CREATE TABLE IF NOT EXISTS ShoppingCart(
    user INT NOT NULL REFERENCES User(user) ON DELETE CASCADE,
    item INT NOT NULL REFERENCES Item(item) ON DELETE CASCADE,
    UNIQUE(item, user)
);

CREATE TABLE IF NOT EXISTS Chat(
    id INTEGER PRIMARY KEY,
    user1 INT NOT NULL REFERENCES User(id) ON DELETE SET NULL,
    user2 INT NOT NULL REFERENCES User(id) ON DELETE SET NULL,
    CONSTRAINT different_users CHECK (user1 != user2),
    UNIQUE(user1, user2)
);

CREATE TRIGGER IF NOT EXISTS unique_chat_between_users
    AFTER INSERT ON Chat
    FOR EACH ROW
    WHEN (SELECT COUNT(*) FROM Chat AS C WHERE C.user1 == NEW.user2 AND C.user2 == NEW.user1) != 0
    -- When the chat exists, but with the users in the opposite order:
    BEGIN
        DELETE FROM Chat
        WHERE user1 == NEW.user1
        AND user2 == NEW.user2; 
    END;


CREATE TABLE IF NOT EXISTS Msg( -- Message
    id INTEGER PRIMARY KEY,
    chat INT NOT NULL REFERENCES Chat(id) ON DELETE CASCADE,
    sender INT NOT NULL REFERENCES User(id) ON DELETE SET NULL,
    content TEXT NOT NULL,
    dt DATETIME NOT NULL
);

CREATE TABLE IF NOT EXISTS Purchase(
    id INTEGER PRIMARY KEY,
    item INT NOT NULL REFERENCES Item(id) ON DELETE CASCADE,
    buyer INT NOT NULL REFERENCES User(id) ON DELETE SET NULL,
    address TEXT NOT NULL,
    postalCode TEXT NOT NULL,
    UNIQUE(item, buyer)
);

INSERT INTO Condition (condition) VALUES ('New');
INSERT INTO Condition (condition) VALUES ('Used');

INSERT INTO Size (size) VALUES ('XS');
INSERT INTO Size (size) VALUES ('S');
INSERT INTO Size (size) VALUES ('M');
INSERT INTO Size (size) VALUES ('L');
INSERT INTO Size (size) VALUES ('XL');
INSERT INTO Size (size) VALUES ('N/A');

INSERT INTO Category (category) VALUES ('Cars');
INSERT INTO Category (category) VALUES ('Clothes');

INSERT INTO User (fullName, username, pw, eMail, isAdmin) VALUES ('Test Account', 'test', '$2y$10$Bk.QPEzXSfAwPvhDLu5u4eOv2ksU4kH3teuFyHgMBcuTcuYhe6gOy', 'test@dino.pt', 1);
-- password: test
