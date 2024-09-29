package com.project.l02gr08.model.pieces;

import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;

import java.util.List;

public class Queen extends Piece {
    static final Paint[] drawing = {
            Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim,
            Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim,
            Paint.Prim, Paint.Prim, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Prim, Paint.Prim,
            Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Prim, Paint.Prim,
            Paint.Prim, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Prim, Paint.Scnd, Paint.Prim, Paint.Prim, Paint.Prim,
            Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim,
            Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim,
            Paint.Prim, Paint.Scnd, Paint.Scnd, Paint.Scnd, Paint.Scnd, Paint.Scnd, Paint.Scnd, Paint.Scnd, Paint.Prim,
            Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim,
    };

    @Override
    public Paint[] getDrawing() {
        return drawing;
    }

    public Queen(Team color, Position position) {
        super(color, position);
    }

    @Override
    public List<Position> generateMoves(Board board) {
        List<Position> res = rookishMoves(board);
        res.addAll(obliqueMoves(board));
        return res;
    }
}
/* Pixel Art by Guilherme Matos
#   #   #
#   #   #
## ### ##
##+###+##
###+#+###
####+####
#########
#+++++++#
#########
*/
