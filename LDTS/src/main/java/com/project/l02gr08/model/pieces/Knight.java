package com.project.l02gr08.model.pieces;

import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;

import java.util.ArrayList;
import java.util.List;

public class Knight extends Piece {
    static final Paint[] drawing = {
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Trns, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Trns,
            Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Trns,
            Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim,
    };

    @Override
    public Paint[] getDrawing() {
        return drawing;
    }

    public Knight(Team color, Position position) {
        super(color, position);
    }

    @Override
    public List<Position> generateMoves(Board board) {
        List<Position> res = new ArrayList<>();
        addIfValid(res, position.getUp().getUp().getLeft(), board);
        addIfValid(res, position.getUp().getUp().getRight(), board);
        addIfValid(res, position.getDown().getDown().getLeft(), board);
        addIfValid(res, position.getDown().getDown().getRight(), board);
        addIfValid(res, position.getUp().getLeft().getLeft(), board);
        addIfValid(res, position.getUp().getRight().getRight(), board);
        addIfValid(res, position.getDown().getLeft().getLeft(), board);
        addIfValid(res, position.getDown().getRight().getRight(), board);
        return res;
    }
}
/* Pixel Art by Guilherme Matos
   # #   
   ###   
   ###+  
  ##+##+ 
 ######+ 
  #  ##+ 
    ##+  
  #####  
#########
*/
