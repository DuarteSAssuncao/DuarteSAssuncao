package com.project.l02gr08.model.pieces;

import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public abstract class Piece {
    public enum Team {
        BLACK, WHITE
    }

    public enum Paint {
        Trns, // Transparent
        Prim, // Primary
        Scnd, // Secondary
    }

    protected final Team color;
    protected Position position;
    protected boolean hasMoved;

    public Piece(Team color, Position position) {
        this.color = color;
        this.position = position;
        this.hasMoved = false;
    }

    public abstract Paint[] getDrawing();

    public Position getPosition() {
        return position;
    }

    public void setPosition(Position position) {
        this.position = position;
    }

    public Team getTeam() {
        return color;
    }

    public boolean getHasMoved() {
        return hasMoved;
    }

    public void setHasMoved(boolean b) {
        hasMoved = b;
    }

    public abstract List<Position> generateMoves(Board board);

    public List<Position> generateRecommendedMoves(Board board) {
        if (!board.isCheck(this.color)) {
            return removeStillInCheckMoves(generateMoves(board), board);
        } else {
            return removeToCheckMoves(generateMoves(board), board);
        }
    }

    public void move(Board b, Position p) {
        List<Position> possibleMoves = generateMoves(b);
        if (!possibleMoves.contains(p)) return;
        Optional<Piece> pis = b.pieceAt(p);
        pis.ifPresent(b::removePiece);
        hasMoved = true;
        position = p;
    }

    // ===============================================================================

    protected boolean addIfValid(List<Position> stack, Position needle, Board b) {
        if (!isInsideBoard(needle, b.getBoardLength())) return true;
        Optional<Piece> p = b.pieceAt(needle);
        if (p.isPresent()) {
            if (getTeam() != p.get().getTeam()) {
                stack.add(needle);
            }
            return true;
        } else {
            stack.add(needle);
            return false;
        }
    }

    protected List<Position> rookishMoves(Board board) {
        List<Position> res = new ArrayList<>();
        int bsize = board.getBoardLength();
        for (Position p = this.position.getUp(); isInsideBoard(p, bsize); p = p.getUp()) {
            if (addIfValid(res, p, board)) break;
        }
        for (Position p = this.position.getDown(); isInsideBoard(p, bsize); p = p.getDown()) {
            if (addIfValid(res, p, board)) break;
        }
        for (Position p = this.position.getLeft(); isInsideBoard(p, bsize); p = p.getLeft()) {
            if (addIfValid(res, p, board)) break;
        }
        for (Position p = this.position.getRight(); isInsideBoard(p, bsize); p = p.getRight()) {
            if (addIfValid(res, p, board)) break;
        }
        return res;
    }

    protected List<Position> obliqueMoves(Board board) {
        List<Position> res = new ArrayList<>();
        int bsize = board.getBoardLength();
        for (Position p = this.position.getUp().getLeft(); isInsideBoard(p, bsize); p = p.getUp().getLeft()) {
            if (addIfValid(res, p, board)) break;
        }
        for (Position p = this.position.getUp().getRight(); isInsideBoard(p, bsize); p = p.getUp().getRight()) {
            if (addIfValid(res, p, board)) break;
        }
        for (Position p = this.position.getDown().getLeft(); isInsideBoard(p, bsize); p = p.getDown().getLeft()) {
            if (addIfValid(res, p, board)) break;
        }
        for (Position p = this.position.getDown().getRight(); isInsideBoard(p, bsize); p = p.getDown()
                .getRight()) {
            if (addIfValid(res, p, board)) break;
        }
        return res;
    }

    protected boolean isInsideBoard(Position position, int boardSize) {
        return position.getX() >= 0 && position.getX() < boardSize && position.getY() >= 0
                && position.getY() < boardSize;
    }

    protected List<Position> removeStillInCheckMoves(List<Position> legalMoves, Board board) {
        List<Position> res = new ArrayList<>();
        for (Position position : legalMoves) {
            if (board.resolvesCheck(this, position))
                res.add(position);
        }
        return res;
    }

    protected List<Position> removeToCheckMoves(List<Position> legalMoves, Board board) {
        List<Position> res = new ArrayList<>();
        for (Position possible : legalMoves) {
            Board newBoard = new Board(board);
            Optional<Piece> newPiece = newBoard.pieceAt(this.position);
            if (newPiece.isPresent()) {
                newPiece.get().move(newBoard, new Position(possible));
                if (!newBoard.isCheck(newPiece.get().color)) {
                    res.add(possible);
                }
            }
        }
        return res;
    }
}
