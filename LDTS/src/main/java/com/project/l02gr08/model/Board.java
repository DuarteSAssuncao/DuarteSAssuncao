package com.project.l02gr08.model;

import com.project.l02gr08.model.pieces.*;
import com.project.l02gr08.model.pieces.Piece.Team;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Board {
    private static final int BOARD_LENGTH = 8;
    private final List<Piece> pieces;

    public Board() {
        pieces = new ArrayList<>();
        pieces.addAll(generateWhitePawns());
        pieces.addAll(generateBlackPawns());
        pieces.addAll(generateRooks());
        pieces.addAll(generateKnights());
        pieces.addAll(generateBishops());
        pieces.addAll(generateQueens());
        pieces.addAll(generateKings());
    }

    public Board(List<Piece> pieces) {
        this.pieces = pieces;
    }

    public Board(Board board) {
        this.pieces = new ArrayList<>();
        for (Piece piece : board.getPieces()) {
            Position newPosition = new Position(piece.getPosition());
            Team team = piece.getTeam();
            Piece newPiece = null;
            try {
                newPiece = piece.getClass().getDeclaredConstructor(Team.class, Position.class).newInstance(team,
                        newPosition);
            } catch (InstantiationException | IllegalAccessException | InvocationTargetException
                    | NoSuchMethodException e) {
                System.out.println("ERROR in creating a new Board using the copy constructor.");
                System.exit(2);
            }
            this.pieces.add(newPiece);
        }
    }

    public List<Piece> getPieces() {
        return pieces;
    }

    public int getBoardLength() {
        return BOARD_LENGTH;
    }

    public Optional<Piece> pieceAt(Position position) {
        for (Piece piece : this.pieces) {
            if (piece.getPosition().equals(position))
                return Optional.of(piece);
        }
        return Optional.empty();
    }

    public boolean isOccupied(Position position) {
        for (Piece piece : this.pieces) {
            if (piece.getPosition().equals(position))
                return true;
        }
        return false;
    }

    public void movePiece(Piece piece, Position position) {
        Optional<Piece> target = pieceAt(position);
        target.ifPresent(this::removePiece);
        piece.setPosition(position);
    }

    public void removePiece(Piece piece) {
        this.pieces.remove(piece);
    }

    public void addPiece(Piece piece) {
        this.pieces.add(piece);
    }

    public boolean isCheck(Team team) {
        Optional<King> king = findKing(team);
        if (king.isPresent()) {
            return king.get().isInCheck(this);
        } else {
            System.out.println("This board doesn't have a king. Aborting program...");
            System.exit(1);
            return false;
        }
    }

    public boolean isCheckMate(Team team) {
        if (!isCheck(team))
            return false;
        for (Piece piece : getPieces()) {
            if (piece.getTeam() == team) {
                for (Position position : piece.generateRecommendedMoves(this)) {
                    if (resolvesCheck(piece, position))
                        return false;
                }
            }
        }
        return true;
    }

    public boolean resolvesCheck(Piece piece, Position newPosition) {
        Board newBoard = new Board(this);
        Optional<Piece> newPiece = newBoard.pieceAt(piece.getPosition());
        Optional<King> king = newBoard.findKing(piece.getTeam());
        if (king.isEmpty()) {
            System.out.println("This board doesn't have a king. Aborting program...");
            System.exit(1);
            return false;
        } else {
            newPiece.ifPresent(value -> newBoard.movePiece(value, newPosition));
            return !king.get().isInCheck(newBoard);
        }
    }

    public Optional<King> findKing(Team team) {
        for (Piece piece: getPieces()) {
            if (piece instanceof King && piece.getTeam() == team)
                return Optional.of((King) piece);
        }
        return Optional.empty();
    }

    // ===============================================================================

    private List<Pawn> generateWhitePawns() {
        ArrayList<Pawn> res = new ArrayList<>();
        for (int i = 0; i < BOARD_LENGTH; ++i) {
            Pawn p = new Pawn(Team.WHITE, new Position(i, BOARD_LENGTH - 2));
            res.add(p);
        }
        return res;
    }

    private List<Pawn> generateBlackPawns() {
        ArrayList<Pawn> res = new ArrayList<>();
        for (int i = 0; i < BOARD_LENGTH; ++i) {
            Pawn p = new Pawn(Team.BLACK, new Position(i, 1));
            res.add(p);
        }
        return res;
    }

    private List<Rook> generateRooks() {
        ArrayList<Rook> res = new ArrayList<>();
        res.add(new Rook(Team.WHITE, new Position(0, BOARD_LENGTH - 1)));
        res.add(new Rook(Team.WHITE, new Position(BOARD_LENGTH - 1, BOARD_LENGTH - 1)));
        res.add(new Rook(Team.BLACK, new Position(0, 0)));
        res.add(new Rook(Team.BLACK, new Position(BOARD_LENGTH - 1, 0)));
        return res;
    }

    private List<Knight> generateKnights() {
        ArrayList<Knight> res = new ArrayList<>();
        res.add(new Knight(Team.WHITE, new Position(1, BOARD_LENGTH - 1)));
        res.add(new Knight(Team.WHITE, new Position(BOARD_LENGTH - 2, BOARD_LENGTH - 1)));
        res.add(new Knight(Team.BLACK, new Position(1, 0)));
        res.add(new Knight(Team.BLACK, new Position(BOARD_LENGTH - 2, 0)));
        return res;
    }

    private List<Bishop> generateBishops() {
        ArrayList<Bishop> res = new ArrayList<>();
        res.add(new Bishop(Team.WHITE, new Position(2, BOARD_LENGTH - 1)));
        res.add(new Bishop(Team.WHITE, new Position(BOARD_LENGTH - 3, BOARD_LENGTH - 1)));
        res.add(new Bishop(Team.BLACK, new Position(2, 0)));
        res.add(new Bishop(Team.BLACK, new Position(BOARD_LENGTH - 3, 0)));
        return res;
    }

    private List<Queen> generateQueens() {
        ArrayList<Queen> res = new ArrayList<>();
        res.add(new Queen(Team.WHITE, new Position(3, BOARD_LENGTH - 1)));
        res.add(new Queen(Team.BLACK, new Position(3, 0)));
        return res;
    }

    private List<King> generateKings() {
        ArrayList<King> res = new ArrayList<>();
        res.add(new King(Team.WHITE, new Position(4, BOARD_LENGTH - 1)));
        res.add(new King(Team.BLACK, new Position(4, 0)));
        return res;
    }
}
