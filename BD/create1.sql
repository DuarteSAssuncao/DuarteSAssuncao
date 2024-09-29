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
  nif INT,
  nome TEXT,
  saldoFichas INT DEFAULT (0),
  PRIMARY KEY (nif)
);

CREATE TABLE DinheiroPorFichas (
  idTransacao INTEGER,
  dataHora DATETIME,
  quantidade INT,
  nif INT,
  PRIMARY KEY (idTransacao),
  UNIQUE (dataHora, nif),
  FOREIGN KEY (nif) REFERENCES Jogador (nif)
);

CREATE TABLE Compra (
  idCompra INTEGER,
  preco INT,
  dataHora DATETIME,
  PRIMARY KEY (idCompra)
  CONSTRAINT precoPositivo CHECK (preco >= 0)
);

CREATE TABLE Realiza (
  nome TEXT,
  idCompra INT,
  nif INT,
  PRIMARY KEY (idCompra, nif),
  FOREIGN KEY (idCompra) REFERENCES Compra (idCompra) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY (nif) REFERENCES Jogador (nif) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE Ganho (
  idGanho INTEGER,
  valor INT,
  nif INT,
  idPoquer INT, -- Não é UNIQUE, porque a uma partida de Póquer está associada a vários jogadores, logo, vários ganhos.
  idSlotMachine INT UNIQUE, -- UNIQUE, porque uma partida de SlotMachine só está associada a 1 jogador, logo, só 1 ganho.
  idBlackjack INT UNIQUE, -- UNIQUE, porque uma partida de BlackJack só está associada a 1 jogador, logo, só 1 ganho.
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
  dataHora DATETIME,
  lucroCasino INT DEFAULT (0),
  valorMesa INT,
  idEquipamento INT,
  PRIMARY KEY (idPoquer),
  UNIQUE (idEquipamento, dataHora),
  FOREIGN KEY (idEquipamento) REFERENCES MesaPoquer (idEquipamento) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE PartidaSlotMachine (
  idSlotMachine INTEGER,
  dataHora DATETIME,
  lucroCasino INT DEFAULT (0),
  listaSimbolos TEXT,
  idEquipamento INT,
  PRIMARY KEY (idSlotMachine),
  UNIQUE (idEquipamento, dataHora),
  FOREIGN KEY (idEquipamento) REFERENCES SlotMachine (idEquipamento) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE PartidaBlackjack (
  idBlackjack INTEGER,
  dataHora DATETIME,
  lucroCasino INT DEFAULT (0),
  pontuacaoCasa SMALLINT,
  pontuacaoJogador SMALLINT,
  aposta INT,
  idEquipamento INT,
  PRIMARY KEY (idBlackjack),
  UNIQUE (idEquipamento, dataHora),
  FOREIGN KEY (idEquipamento) REFERENCES MesaBlackjack (idEquipamento) ON DELETE RESTRICT ON UPDATE CASCADE
);

CREATE TABLE MesaPoquer (
  idEquipamento INTEGER,
  taxaComissao FLOAT,
  apostaMinima INT,
  PRIMARY KEY (idEquipamento)
);

CREATE TABLE SlotMachine (
  idEquipamento INTEGER,
  premioMaximo INT,
  preco INT,
  PRIMARY KEY (idEquipamento)
);

CREATE TABLE MesaBlackjack (
  idEquipamento INTEGER,
  apostaMinima INT,
  PRIMARY KEY (idEquipamento)
);
