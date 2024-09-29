#!/usr/bin/python3
import random
from dataclasses import dataclass
import datetime

@dataclass
class Gains:
    value : int
    nif   : int
    idBJ  : int
    idSM  : int
    idPK  : int

@dataclass
class Player:
    name: str
    nif: int
    tokens: int

@dataclass
class MoneyForTokens:
    datehour: str
    amount : int 
    nif : int

@dataclass
class PokerTable:
    comission : float
    minRate : int

@dataclass
class SlotMachine:
    maxprize : int
    price : int

@dataclass
class BlackJack:
    minRate: int

@dataclass
class BJGame:
    id : int
    datetime: str
    lucro: int
    casino_score: int
    player_score: int
    aposta: int
    mesa: int

symbols = [
        '🍑',
        '🍆',
        '🍌',
        '🍒',
        '💩',
        '７',
        '🍐',
        '🎁',
        '♥',
        '♠',
        '♣',
        '♦',
        '󰢺',
        '🍼'
        ]
@dataclass
class SMGame:
    id : int
    datetime : str
    lucro : int
    resultado : str
    mesa : int

@dataclass
class PKGame:
    id : int
    datetime : str
    lucro : int
    valueTable : int
    mesa : int


types_of_compra = [("Hotel",100,10000),("Restaurante",10,5000),("Bar", 2,10000),("Concierge",30,300)]

@dataclass 
class Compra:
    id : int
    preco: int
    datetime : str

@dataclass
class Realiza:
    categoria : str
    idcompra : int
    nif : int


first_names = list(map(lambda a: a.rstrip() ,open("first_names.tmp").readlines()))
last_names = list(map(lambda a : a.rstrip(),open("last_names.tmp").readlines()))

players = []

money_tokens = []

poker_tables = []
slot_machines = []
blackjack_tables = []


gains = []

blackjack_games= []

slot_machine_games = []

pocagueime = []

realiza_lst = []
compra_lst = []



##########################################################################
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
##########################################################################



for _ in range(random.randrange(20,100)):
    nif = random.randrange(100000000,999999999)
    while sum( 1 for _ in filter(lambda a: a.nif == nif,players)) != 0:
        nif = random.randrange(100000000,999999999)
    player = Player(first_names[random.randrange(0,len(first_names))] + " " + last_names[random.randrange(0,len(last_names))], nif, 0)
    players.append(player)

for player in players:
    for _ in range(random.randrange(1,20)):
        am = random.randrange(1,5000)
        player.tokens += am
        date = datetime.datetime.now() - datetime.timedelta(days=random.randrange(0,365 * 10), seconds=random.randrange(0,3600*24))
        transaction = MoneyForTokens(date.strftime("%Y-%m-%d %H:%M:%S"), am, player.nif)
        money_tokens.append(transaction)

##########################################################################

for _ in range(random.randrange(1,10)):
    table = PokerTable(random.randrange(0,20) / 100.0, random.randrange(2,50))
    poker_tables.append(table)

for _ in range(random.randrange(10,50)):
    price = random.randrange(1,50)
    machine = SlotMachine(price * 15, price)
    slot_machines.append(machine)

for _ in range(random.randrange(1,50)):
    table = BlackJack(random.randrange(1,50))
    blackjack_tables.append(table)

##########################################################################

idBj = 0

for i, t in enumerate(blackjack_tables):
    for _ in range(random.randrange(1,20)):
        player = players[random.randrange(0,len(players))]
        if max(map(lambda a: a.tokens,players)) < t.minRate:
            break
        while player.tokens <= t.minRate:
            player = players[random.randrange(0,len(players))]
        idBj += 1
        aposta = random.randrange(t.minRate, player.tokens) // 50
        pp = random.randrange(2,30)
        pc = random.randrange(2,30)
        date = datetime.datetime.now() - datetime.timedelta(days=random.randrange(0,365 * 10), seconds=random.randrange(0,3600*24))
        lucro_casino = 0
        # player busts
        if pp > 21 and not (pc > 21):
            lucro_casino = aposta
            player.tokens -= aposta
            gains.append(Gains(-aposta,player.nif, idBj, 0 ,0))
        # casino busts
        elif pc > 21 and not (pp > 21):
            lucro_casino = -aposta
            player.tokens += aposta
            gains.append(Gains(aposta,player.nif, idBj, 0 ,0))
        # both bust
        elif pc > 21 and pp > 21:
            lucro_casino = aposta // 2 + 1
            player.tokens += aposta // 2
            gains.append(Gains(aposta // 2,player.nif, idBj, 0 ,0))
        # same score
        elif pc == pp:
            lucro_casino = aposta // 2
            player.tokens += aposta // 2 + 1
            gains.append(Gains(aposta // 2 + 1,player.nif, idBj, 0 ,0))
        # player wins
        elif pp > pc:
            if pp == 21:
                lucro_casino = - 3*aposta//2
                player.tokens += 3*aposta//2 
                gains.append(Gains(3*aposta//2,player.nif, idBj, 0 ,0))
            else:
                lucro_casino = -aposta
                player.tokens += aposta
                gains.append(Gains(aposta,player.nif, idBj, 0 ,0))
        # casino wins 
        elif pc > pp:
            lucro_casino = aposta
            player.tokens -= aposta
            gains.append(Gains(-aposta,player.nif, idBj, 0 ,0))
        game = BJGame(idBj,date.strftime("%Y-%m-%d %H:%M:%S"), lucro_casino, pc, pp, aposta,i+1)
        blackjack_games.append(game)


idSm = 0
for i, t in  enumerate(slot_machines):
    for _ in range(random.randrange(1,20)):
        player = players[random.randrange(0,len(players))]
        if max(map(lambda a: a.tokens, players)) < t.price:
            break
        while player.tokens <= t.price:
            player = players[random.randrange(0,len(players))]
        idSm += 1
        player.tokens -= t.price
        result = []
        for _ in range(3):
            result.append(symbols[random.randrange(0,len(symbols))])
        lucro = t.price
        date = datetime.datetime.now() - datetime.timedelta(days=random.randrange(0,365 * 10), seconds=random.randrange(0,3600*24))
        if result[0] == result[1] and result[1] == result[2]:
            lucro -= t.maxprize
            player.tokens += t.maxprize
            gains.append(Gains(t.maxprize - t.price,player.nif,0,idSm,0))
        elif result[0] == result[1] or result[0] == result[2] or result[1] == result[2]:
            lucro -= (t.maxprize ** 1/3) // 2
            player.tokens += (t.maxprize ** 1/3) // 2
            gains.append(Gains((t.maxprize ** 1/3) // 2 - t.price,player.nif,0,idSm,0))
        else:
            gains.append(Gains(-t.price, player.nif, 0, idSm,0))
        game = SMGame(idSm,date.strftime("%Y-%m-%d %H:%M:%S") ,lucro,"".join(result),i+1)
        slot_machine_games.append(game)

idPk = 0
for i,t in enumerate(poker_tables):
    for _ in range(random.randrange(1,20)):
        ps = random.sample(players, random.randrange(2,9))
        idPk += 1
        posta = t.minRate
        valorMesa = 0
        ganhoslocais = []
        for p in ps:
            if posta >= p.tokens:
                val = 0
            else:
                val = random.randrange(posta, int(p.tokens))
                valorMesa += val             
            ganhoslocais.append(-val)
        lucro = int(valorMesa * t.comission)
        idx = random.randrange(0,len(ganhoslocais))
        iterations = 10000
        while ganhoslocais[idx] == 0 and iterations > 0:
            idx = random.randrange(0,len(ganhoslocais))
            iterations -= 1
        ganhoslocais[idx] += int(valorMesa - lucro)
        for j,p in enumerate(ps):
            p.tokens += ganhoslocais[j]
            gains.append(Gains(ganhoslocais[j],p.nif,0,0,idPk))
        date = datetime.datetime.now() - datetime.timedelta(days=random.randrange(0,365 * 10), seconds=random.randrange(0,3600*24))
        game = PKGame(idPk,date.strftime("%Y-%m-%d %H:%M:%S"),lucro, valorMesa,i+1)
        pocagueime.append(game)

##########################################################################

idCom = 0
for i,p in enumerate(players):
    for _ in range(random.randrange(50)):
        maybe_compra = random.sample(types_of_compra,1)[0]
        compra = (maybe_compra[0], random.randrange(maybe_compra[1],maybe_compra[2]))
        nif = p.nif
        date = datetime.datetime.now() - datetime.timedelta(days=random.randrange(0,365 * 10), seconds=random.randrange(0,3600*24))
        idCom += 1
        realiza = Realiza(compra[0],idCom,nif)
        compr = Compra(idCom,compra[1],date.strftime("%Y-%m-%d %H:%M:%S"))
        realiza_lst.append(realiza)
        compra_lst.append(compr)



##########################################################################
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
##########################################################################



print("INSERT INTO DinheiroPorFichas (dataHora, quantidade, nif) VALUES")
for i,t in enumerate(money_tokens):
    if i == len(money_tokens) - 1:
        print(f"(\"{t.datehour}\", {t.amount}, {t.nif});")
    else:
        print(f"(\"{t.datehour}\", {t.amount}, {t.nif}),")

##########################################################################

print()
print("INSERT INTO MesaPoquer (taxaComissao, apostaMinima) VALUES")
for i,t in enumerate(poker_tables):
    if i == len(poker_tables) -1:
        print(f"({t.comission},{t.minRate});")
    else:
        print(f"({t.comission},{t.minRate}),")
print()
print("INSERT INTO SlotMachine (premioMaximo, preco) VALUES")
for i,t in enumerate(slot_machines):
    if i == len(slot_machines) -1:
        print(f"({t.maxprize},{t.price});")
    else:
        print(f"({t.maxprize},{t.price}),")
print()
print("INSERT INTO MesaBlackJack (apostaMinima) VALUES")
for i,t in enumerate(blackjack_tables):
    if i == len(blackjack_tables) -1:
        print(f"({t.minRate});")
    else:
        print(f"({t.minRate}),")

##########################################################################

print()
print("INSERT INTO PartidaBlackJack (idBlackJack,dataHora,lucroCasino,pontuacaoCasa,pontuacaoJogador,aposta,idEquipamento) VALUES")
for i,t in enumerate(blackjack_games):
    if i == len(blackjack_games) -1:
        print(f"({t.id},\"{t.datetime}\", {int(t.lucro)}, {t.casino_score}, {t.player_score}, {t.aposta}, {t.mesa});")
    else:
        print(f"({t.id},\"{t.datetime}\", {int(t.lucro)}, {t.casino_score}, {t.player_score}, {t.aposta}, {t.mesa}),")

print()
print("INSERT INTO PartidaSlotMachine (idSlotMachine,dataHora, lucroCasino,listaSimbolos,idEquipamento) VALUES")
for i,t in enumerate(slot_machine_games):
    if i == len(slot_machine_games) -1:
        print(f"({t.id},\"{t.datetime}\", {int(t.lucro)}, \"{t.resultado}\", {t.mesa});")
    else:
        print(f"({t.id},\"{t.datetime}\", {int(t.lucro)}, \"{t.resultado}\", {t.mesa}),")

print()
print("INSERT INTO PartidaPoquer (idPoquer, dataHora, lucroCasino, valorMesa,idEquipamento) VALUES")
for i,t in enumerate(pocagueime):
    if i == len(pocagueime) -1:
        print(f"({t.id},\"{t.datetime}\", {int(t.lucro)}, {t.valueTable}, {t.mesa});")
    else:
        print(f"({t.id},\"{t.datetime}\", {int(t.lucro)}, {t.valueTable}, {t.mesa}),")

##########################################################################

print()
print("INSERT INTO Ganho (valor,nif,idPoquer,idSlotMachine,idBlackJack) VALUES")
for i,t in enumerate(gains):
    idBlackJack = str(t.idBJ)
    idSlotMachine = str(t.idSM) 
    idPoker = str(t.idPK)
    if t.idBJ == 0:
        idBlackJack = "NULL"
    if t.idSM == 0:
        idSlotMachine = "NULL"
    if t.idPK == 0:
        idPoker = "NULL"
    if i == len(gains) -1:
        print(f"({int(t.value)}, {t.nif}, {idPoker}, {idSlotMachine}, {idBlackJack});")
    else:
        print(f"({int(t.value)}, {t.nif}, {idPoker}, {idSlotMachine}, {idBlackJack}),")

##########################################################################

print()
print("INSERT INTO Compra (idCompra, preco, dataHora) VALUES")
for i,c in enumerate(compra_lst):
    if i == len(compra_lst) -1:
        print(f"({c.id}, {c.preco}, \"{c.datetime}\");")
    else:
        print(f"({c.id}, {c.preco}, \"{c.datetime}\"),")

print()
print("INSERT INTO Realiza (nome,idCompra,nif) VALUES")
for i,c in enumerate(realiza_lst):
    if i == len(realiza_lst) -1:
        print(f"(\"{c.categoria}\", {c.idcompra}, {c.nif});")
    else:
        print(f"(\"{c.categoria}\", {c.idcompra}, {c.nif}),")

##########################################################################

print()
print("INSERT INTO Jogador (nif, nome, saldoFichas) VALUES")
for i,player in enumerate(players):
    if i == len(players) - 1:
        print(f"({player.nif}, \"{player.name}\", {int(player.tokens)});")
    else:
        print(f"({player.nif}, \"{player.name}\", {int(player.tokens)}),")


