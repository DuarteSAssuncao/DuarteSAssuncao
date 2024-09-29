package com.project.l02gr08.model.pieces;

import java.util.Optional;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;

import java.util.ArrayList;
import java.util.List;

public class Pawn extends Piece {
    static final Paint[] drawing = {
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns,
            Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Scnd, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Trns, Paint.Trns,
            Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim,
    };

    @Override
    public Paint[] getDrawing() {
        return drawing;
    }

    public Pawn(Team color, Position position) {
        super(color, position);
    }
   
    private void upgrade(Board b) {
        b.removePiece(this);
        Piece p = new Queen(this.getTeam(), this.getPosition());
        b.addPiece(p);
    }

    @Override
    public void move(Board b, Position p) {
        List<Position> possibleMoves = generateMoves(b);
        if (!possibleMoves.contains(p)) return;
        Optional<Piece> pis = b.pieceAt(p);
        pis.ifPresent(b::removePiece);
        hasMoved = true;
        position = p;
        if ((this.getTeam() == Team.WHITE && this.getPosition().getY() == 0) || (this.getTeam() == Team.BLACK && this.getPosition().getY() == b.getBoardLength() - 1)) {
            this.upgrade(b);
        }
    }

    @Override
    public List<Position> generateMoves(Board board) {
        List<Position> res = new ArrayList<>();
        Position front = this.position;
        Position twoFront = this.position;
        if (getTeam() == Team.WHITE) {
            front = position.getUp();
            twoFront = position.getUp().getUp();
        } else if (getTeam() == Team.BLACK) {
            front = position.getDown();
            twoFront = position.getDown().getDown();
        }
        if (!board.isOccupied(front)) {
            if (!addIfValid(res, front, board) && !hasMoved) {
                if (!board.isOccupied(twoFront))
                    addIfValid(res, twoFront, board);
            }
        }
        if (board.isOccupied(front.getLeft())) {
            addIfValid(res, front.getLeft(), board);
        }
        if (board.isOccupied(front.getRight())) {
            addIfValid(res, front.getRight(), board);
        }

        return res;
    }
}
/* Pixel Art by Guilherme matos
         
   ###   
  #####  
 ####### 
 ####### 
  #####  
   ###   
  +###+  
#########
*/
