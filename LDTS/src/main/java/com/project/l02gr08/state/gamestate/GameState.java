package com.project.l02gr08.state.gamestate;

import com.project.l02gr08.controller.gamecontroller.GameController;
import com.project.l02gr08.model.Board;
import com.project.l02gr08.model.Position;
import com.project.l02gr08.state.State;
import com.project.l02gr08.viewer.gameviewer.GameViewer;

public abstract class GameState<GC extends GameController<? extends GameState<GC, GV>>, GV extends GameViewer>
        extends State<GC, GV> {
    private final Board board;
    private Position cursor;

    public Board getBoard() {
        return board;
    }

    public Position getCursor() {
        return cursor;
    }

    public void setCursor(Position p) {
        cursor = p;
    }

    public GameState(GC controller, GV viewer) {
        super(controller, viewer);
        board = new Board();
        cursor = controller.preferredInitialCursor(board);
    }

    public GameState(GC controller, GV viewer, Board b) {
        super(controller, viewer);
        board = b;
        cursor = controller.preferredInitialCursor(board);
    }
}
