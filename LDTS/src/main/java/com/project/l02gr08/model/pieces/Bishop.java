package com.project.l02gr08.model.pieces;

import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;

import java.util.List;

public class Bishop extends Piece {
    static final Paint[] drawing = {
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Trns, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Trns, Paint.Trns, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Trns, Paint.Trns, Paint.Trns,
            Paint.Trns, Paint.Scnd, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Scnd, Paint.Trns,
            Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim, Paint.Prim,
    };

    @Override
    public Paint[] getDrawing() {
        return drawing;
    }

    public Bishop(Team color, Position position) {
        super(color, position);
    }

    @Override
    public List<Position> generateMoves(Board board) { 
       return obliqueMoves(board); 
    }
}

/* Pixel Art by Guilherme Matos
    #    
   ##    
   # #   
  #####  
  #####  
   ###   
   ###   
 +#####+ 
#########
*/
