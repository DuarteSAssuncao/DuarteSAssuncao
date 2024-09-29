DROP TABLE IF EXISTS Jogador;
DROP TABLE IF EXISTS DinheiroPorFichas;
DROP TABLE IF EXISTS Compra;
DROP TABLE IF EXISTS Realiza;
DROP TABLE IF EXISTS Ganho;
DROP TABLE IF EXISTS PartidaPoquer;
DROP TABLE IF EXISTS PartidaSlotMachine;
DROP TABLE IF EXISTS PartidaBlackjack;
DROP TABLE IF EXISTS MesaPoquer;
DROP TABLE IF EXISTS SlotMachine;
DROP TABLE IF EXISTS MesaBlackjack;


CREATE TABLE Jogador (
  nif INT NOT NULL,
  nome TEXT NOT NULL,
  saldoFichas INT DEFAULT (0),
  PRIMARY KEY (nif)
);

CREATE TABLE DinheiroPorFichas (
  idTransacao INTEGER,
  dataHora DATETIME NOT NULL,
  quantidade INT NOT NULL,
  nif INT NOT NULL,
  PRIMARY KEY (idTransacao),
  UNIQUE (dataHora, nif),
  FOREIGN KEY (nif) REFERENCES Jogador (nif)
);

CREATE TABLE Compra (
  idCompra INTEGER,
  preco INT NOT NULL,
  dataHora DATETIME NOT NULL,
  PRIMARY KEY (idCompra)
  CONSTRAINT precoPositivo CHECK (preco >= 0)
);

CREATE TABLE Realiza (
  nome TEXT NOT NULL,
  idCompra INT NOT NULL,
  nif INT NOT NULL,
  PRIMARY KEY (idCompra, nif),
  FOREIGN KEY (idCompra) REFERENCES Compra (idCompra) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (nif) REFERENCES Jogador (nif) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE Ganho (
  idGanho INTEGER,
  valor INT NOT NULL,
  nif INT NOT NULL,
  idPoquer INT DEFAULT NULL, -- Não é UNIQUE, porque a uma partida de Póquer está associada a vários jogadores, logo, vários ganhos.
  idSlotMachine INT UNIQUE DEFAULT NULL, -- UNIQUE, porque uma partida de SlotMachine só está associada a 1 jogador, logo, só 1 ganho.
  idBlackjack INT UNIQUE DEFAULT NULL, -- UNIQUE, porque uma partida de BlackJack só está associada a 1 jogador, logo, só 1 ganho.
  PRIMARY KEY (idGanho),
  UNIQUE (nif, idPoquer, idSlotMachine, idBlackjack), -- Cada jogador só tem um ganho por jogo que faça
  FOREIGN KEY (nif) REFERENCES Jogador (nif) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (idPoquer) REFERENCES PartidaPoquer (idPoquer) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (idSlotMachine) REFERENCES PartidaSlotMachine (idSlotMachine) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (idBlackjack) REFERENCES PartidaBlackjack (idBlackjack) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT partidaUnica CHECK ((idPoquer != NULL and idSlotMachine == NULL and idBlackjack == NULL) or (idPoquer == NULL and idSlotMachine != NULL and idBlackjack == NULL) or (idPoquer == NULL and idSlotMachine == NULL and idBlackjack != NULL))
  -- Como um ganho só está associado a uma única partida, 2 chaves estrangeiras idPartida terão de ser NULAS 1 não NULA
);

CREATE TABLE PartidaPoquer (
  idPoquer INTEGER,
  dataHora DATETIME NOT NULL,
  lucroCasino INT DEFAULT (0),
  valorMesa INT NOT NULL,
  idEquipamento INT NOT NULL,
  PRIMARY KEY (idPoquer),
  UNIQUE (idEquipamento, dataHora),
  FOREIGN KEY (idEquipamento) REFERENCES MesaPoquer (idEquipamento) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE PartidaSlotMachine (
  idSlotMachine INTEGER,
  dataHora DATETIME NOT NULL,
  lucroCasino INT DEFAULT (0),
  listaSimbolos TEXT NOT NULL,
  idEquipamento INT NOT NULL,
  PRIMARY KEY (idSlotMachine),
  UNIQUE (idEquipamento, dataHora),
  FOREIGN KEY (idEquipamento) REFERENCES SlotMachine (idEquipamento) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE PartidaBlackjack (
  idBlackjack INTEGER,
  dataHora DATETIME NOT NULL,
  lucroCasino INT DEFAULT (0),
  pontuacaoCasa SMALLINT NOT NULL,
  pontuacaoJogador SMALLINT NOT NULL,
  aposta INT NOT NULL,
  idEquipamento INT NOT NULL,
  PRIMARY KEY (idBlackjack),
  UNIQUE (idEquipamento, dataHora),
  FOREIGN KEY (idEquipamento) REFERENCES MesaBlackjack (idEquipamento) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE MesaPoquer (
  idEquipamento INTEGER,
  taxaComissao FLOAT NOT NULL,
  apostaMinima INT NOT NULL,
  PRIMARY KEY (idEquipamento)
);

CREATE TABLE SlotMachine (
  idEquipamento INTEGER,
  premioMaximo INT NOT NULL,
  preco INT NOT NULL,
  PRIMARY KEY (idEquipamento)
);

CREATE TABLE MesaBlackjack (
  idEquipamento INTEGER,
  apostaMinima INT NOT NULL,
  PRIMARY KEY (idEquipamento)
);
