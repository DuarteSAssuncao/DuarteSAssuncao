package com.project.l02gr08.state.gamestate;

import com.project.l02gr08.controller.gamecontroller.PositionController;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.pieces.Piece;
import com.project.l02gr08.viewer.gameviewer.PositionViewer;

public class PositionState extends GameState<PositionController, PositionViewer> {
    private final Piece selected;

    public PositionState(PositionController c, PositionViewer v, Board b, Piece s) {
        super(c, v, b);
        selected = s;
    }

    public Piece getSelectedPiece() {
        return selected;
    }
}
