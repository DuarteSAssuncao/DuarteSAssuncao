package com.project.l02gr08.model.pieces;

import java.util.Optional;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import java.util.ArrayList;
import java.util.List;

public class King extends Piece {
    static final Paint[] drawing = {
            Paint.Trns, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Scnd, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Trns,
            Paint.Prim, Paint.Scnd, Paint.Prim, Paint.Trns, Paint.Scnd, Paint.Trns, Paint.Prim, Paint.Scnd, Paint.Prim,
            Paint.Trns, Paint.Prim, Paint.Trns, Paint.Scnd, Paint.Scnd, Paint.Scnd, Paint.Trns, Paint.Prim, Paint.Trns,
            Paint.Trns, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Scnd, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Trns,
            Paint.Trns, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Scnd, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Trns,
            Paint.Trns, Paint.Prim, Paint.Scnd, Paint.Prim, Paint.Scnd, Paint.Prim, Paint.Scnd, Paint.Prim, Paint.Trns,
            Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns,
            Paint.Trns, Paint.Prim, Paint.Scnd, Paint.Scnd, Paint.Prim, Paint.Scnd, Paint.Scnd, Paint.Prim, Paint.Trns,
            Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim,
    };

    @Override
    public Paint[] getDrawing() {
        return drawing;
    }

    public King(Team color, Position position) {
        super(color, position);
    }

    @Override
    public void move(Board b, Position p) {
        List<Position> possibleMoves = generateMoves(b);
        if (!possibleMoves.contains(p)) return;
        Optional<Piece> pis = b.pieceAt(p);
        pis.ifPresent(b::removePiece);

        List<Position> castlingMoves = generateCastling(b);
        if (castlingMoves.contains(p)) {
            moveCastling(b, p);
        }

        hasMoved = true;
        position = p;
    }

    @Override
    public List<Position> generateMoves(Board board) {
        List<Position> res = new ArrayList<>();
        addIfValid(res, position.getUp(), board);
        addIfValid(res, position.getRight(), board);
        addIfValid(res, position.getDown(), board);
        addIfValid(res, position.getLeft(), board);
        addIfValid(res, position.getUp().getRight(), board);
        addIfValid(res, position.getUp().getLeft(), board);
        addIfValid(res, position.getDown().getRight(), board);
        addIfValid(res, position.getDown().getLeft(), board);

        for (Position pos : generateCastling(board)) {
            addIfValid(res, pos, board);
        }
        return res;
    }

    public boolean isInCheck(Board board) {
        for (Piece piece : board.getPieces()) {
            List<Position> legalMoves = piece.generateMoves(board);
            if (legalMoves.contains(position)) {
                return true;
            }
        }
        return false;
    }

    // ===============================================================================

    private void tryCastlingLeft(Board board, List<Position> res, Piece p) {
        if (p.getHasMoved())
            return;
        if (!(p instanceof Rook))
            return;

        if (board.isOccupied(position.getLeft()))
            return;
        if (board.isOccupied(position.getLeft().getLeft()))
            return;
        if (board.isOccupied(position.getLeft().getLeft().getLeft()))
            return;

        res.add(position.getLeft().getLeft());
    }

    private void tryCastlingRight(Board board, List<Position> res, Piece p) {
        if (p.getHasMoved())
            return;
        if (!(p instanceof Rook))
            return;

        if (board.isOccupied(position.getRight()))
            return;
        if (board.isOccupied(position.getRight().getRight()))
            return;

        res.add(position.getRight().getRight());
    }

    private List<Position> generateCastling(Board board) {
        List<Position> res = new ArrayList<>();
        if (getHasMoved())
            return res;
        int line;
        if (getTeam() == Team.WHITE)
            line = board.getBoardLength() - 1;
        else
            line = 0;

        Optional<Piece> p = board.pieceAt(new Position(0, line));
        p.ifPresent(piece -> tryCastlingLeft(board, res, piece));

        p = board.pieceAt(new Position(board.getBoardLength() - 1, line));
        p.ifPresent(piece -> tryCastlingRight(board, res, piece));

        return res;
    }

    private void moveCastling(Board board, Position newPos) {
        int line;
        if (getTeam() == Team.WHITE)
            line = board.getBoardLength() - 1;
        else
            line = 0;

        int newColumn;
        int oldColumn;
        if (newPos.getX() == 2) {
            newColumn = 3;
            oldColumn = 0;
        } else {
            newColumn = board.getBoardLength() - 3;
            oldColumn = board.getBoardLength() - 1;
        }

        Optional<Piece> rook = board.pieceAt(new Position(oldColumn, line));
        if (rook.isPresent()) {
            if (rook.get().getHasMoved()) return;
            rook.get().setHasMoved(true);
            rook.get().setPosition(new Position(newColumn, line));
        }
    }
}
/* Pixel Art by Guilherme Matos
 #  +  # 
#+# + #+#
 # +++ # 
 ## + ## 
 ## + ## 
 #+#+#+# 
 ###+### 
 #++#++# 
#########
*/
